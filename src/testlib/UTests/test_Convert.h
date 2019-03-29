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

#ifndef _TEST_CONVERT_H_
#define _TEST_CONVERT_H_

#include "catch2\catch.hpp"
#include "Convert.h"
#include <limits>

template <typename T>
void test_signed(const std::string &dataType)
{
	INFO("Test conversion of [" + dataType + "]");
	std::string value_string;
	T value_numeric;

	// Numeric value to string
	value_numeric = -1;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("-1" == value_string);

	value_numeric = 0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("0" == value_string);

	value_numeric = 1;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("1" == value_string);

	// String to numeric value
	value_string = "-1";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(-1 == value_numeric);

	value_string = "0";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(0 == value_numeric);

	value_string = "1";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(1 == value_numeric);
}

template <typename T>
void test_unsigned(const std::string &dataType)
{
	INFO("Test conversion of [" + dataType + "]");
	std::string value_string;
	T value_numeric;

	// Numeric value to string
	value_numeric = 0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("0" == value_string);

	value_numeric = 1;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("1" == value_string);

	// String to numeric value
	value_string = "0";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(0 == value_numeric);

	value_string = "1";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(1 == value_numeric);
}

template <typename T>
void test_characters(const std::string &dataType)
{
	INFO("Test conversion of [" + dataType + "]");
	std::string value_string;
	T value_char;

	// Character value to string
	value_char = 'A';
	net::derpaul::yaip::Convert::ConvertTo(value_char, value_string);
	REQUIRE("A" == value_string);

	value_char = 'Z';
	net::derpaul::yaip::Convert::ConvertTo(value_char, value_string);
	REQUIRE("Z" == value_string);

	// String to character value
	value_string = "A";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_char);
	REQUIRE('A' == value_char);

	value_string = "Z";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_char);
	REQUIRE('Z' == value_char);
}

void test_float(void)
{
	INFO("Test conversion of [float]");
	std::string value_string;
	float value_numeric;

	// Numeric value to string
	value_numeric = -1.0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("-1.000000000e+00" == value_string);

	value_numeric = 0.0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("0.000000000e+00" == value_string);

	value_numeric = 1.0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("1.000000000e+00" == value_string);

	// String to numeric value
	value_string = "-1.000000000e+00";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(-1.0 == Approx(value_numeric));

	value_string = "-0.000000000e+00";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(0.0 == Approx(value_numeric));

	value_string = "1.000000000e+00";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(1.0 == Approx(value_numeric));
}

void test_double(void)
{
	INFO("Test conversion of [double]");
	std::string value_string;
	double value_numeric;

	// Numeric value to string
	value_numeric = -1.0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("-1.00000000000000000e+00" == value_string);

	value_numeric = 0.0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("0.00000000000000000e+00" == value_string);

	value_numeric = 1.0;
	net::derpaul::yaip::Convert::ConvertTo(value_numeric, value_string);
	REQUIRE("1.00000000000000000e+00" == value_string);

	// String to numeric value
	value_string = "-1.00000000000000000e+00";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(-1.0 == Approx(value_numeric));

	value_string = "0.00000000000000000e+00";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(0.0 == Approx(value_numeric));

	value_string = "1.00000000000000000e+00";
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_numeric);
	REQUIRE(1.0 == Approx(value_numeric));
}

void test_bool(void)
{
	INFO("Test conversion of [bool]");
	std::string value_string;
	bool value_bool = true;

	// Bool value to string
	net::derpaul::yaip::Convert::ConvertTo(value_bool, value_string);
	REQUIRE(net::derpaul::yaip::Convert::StringTrue == value_string);

	value_bool = false;
	net::derpaul::yaip::Convert::ConvertTo(value_bool, value_string);
	REQUIRE(net::derpaul::yaip::Convert::StringFalse == value_string);

	// String to bool value
	value_string = net::derpaul::yaip::Convert::StringTrue;
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_bool);
	REQUIRE(value_bool);

	value_string = net::derpaul::yaip::Convert::StringFalse;
	net::derpaul::yaip::Convert::ConvertTo(value_string, value_bool);
	REQUIRE(false == value_bool);
}

SCENARIO("Test class Convert", "[Convert]")
{
	// Templated tests for numeric datatypes with no fraction
	// int
	test_signed<int>("int");

	// unsigned int
	test_unsigned<unsigned int>("unsigned int");

	// short
	test_signed<short>("short");

	// unsigned short
	test_unsigned<unsigned short>("unsigned short");

	// long
	test_signed<long>("long");

	// unsigned long
	test_unsigned<unsigned long>("unsigned long");

	// Templated tests for character datatypes
	// char
	test_characters<char>("char");

	// unsigned char
	test_characters<unsigned char>("unsigned char");

	// Tests for numeric datatypes with fraction
	// float
	test_float();

	// double
	test_double();

	// Other tests
	// bool
	test_bool();
}

#endif // _TEST_CONVERT_H_