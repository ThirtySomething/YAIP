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
 * \file	Convert.cpp
 * \author	ThirtySomething
 * \date	2016-09-19
 * \brief	Converter between different datatypes and std::string
 */
#include "Convert.h"
#include <sstream>
#include <iomanip>

#ifdef __MINGW32__
 // GCC on windows does not support std::to_string
#include <string>
#include <sstream>
#include <stdlib.h>

namespace std
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}

	int stoi(const std::string &s)
	{
		int i = 0;
		sscanf(s.c_str(), "%d", &i);
		return i;
	}

	long stol(const std::string &s)
	{
		long i = 0;
		sscanf(s.c_str(), "%ld", &i);
		return i;
	}

	long long stol(const std::string &s)
	{
		long long i = 0;
		sscanf(s.c_str(), "%I64d", &i);
		return i;
	}

	double stod(const std::string &s)
	{
		double d = 0.0;
		sscanf(s.c_str(), "%lf", &d);
		return d;
	}

	float stof(const std::string &s)
	{
		float f = 0.0;
		sscanf(s.c_str(), "%f", &f);
		return f;
	}
}
#endif // __MINGW32__

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
			void Convert::ConvertTo(int Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(unsigned int Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(long Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(unsigned long Value, std::string &ValueString)
			{
				std::ostringstream StringStream;
				StringStream << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(float Value, std::string &ValueString)
			{
				typedef std::numeric_limits<float> Limits;
				std::ostringstream StringStream;
				StringStream << std::setprecision(Limits::max_digits10) << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(double Value, std::string &ValueString)
			{
				typedef std::numeric_limits<double> Limits;
				std::ostringstream StringStream;
				StringStream << std::setprecision(Limits::max_digits10) << std::scientific << Value;
				ValueString = StringStream.str();
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(bool Value, std::string &ValueString)
			{
				ValueString = Convert::StringFalse;
				if (true == Value)
				{
					ValueString = Convert::StringTrue;
				}
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, int &Value)
			{
				Value = static_cast<int>(std::stoll(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, unsigned int &Value)
			{
				Value = std::stoul(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, long &Value)
			{
				Value = static_cast<long>(std::stoll(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, unsigned long &Value)
			{
				Value = static_cast<unsigned long>(std::stoll(ValueString));
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, double &Value)
			{
				Value = std::stod(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, float &Value)
			{
				Value = std::stof(ValueString);
			}

			// ******************************************************************
			// ******************************************************************
			void Convert::ConvertTo(std::string ValueString, bool &Value)
			{
				Value = false;
				if (0 == ValueString.compare(Convert::StringTrue))
				{
					Value = true;
				}
			}
		}
	}
}
