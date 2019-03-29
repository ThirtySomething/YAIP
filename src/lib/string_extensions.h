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
 * \file	string_extensions.h
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Extensions to std::string
 */
#ifndef _STRING_EXTENSIONS_H_
#define _STRING_EXTENSIONS_H_

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
			 * Defined whitepaces to trim
			 */
			const std::string WHITESPACE = " \n\r\t\f\v";

			/**
			 * Trim whitespaces from left side of string
			 * \param in String to trim
			 * \return Trimmed string
			 */
			std::string ltrim(const std::string& in);

			/**
			 * Trim whitespaces from right side of string
			 * \param in String to trim
			 * \return Trimmed string
			 */
			std::string rtrim(const std::string& in);

			/**
			 * Compare two strings case insensitive
			 * \param left Left string
			 * \param right Right string
			 * \return True on equal, otherwise false
			 */
			bool strcmpcaseless(const std::string& left, const std::string& right);

			/**
			 * Trim whitespaces from both sides of string
			 * \param in String to trim
			 * \return Trimmed string
			 */
			std::string trim(const std::string& in);
		}
	}
}

#endif // _STRING_EXTENSIONS_H_
