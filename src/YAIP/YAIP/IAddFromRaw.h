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
 * \file	IAddFromRaw.h
 * \author	ThirtySomething
 * \date	2016-11-06
 * \brief	Interface for INI elements to add from raw data
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
			 * Interface for INI objects to parse data from string
			 */
			class IAddFromRaw
			{
			public:
				/**
				 * Will transform string into internal properties
				 * \param RawData string from INI file to transform
				 * \return true on success, otherwise false
				 */
				virtual bool CreateFromRawData(const std::string &RawData) = 0;
			};
		}
	}
}
