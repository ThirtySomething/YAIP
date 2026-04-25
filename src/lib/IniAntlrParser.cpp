//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************
// This file is part of YAIP.
//
// YAIP is free software: you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// YAIP is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with YAIP. If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************

#include "IniAntlrParser.h"

#include "IniEntry.h"
#include "IniSection.h"
#include "ParseErrorListener.h"
#include "antlr/generated/IniLexer.h"
#include "antlr/generated/IniParser.h"
#include "antlr4-runtime.h"
#include "string_extensions.h"
#include <memory>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            IniSection *ensureImplicitGlobalSection(IniSectionList &sections)
            {
                if (auto existing = sections.ElementFind(""); existing != nullptr)
                {
                    existing->ImplicitGlobalSet(true);
                    return existing.get();
                }

                auto sectionPtr = std::make_shared<IniSection>();
                sectionPtr->ImplicitGlobalSet(true);
                sections.ElementAdd(sectionPtr);
                return sectionPtr.get();
            }

            std::string textFrom(IniParser::TextContext *ctx)
            {
                if (nullptr == ctx)
                {
                    return "";
                }

                std::string result;
                auto tokens = ctx->TEXT();
                for (auto *token : tokens)
                {
                    result += token->getText();
                }

                std::string restored;
                restored.reserve(result.size());
                for (size_t i = 0; i < result.size(); ++i)
                {
                    unsigned char lead = static_cast<unsigned char>(result[i]);
                    if ((lead >= 0xC2) && (lead <= 0xC3) && ((i + 1) < result.size()))
                    {
                        unsigned char tail = static_cast<unsigned char>(result[i + 1]);
                        if ((tail >= 0x80) && (tail <= 0xBF))
                        {
                            unsigned char codePoint = static_cast<unsigned char>(((lead & 0x1F) << 6) | (tail & 0x3F));
                            restored.push_back(static_cast<char>(codePoint));
                            ++i;
                            continue;
                        }
                    }

                    restored.push_back(result[i]);
                }

                return trim(restored);
            }

            std::string encodeBytesAsUtf8(const std::string &raw)
            {
                std::string utf8;
                utf8.reserve(raw.size() * 2);

                for (unsigned char byte : raw)
                {
                    if (byte < 0x80)
                    {
                        utf8.push_back(static_cast<char>(byte));
                    }
                    else
                    {
                        utf8.push_back(static_cast<char>(0xC0 | (byte >> 6)));
                        utf8.push_back(static_cast<char>(0x80 | (byte & 0x3F)));
                    }
                }

                return utf8;
            }

            bool IniAntlrParser::Parse(const std::string &content, IniSectionList &sections) const
            {
                antlr4::ANTLRInputStream input;
                input.load(encodeBytesAsUtf8(content), true);
                IniLexer lexer(&input);
                antlr4::CommonTokenStream tokens(&lexer);
                IniParser parser(&tokens);

                detail::ParseErrorListener lexerErrorListener;
                detail::ParseErrorListener parserErrorListener;

                lexer.removeErrorListeners();
                parser.removeErrorListeners();
                lexer.addErrorListener(&lexerErrorListener);
                parser.addErrorListener(&parserErrorListener);

                IniParser::IniFileContext *document = parser.iniFile();

                if (lexerErrorListener.HadError() || parserErrorListener.HadError() || nullptr == document)
                {
                    return false;
                }

                sections.clear();
                IniSection *currentSection = nullptr;

                for (auto *statement : document->statement())
                {
                    if (nullptr == statement)
                    {
                        continue;
                    }

                    if (statement->sectionStatement())
                    {
                        IniParser::SectionStatementContext *sectionCtx = statement->sectionStatement();

                        auto sectionPtr = std::make_shared<IniSection>();
                        sectionPtr->ElementIdentifierSet(textFrom(sectionCtx->name));
                        if (sectionCtx->comment())
                        {
                            sectionPtr->ElementCommentSet(textFrom(sectionCtx->comment()->text()));
                        }

                        sections.ElementAdd(sectionPtr);
                        currentSection = sectionPtr.get();
                        continue;
                    }

                    if (statement->pairStatement())
                    {
                        if (nullptr == currentSection)
                        {
                            currentSection = ensureImplicitGlobalSection(sections);
                        }

                        IniParser::PairStatementContext *pairCtx = statement->pairStatement();

                        auto entryPtr = std::make_shared<IniEntry>();
                        entryPtr->ElementIdentifierSet(textFrom(pairCtx->key));
                        entryPtr->ElementValueSet(textFrom(pairCtx->value));
                        if (pairCtx->comment())
                        {
                            entryPtr->ElementCommentSet(textFrom(pairCtx->comment()->text()));
                        }

                        currentSection->EntryAdd(entryPtr);
                    }
                }

                return true;
            }
        }
    }
}
