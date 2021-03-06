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
 * \file	string_extensions.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Extensions to std::string
 */
#include "string_extensions.h"
#include <iostream>
#include <algorithm>
#include <cstring>

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
			// ******************************************************************
			// ******************************************************************
			std::string ltrim(const std::string& in)
			{
				size_t start = in.find_first_not_of(WHITESPACE);
				return (start == std::string::npos) ? "" : in.substr(start);
			}

			// ******************************************************************
			// ******************************************************************
			std::string rtrim(const std::string& in)
			{
				size_t end = in.find_last_not_of(WHITESPACE);
				return (end == std::string::npos) ? "" : in.substr(0, end + 1);
			}

			// ******************************************************************
			// ******************************************************************
			bool strcmpcaseless(const std::string& left, const std::string& right)
			{
				return std::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end(), [](char first, char second)
					{
						return tolower(first) < tolower(second);
					});
			}

			// ******************************************************************
			// ******************************************************************
			std::string trim(const std::string& in)
			{
				return rtrim(ltrim(in));
			}
		}
	}
}
