//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************
// This file is part of YAIP++.
//
// YAIP++ is free software: you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// YAIP++ is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with YAIP++. If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************

/**
 * \file	Convert.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Converter between different datatypes and std::string
 */
#pragma once

#include <string>

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
			/**
			 * Class to convert data from and to std::string
			 * \todo Add converters for all fundamental types:
			 * \see http://en.cppreference.com/w/cpp/language/types
			 * <table>
			 * <caption id="multi_row">Fundamental types</caption>
			 * <tr><th>Type</th><th>Done</th></tr>
			 * <tr><td>bool</td><td>x</td></tr>
			 * <tr><td>int</td><td>x</td></tr>
			 * <tr><td>unsigned int</td><td>-</td>x</tr>
			 * <tr><td>short</td><td>-</td></tr>
			 * <tr><td>unsigned short</td><td>-</td></tr>
			 * <tr><td>long</td><td>-</td></tr>
			 * <tr><td>unsigned long</td><td>-</td></tr>
			 * <tr><td>long long</td><td>-</td></tr>
			 * <tr><td>unsigned long long</td><td>-</td></tr>
			 * <tr><td>char</td><td>-</td></tr>
			 * <tr><td>unsigned char</td><td>-</td></tr>
			 * <tr><td>float</td><td>x</td></tr>
			 * <tr><td>double</td><td>x</td></tr>
			 * <tr><td>long double</td><td>-</td></tr>
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
				 * Convert integer to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(int Value, std::string &ValueString);

				/**
				 * Convert unsigned integer to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(unsigned int Value, std::string &ValueString);

				/**
				 * Convert long to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(long Value, std::string &ValueString);

				/**
				 * Convert unsigned long to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(unsigned long Value, std::string &ValueString);

				/**
				 * Convert float to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(float Value, std::string &ValueString);

				/**
				 * Convert double to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(double Value, std::string &ValueString);

				/**
				 * Convert bool to std::string
				 * \param Value Value to convert from
				 * \param ValueString Value to convert to
				 */
				static void ConvertTo(bool Value, std::string &ValueString);

				/**
				 * Convert std::string to int
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, int &Value);

				/**
				 * Convert std::string to unsigned int
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, unsigned int &Value);

				/**
				 * Convert std::string to long
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, long &Value);

				/**
				 * Convert std::string to unsigned long
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, unsigned long &Value);

				/**
				 * Convert std::string to float
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, float &Value);

				/**
				 * Convert std::string to double
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, double &Value);

				/**
				 * Convert std::string to bool
				 * \param ValueString Value to convert from
				 * \param Value Value to convert to
				 */
				static void ConvertTo(std::string ValueString, bool &Value);
			};
		}
	}
}
