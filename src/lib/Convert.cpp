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
 * \file	Convert.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Converter between different datatypes and std::string
 */
#include "Convert.h"
#include <sstream>
#include <iomanip>
#include <limits>
#include <type_traits>

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
			namespace
			{
				template <typename T>
				std::string NumericToString(const T &Value)
				{
					std::ostringstream StringStream;
					StringStream << Value;
					return StringStream.str();
				}

				template <typename T>
				std::string FloatingToString(const T &Value)
				{
					typedef std::numeric_limits<T> Limits;
					std::ostringstream StringStream;
					StringStream << std::setprecision(Limits::max_digits10) << std::scientific << Value;
					return StringStream.str();
				}

				template <typename T>
				T ParseFromString(const std::string &ValueString)
				{
					if constexpr (std::is_same_v<T, bool>)
					{
						return (0 == ValueString.compare(Convert::StringTrue));
					}
					else if constexpr (std::is_same_v<T, char>)
					{
						if (0 < ValueString.length())
						{
							return ValueString[0];
						}
						return T{};
					}
					else if constexpr (std::is_same_v<T, unsigned char>)
					{
						if (0 < ValueString.length())
						{
							return static_cast<unsigned char>(ValueString[0]);
						}
						return T{};
					}
					else if constexpr (std::is_same_v<T, double>)
					{
						return std::stod(ValueString);
					}
					else if constexpr (std::is_same_v<T, float>)
					{
						return std::stof(ValueString);
					}
					else if constexpr (std::is_same_v<T, int>)
					{
						return static_cast<int>(std::stoll(ValueString));
					}
					else if constexpr (std::is_same_v<T, long>)
					{
						return static_cast<long>(std::stoll(ValueString));
					}
					else if constexpr (std::is_same_v<T, short>)
					{
						return static_cast<short>(std::stoll(ValueString));
					}
					else if constexpr (std::is_same_v<T, unsigned int>)
					{
						return static_cast<unsigned int>(std::stoul(ValueString));
					}
					else if constexpr (std::is_same_v<T, unsigned long>)
					{
						return static_cast<unsigned long>(std::stoul(ValueString));
					}
					else if constexpr (std::is_same_v<T, unsigned short>)
					{
						return static_cast<unsigned short>(std::stoul(ValueString));
					}
					else
					{
						return ValueString;
					}
				}
			}

			// ******************************************************************
			// ******************************************************************
			const std::string Convert::StringTrue = "true";
			const std::string Convert::StringFalse = "false";

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const ConvertValue &Value, std::string &ValueString)
			{
				ValueString = std::visit([](const auto &TypedValue) -> std::string {
					using T = std::decay_t<decltype(TypedValue)>;
					if constexpr (std::is_same_v<T, bool>)
					{
						return TypedValue ? Convert::StringTrue : Convert::StringFalse;
					}
					else if constexpr (std::is_same_v<T, char>)
					{
						return std::string(1, TypedValue);
					}
					else if constexpr (std::is_same_v<T, unsigned char>)
					{
						return std::string(1, static_cast<char>(TypedValue));
					}
					else if constexpr (std::is_same_v<T, float> || std::is_same_v<T, double>)
					{
						return FloatingToString(TypedValue);
					}
					else if constexpr (std::is_same_v<T, std::string>)
					{
						return TypedValue;
					}
					else
					{
						return NumericToString(TypedValue);
					}
				}, Value);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, ConvertValue &Value)
			{
				std::visit([&ValueString](auto &TypedValue) {
					using T = std::decay_t<decltype(TypedValue)>;
					TypedValue = ParseFromString<T>(ValueString);
				}, Value);
			}
		}
	}
}
