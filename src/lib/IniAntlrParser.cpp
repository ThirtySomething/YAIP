//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************

#include "IniAntlrParser.h"

#include "IniEntry.h"
#include "IniSection.h"
#include "ParseErrorListener.h"
#include "antlr/generated/IniLexer.h"
#include "antlr/generated/IniParser.h"
#include "antlr4-runtime.h"
#include "string_extensions.h"

namespace
{
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

        // Recover original byte values after feeding parser with UTF-8-safe data.
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

        return net::derpaul::yaip::trim(restored);
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
}

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            bool IniAntlrParser::Parse(const std::string &content, IniSectionList &sections)
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

                        IniSectionPtr sectionPtr(new IniSection);
                        sectionPtr->ElementIdentifierSet(textFrom(sectionCtx->name));
                        if (sectionCtx->comment())
                        {
                            sectionPtr->ElementCommentSet(textFrom(sectionCtx->comment()->text()));
                        }

                        sections.ElementAdd(sectionPtr);
                        currentSection = sectionPtr.get();
                        continue;
                    }

                    if (statement->pairStatement() && (nullptr != currentSection))
                    {
                        IniParser::PairStatementContext *pairCtx = statement->pairStatement();

                        IniEntryPtr entryPtr(new IniEntry);
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
