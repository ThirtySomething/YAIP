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

#pragma once

#include "YAIP++.h"

/**
 * Base class for fixtures and tests
 */
class YAIPTestFixtureBase
{
public:
	/**
	 * Instance of INI parser
	 */
	net::derpaul::yaip::YAIP IniParser;

	/**
	 * Name of sample INI file
	 */
	static const std::string INIFilename;

	/**
	 * Name of section
	 */
	static const std::string Section;

	/**
	 * Name of key for bool
	 */
	static const std::string KeyBool;

	/**
	 * Name of key for double
	 */
	static const std::string KeyDouble;

	/**
	 * Name of key for float
	 */
	static const std::string KeyFloat;

	/**
	 * Name of key for integer
	 */
	static const std::string KeyInteger;

	/**
	 * Name of key for long
	 */
	static const std::string KeyLong;

	/**
	 * Name of key for string
	 */
	static const std::string KeyString;

	/**
	 * Default Constructor for initialization
	 */
	YAIPTestFixtureBase(void);
};

/**
 * Class for fixtures and tests for saving data
 */
class YAIPTestFixtureSave : public YAIPTestFixtureBase
{
public:
	/**
	 * Value for bool
	 */
	static const bool ValueBool;

	/**
	 * Value for double
	 */
	static const double ValueDouble;

	/**
	 * Value for float
	 */
	static const float ValueFloat;

	/**
	 * Value for integer
	 */
	static const int ValueInteger;

	/**
	 * Value for long
	 */
	static const long ValueLong;

	/**
	 * Value for string
	 */
	static const std::string ValueString;

	/**
	 * Default Constructor for initialization
	 */
	YAIPTestFixtureSave(void);
};

/**
 * Class for fixtures and tests for loading data
 */
class YAIPTestFixtureLoad : public YAIPTestFixtureSave
{
public:
	/**
	 * Default value for bool
	 */
	static const bool DefaultBool;

	/**
	 * Default value for double
	 */
	static const double DefaultDouble;

	/**
	 * Default value for float
	 */
	static const float DefaultFloat;

	/**
	 * Default value for integer
	 */
	static const int DefaultInteger;

	/**
	 * Default value for long
	 */
	static const long DefaultLong;

	/**
	 * Default value for string
	 */
	static const std::string DefaultString;

	/**
	 * Default Constructor for initialization
	 */
	YAIPTestFixtureLoad(void);
};

/**
 * Class for fixtures and tests for reading section list
 */
class YAIPTestFixtureSectionList : public YAIPTestFixtureBase
{
public:
	/**
	 * Default Constructor for initialization
	 */
	YAIPTestFixtureSectionList(void);
};

/**
 * Class for fixtures and tests for reading section key list
 */
class YAIPTestFixtureSectionKeyList : public YAIPTestFixtureBase
{
public:
	/**
	 * Default Constructor for initialization
	 */
	YAIPTestFixtureSectionKeyList(void);
};

/**
 * Class for fixtures and tests for removing section key
 */
class YAIPTestFixtureSectionKeyKill : public YAIPTestFixtureBase
{
public:
	/**
	 * Default Constructor for initialization
	 */
	YAIPTestFixtureSectionKeyKill(void);
};

/**
 * Class for fixtures and tests for removing section
 */
class YAIPTestFixtureSectionKill : public YAIPTestFixtureBase
{
public:
	/**
	 * Default Constructor for initialization
	 */
	YAIPTestFixtureSectionKill(void);
};
