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

#ifndef _INISECTION_H_
#define _INISECTION_H_

#include "IElementCommon.h"
#include "IniEntry.h"
#include "IniEntryList.h"
#include <iostream>
#include <memory>
#include <string>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class IIniVisitor;

            class IniSection : public IElementCommon
            {
            public:
                IniSection(void);
                virtual ~IniSection(void);
                virtual void clear(void) override;
                virtual std::string ElementCommentGet(void) const override;
                virtual void ElementCommentSet(const std::string &ElementComment) override;
                virtual std::string ElementIdentifierGet(void) const override;
                virtual void ElementIdentifierSet(const std::string &ElementIdentifier) override;
                void EntryAdd(const IniEntryPtr &Entry);
                void EntryDelete(const IniEntryPtr &Entry);
                IniEntryPtr EntryFind(const std::string &EntryName);
                tListString EntryKeyList(void) const;
                bool IsEmpty(void) const;
                IniEntryList SectionEntriesGet(void) const;
                void SectionEntriesSet(const IniEntryList &SectionEntries);
                void sort(void);
                std::string to_string(void) const override;
                void Accept(IIniVisitor &visitor) const;
                void ImplicitGlobalSet(const bool IsImplicitGlobal);
                bool IsImplicitGlobal(void) const;

            private:
                IniEntryList m_Entries;
                std::string m_SectionComment;
                std::string m_SectionName;
                bool m_IsImplicitGlobal;
            };

            using IniSectionPtr = std::shared_ptr<IniSection>;

            bool IniSectionCompare(const IniSectionPtr Left, const IniSectionPtr Right);
        }
    }
}

#endif
