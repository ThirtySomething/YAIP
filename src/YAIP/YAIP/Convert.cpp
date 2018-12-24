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
			const std::string Convert::StringTrue = "true";
			const std::string Convert::StringFalse = "false";

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const bool &Value, std::string &ValueString)
			{
				ValueString = Convert::StringFalse;
				if (Value)
				{
					ValueString = Convert::StringTrue;
				}
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, bool &Value)
			{
				Value = false;
				if (0 == ValueString.compare(Convert::StringTrue))
				{
					Value = true;
				}
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const char &Value, std::string &ValueString)
			{
				ValueString = Value;
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, char &Value)
			{
				if (0 < ValueString.length())
				{
					Value = ValueString[0];
				}
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const double &Value, std::string &ValueString)
			{
				typedef std::numeric_limits<double> Limits;
				std::ostringstream StringStream;
				StringStream << std::setprecision(Limits::max_digits10) << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, double &Value)
			{
				Value = std::stod(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const float &Value, std::string &ValueString)
			{
				typedef std::numeric_limits<float> Limits;
				std::ostringstream StringStream;
				StringStream << std::setprecision(Limits::max_digits10) << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, float &Value)
			{
				Value = std::stof(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const int &Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, int &Value)
			{
				Value = static_cast<int>(std::stoll(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const long &Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, long &Value)
			{
				Value = static_cast<long>(std::stoll(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const short &Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, short &Value)
			{
				Value = static_cast<short>(std::stoll(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const unsigned char &Value, std::string &ValueString)
			{
				ValueString = Value;
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, unsigned char &Value)
			{
				if (0 < ValueString.length())
				{
					Value = ValueString[0];
				}
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const unsigned int &Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, unsigned int &Value)
			{
				Value = static_cast<unsigned int>(std::stoul(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const unsigned long &Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, unsigned long &Value)
			{
				Value = static_cast<unsigned long>(std::stoul(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const unsigned short &Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(const std::string &ValueString, unsigned short &Value)
			{
				Value = static_cast<unsigned short>(std::stoul(ValueString));
			}
		}
	}
}
