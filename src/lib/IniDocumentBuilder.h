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
 * \file    IniDocumentBuilder.h
 * \author  ThirtySomething
 * \brief   Fluent builder for constructing an INI document programmatically
 */
#ifndef _INIDOCUMENTBUILDER_H_
#define _INIDOCUMENTBUILDER_H_

#include "Convert.h"
#include "IniSection.h"
#include <memory>
#include <string>
#include <vector>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            class YAIP;

            /**
             * Fluent builder that assembles sections and key/value entries and
             * then populates a YAIP instance via build().
             *
             * Usage:
             * @code
             *   YAIP ini;
             *   IniDocumentBuilder{}
             *       .section("Database")
             *           .entry("host", "localhost")
             *           .entry("port", 5432)
             *       .section("Auth")
             *           .entry("user", "admin")
             *       .build(ini);
             * @endcode
             */
            class IniDocumentBuilder
            {
            public:
                /**
                 * Start (or continue) a named section.
                 * All subsequent entry() calls go into this section.
                 * \param name  Section name
                 * \return Reference to this builder for chaining
                 */
                IniDocumentBuilder &section(const std::string &name);

                /**
                 * Add a string key/value entry to the current section.
                 * \param key   Entry key
                 * \param value Entry value
                 * \return Reference to this builder for chaining
                 */
                IniDocumentBuilder &entry(const std::string &key, const std::string &value);

                /**
                 * Overload to prevent implicit C-string → bool conversion in the
                 * templated entry() below.
                 * \param key   Entry key
                 * \param value Entry value as C-string literal
                 * \return Reference to this builder for chaining
                 */
                IniDocumentBuilder &entry(const std::string &key, const char *value);

                /**
                 * Add a typed key/value entry to the current section.
                 * The value is converted to a string via Convert::ConvertTo.
                 * \param key   Entry key
                 * \param value Entry value of any type supported by Convert
                 * \return Reference to this builder for chaining
                 */
                template <typename T>
                IniDocumentBuilder &entry(const std::string &key, const T &value)
                {
                    std::string converted;
                    Convert::ConvertTo(value, converted);
                    return entry(key, converted);
                }

                /**
                 * Populate the given YAIP instance with all accumulated sections
                 * and entries.  Existing content in the target is cleared first.
                 * \param target  YAIP instance to populate
                 */
                void build(YAIP &target) const;

            private:
                std::vector<IniSectionPtr> m_Sections;
            };
        }
    }
}

#endif
