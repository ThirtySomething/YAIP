#pragma once

#include "main_fixtures.h"

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
