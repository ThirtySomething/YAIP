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
 * \file    Convert.h
 * \author  ThirtySomething
 * \date    2016-09-19
 * \brief   Converter between different datatypes and std::string
 */
#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <string>
#include <variant>

 /**
  * Namespace of YAIP
  */
namespace net
{
    /**
     * Namespace of YAIP
     */
    namespace derpaul
    {
        /**
         * Namespace of YAIP
         */
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

            /**
             * Class to convert data from and to std::string using std::variant
             * \see http://en.cppreference.com/w/cpp/language/types
             * <table>
             * <caption id="multi_row">Fundamental types</caption>
             * <tr><th>Type</th><th>Done</th></tr>
             * <tr><td>bool</td><td>x</td></tr>
             * <tr><td>char</td><td>x</td></tr>
             * <tr><td>double</td><td>x</td></tr>
             * <tr><td>float</td><td>x</td></tr>
             * <tr><td>int</td><td>x</td></tr>
             * <tr><td>long</td><td>x</td></tr>
             * <tr><td>short</td><td>x</td></tr>
             * <tr><td>std::string</td><td>x</td></tr>
             * <tr><td>unsigned char</td><td>x</td></tr>
             * <tr><td>unsigned int</td><td>x</td></tr>
             * <tr><td>unsigned long</td><td>x</td></tr>
             * <tr><td>unsigned short</td><td>x</td></tr>
             * </table>
             */
            class Convert
            {
            public:
                /**
                 * Used as constant for bool
                 */
                static const std::string StringTrue;

                /**
                 * Used as constant for bool
                 */
                static const std::string StringFalse;

                /**
                 * Convert a variant value to std::string.
                 * \param Value Value to convert from
                 * \param ValueString Value to convert to
                 */
                static void ConvertTo(const ConvertValue &Value, std::string &ValueString);

                /**
                 * Convert std::string to the active type stored in the variant.
                 * \param ValueString Value to convert from
                 * \param Value Variant with target type as active alternative
                 */
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
