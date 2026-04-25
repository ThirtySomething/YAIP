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

#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <string>
#include <variant>

namespace net
{
    namespace derpaul
    {
        namespace yaip
        {
            using ConvertValue = std::variant<bool,
                                              char,
                                              double,
                                              float,
                                              int,
                                              long,
                                              short,
                                              std::string,
                                              unsigned char,
                                              unsigned int,
                                              unsigned long,
                                              unsigned short>;

            class Convert
            {
            public:
                static const std::string StringTrue;
                static const std::string StringFalse;

                static void ConvertTo(const ConvertValue &Value, std::string &ValueString);
                static void ConvertTo(const std::string &ValueString, ConvertValue &Value);

                template <typename T>
                static void ConvertTo(const T &Value, std::string &ValueString)
                {
                    ConvertValue VariantValue = Value;
                    ConvertTo(VariantValue, ValueString);
                }

                template <typename T>
                static void ConvertTo(const std::string &ValueString, T &Value)
                {
                    ConvertValue VariantValue = T{};
                    ConvertTo(ValueString, VariantValue);
                    Value = std::get<T>(VariantValue);
                }
            };
        }
    }
}

#endif
