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

/**
 * \file    IIniVisitor.h
 * \author  ThirtySomething
 * \brief   Visitor interface for traversing YAIP documents
 */
#ifndef _IINIVISITOR_H_
#define _IINIVISITOR_H_

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class YAIP;
            class IniSection;
            class IniEntry;

            class IIniVisitor
            {
            public:
                virtual ~IIniVisitor() = default;

                virtual void VisitDocumentBegin(const YAIP &document) = 0;
                virtual void VisitSectionBegin(const IniSection &section) = 0;
                virtual void VisitEntry(const IniEntry &entry) = 0;
                virtual void VisitSectionEnd(const IniSection &section) = 0;
                virtual void VisitDocumentEnd(const YAIP &document) = 0;
            };
        }
    }
}

#endif