#pragma once

#include "main_fixtures.h"
#include <iostream>

/**
 * Simple function to display content of INI file
 * \param IniParser An instance of YAIP
 * \param Comment A remark printed on top
 */
void DisplayINI(org::derpaul::yaip::YAIP &IniParser, std::string &Comment);

/**
 * Test for saving an INI file
 * \param TestName Name of test to pass DisplayINI
 * \param INIFilename Name of INI file
 */
void TestSave(std::string TestName, std::string INIFilename);

/**
 * Test for loading an INI file
 * \param TestName Name of test to pass DisplayINI
 * \param INIFilename Name of INI file
 */
void TestLoad(std::string TestName, std::string INIFilename);

/**
 * Test for listing of all sections of INI file
 * \param TestName Name of test to pass DisplayINI
 * \param INIFilename Name of INI file
 */
void TestSectionList(std::string TestName, std::string INIFilename);

/**
 * Test for listing of all keys of a sections of INI file
 * \param TestName Name of test to pass DisplayINI
 * \param INIFilename Name of INI file
 */
void TestSectionKeyList(std::string TestName, std::string INIFilename);

/**
 * Test for deleting a key of a section of INI file
 * \param TestName Name of test to pass DisplayINI
 * \param INIFilename Name of INI file
 */
void TestSectionKeyKill(std::string TestName, std::string INIFilename);

/**
 * Test for deleting a section of INI file
 * \param TestName Name of test to pass DisplayINI
 * \param INIFilename Name of INI file
 */
void TestSectionKill(std::string TestName, std::string INIFilename);

/**
 * Helper method: vector contains given value
 * \param KeyList Vector of strings
 * \param Value Value to search for
 * \param Message Error message to print
 */
void VectorCompareExist(const std::vector<std::string> &KeyList, const std::string &Value, const std::string &Message);

/**
 * Helper method: vector does not contain given value
 * \param KeyList Vector of strings
 * \param Value Value to search for
 * \param Message Error message to print
 */
void VectorCompareExistNot(const std::vector<std::string> &KeyList, const std::string &Value, const std::string &Message);

/**
 * Templated method to check correct read of value
 * \param Parser Reference to INI parser
 * \param Section The section name
 * \param Key The key name
 * \param Default Default value
 * \param Value Expected value
 * \param Message Error message to print
 */
template <typename T>
void TestKeyValue(org::derpaul::yaip::YAIP &Parser, const std::string &Section, const std::string &Key, const T &Default, const T &Value, const std::string &Message)
{
	T ResultValue = Parser.SectionKeyValueGet(Section, Key, Default);
	if ((ResultValue == Default) ||
		(ResultValue != Value))
	{
		std::cout << Message << std::endl;
	}
}
