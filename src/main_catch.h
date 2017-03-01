#pragma once

#include "YAIP++.h"
#include "main_fixtures.h"
#include <sys/stat.h>

#define CATCH_CONFIG_MAIN
#include "./../externals/Catch/single_include/catch.hpp"

/**
 * Helper method: vector contains given value
 * \param KeyList Vector of strings
 * \param Value Value to search for
 */
template <typename T>
void VectorCompareExist(const std::vector<std::string> &KeyList, const std::string &Value)
{
	auto ResultValue = std::find(std::begin(KeyList), std::end(KeyList), Value);
	CHECK((ResultValue != std::end(KeyList)));
}

/**
 * Helper method: vector does not contain given value
 * \param KeyList Vector of strings
 * \param Value Value to search for
 */
template <typename T>
void VectorCompareExistNot(const std::vector<std::string> &KeyList, const std::string &Value)
{
	auto ResultValue = std::find(std::begin(KeyList), std::end(KeyList), Value);
	CHECK((ResultValue == std::end(KeyList)));
}

/**
 * Templated method to check correct read of value
 * \param Parser Reference to INI parser
 * \param Section The section name
 * \param Key The key name
 * \param Default Default value
 * \param Value Expected value
 */
template <typename T>
void TestKeyValue(org::derpaul::yaip::YAIP &Parser, const std::string &Section, const std::string &Key, const T &Default, const T &Value)
{
	T ResultValue = Parser.SectionKeyValueGet(Section, Key, Default);
	CHECK((ResultValue != Default));
	CHECK((ResultValue == Value));
}

TEST_CASE_METHOD(YAIPTestFixtureSave, "Create sample INI file", "[save]")
{
	struct stat FileDataRaw;

	CHECK(IniParser.SectionKeyValueSet(Section, KeyBool, ValueBool));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyDouble, ValueDouble));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyFloat, ValueFloat));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyInteger, ValueInteger));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyLong, ValueLong));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyString, ValueString));
	CHECK(IniParser.INIFileSave(INIFilename));
	CHECK(0 == stat(INIFilename.c_str(), &FileDataRaw));
}

TEST_CASE_METHOD(YAIPTestFixtureLoad, "Load sample INI file", "[load]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));

	TestKeyValue(IniParser, Section, KeyBool, DefaultBool, ValueBool);
	TestKeyValue(IniParser, Section, KeyDouble, DefaultDouble, ValueDouble);
	TestKeyValue(IniParser, Section, KeyFloat, DefaultFloat, ValueFloat);
	TestKeyValue(IniParser, Section, KeyInteger, DefaultInteger, ValueInteger);
	TestKeyValue(IniParser, Section, KeyLong, DefaultLong, ValueLong);
	TestKeyValue(IniParser, Section, KeyString, DefaultString, ValueString);
}

TEST_CASE_METHOD(YAIPTestFixtureSectionList, "Get section list", "[sectionlist]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	std::vector<std::string> SectionList = IniParser.SectionListGet();

	VectorCompareExist<std::string>(SectionList, Section);
}

TEST_CASE_METHOD(YAIPTestFixtureSectionKeyList, "Get section key list", "[sectionkeylist]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

	VectorCompareExist<bool>(KeyList, KeyBool);
	VectorCompareExist<double>(KeyList, KeyDouble);
	VectorCompareExist<float>(KeyList, KeyFloat);
	VectorCompareExist<int>(KeyList, KeyInteger);
	VectorCompareExist<long>(KeyList, KeyLong);
	VectorCompareExist<std::string>(KeyList, KeyString);
}

TEST_CASE_METHOD(YAIPTestFixtureSectionKeyKill, "Kill section key", "[sectionkeykill]")
{
	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyBool);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		VectorCompareExistNot<bool>(KeyList, KeyBool);
		VectorCompareExist<double>(KeyList, KeyDouble);
		VectorCompareExist<float>(KeyList, KeyFloat);
		VectorCompareExist<int>(KeyList, KeyInteger);
		VectorCompareExist<long>(KeyList, KeyLong);
		VectorCompareExist<std::string>(KeyList, KeyString);
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyDouble);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		VectorCompareExist<bool>(KeyList, KeyBool);
		VectorCompareExistNot<double>(KeyList, KeyDouble);
		VectorCompareExist<float>(KeyList, KeyFloat);
		VectorCompareExist<int>(KeyList, KeyInteger);
		VectorCompareExist<long>(KeyList, KeyLong);
		VectorCompareExist<std::string>(KeyList, KeyString);
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyFloat);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		VectorCompareExist<bool>(KeyList, KeyBool);
		VectorCompareExist<double>(KeyList, KeyDouble);
		VectorCompareExistNot<float>(KeyList, KeyFloat);
		VectorCompareExist<int>(KeyList, KeyInteger);
		VectorCompareExist<long>(KeyList, KeyLong);
		VectorCompareExist<std::string>(KeyList, KeyString);
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyInteger);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		VectorCompareExist<bool>(KeyList, KeyBool);
		VectorCompareExist<double>(KeyList, KeyDouble);
		VectorCompareExist<float>(KeyList, KeyFloat);
		VectorCompareExistNot<int>(KeyList, KeyInteger);
		VectorCompareExist<long>(KeyList, KeyLong);
		VectorCompareExist<std::string>(KeyList, KeyString);
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyLong);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		VectorCompareExist<bool>(KeyList, KeyBool);
		VectorCompareExist<double>(KeyList, KeyDouble);
		VectorCompareExist<float>(KeyList, KeyFloat);
		VectorCompareExist<int>(KeyList, KeyInteger);
		VectorCompareExistNot<long>(KeyList, KeyLong);
		VectorCompareExist<std::string>(KeyList, KeyString);
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyString);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		VectorCompareExist<bool>(KeyList, KeyBool);
		VectorCompareExist<double>(KeyList, KeyDouble);
		VectorCompareExist<float>(KeyList, KeyFloat);
		VectorCompareExist<int>(KeyList, KeyInteger);
		VectorCompareExist<long>(KeyList, KeyLong);
		VectorCompareExistNot<std::string>(KeyList, KeyString);
	}
}

TEST_CASE_METHOD(YAIPTestFixtureSectionKill, "Kill section", "[sectionkill]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	IniParser.SectionKill(Section);
	std::vector<std::string> SectionList = IniParser.SectionListGet();

	VectorCompareExistNot<std::string>(SectionList, Section);
}
