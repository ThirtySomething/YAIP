#pragma once

#include "YAIP++.h"
#include "main_fixtures.h"
#include <sys/stat.h>

#define CATCH_CONFIG_MAIN
#include "./../externals/Catch/single_include/catch.hpp"

TEST_CASE_METHOD(YAIPTestFixtureSave, "Create sample INI file", "[save]")
{
	struct stat FileDataRaw;

	CHECK(IniParser.SectionKeyValueSet(Section, KeyBool, ValueBool));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyDouble, ValueDouble));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyInteger, ValueInt));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyString, ValueString));
	CHECK(IniParser.INIFileSave(INIFilename));
	CHECK(0 == stat(INIFilename.c_str(), &FileDataRaw));
}

TEST_CASE_METHOD(YAIPTestFixtureLoad, "Load sample INI file", "[load]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));

	bool ResultBool = IniParser.SectionKeyValueGet(Section, KeyBool, DefaultBool);
	CHECK(ResultBool != DefaultBool);
	CHECK(ResultBool == ValueBool);

	double ResultDouble = IniParser.SectionKeyValueGet(Section, KeyDouble, DefaultDouble);
	CHECK(ResultDouble != DefaultDouble);
	CHECK(ResultDouble == ValueDouble);

	int ResultInt = IniParser.SectionKeyValueGet(Section, KeyInteger, DefaultInt);
	CHECK(ResultInt != DefaultInt);
	CHECK(ResultInt == ValueInt);

	std::string ResultString = IniParser.SectionKeyValueGet(Section, KeyString, DefaultString);
	CHECK(0 != ResultString.compare(DefaultString));
	CHECK(0 == ResultString.compare(ValueString));
}

TEST_CASE_METHOD(YAIPTestFixtureSectionList, "Get section list", "[sectionlist]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	std::vector<std::string> SectionList = IniParser.SectionListGet();

	auto ResultSection = std::find(std::begin(SectionList), std::end(SectionList), Section);
	CHECK(ResultSection != std::end(SectionList));
}

TEST_CASE_METHOD(YAIPTestFixtureSectionKeyList, "Get section key list", "[sectionkeylist]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

	auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), KeyBool);
	CHECK(ResultBool != std::end(KeyList));

	auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), KeyDouble);
	CHECK(ResultDouble != std::end(KeyList));

	auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), KeyInteger);
	CHECK(ResultInt != std::end(KeyList));

	auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), KeyString);
	CHECK(ResultString != std::end(KeyList));
}

TEST_CASE_METHOD(YAIPTestFixtureSectionKeyKill, "Kill section key", "[sectionkeykill]")
{
	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyBool);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), KeyBool);
		CHECK(ResultBool == std::end(KeyList));

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), KeyDouble);
		CHECK(ResultDouble != std::end(KeyList));

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), KeyInteger);
		CHECK(ResultInt != std::end(KeyList));

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), KeyString);
		CHECK(ResultString != std::end(KeyList));
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyDouble);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), KeyBool);
		CHECK(ResultBool != std::end(KeyList));

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), KeyDouble);
		CHECK(ResultDouble == std::end(KeyList));

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), KeyInteger);
		CHECK(ResultInt != std::end(KeyList));

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), KeyString);
		CHECK(ResultString != std::end(KeyList));
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyInteger);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), KeyBool);
		CHECK(ResultBool != std::end(KeyList));

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), KeyDouble);
		CHECK(ResultDouble != std::end(KeyList));

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), KeyInteger);
		CHECK(ResultInt == std::end(KeyList));

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), KeyString);
		CHECK(ResultString != std::end(KeyList));
	}

	{
		CHECK(IniParser.INIFileLoad(INIFilename));
		IniParser.SectionKeyKill(Section, KeyString);
		std::vector<std::string> KeyList = IniParser.SectionKeyListGet(Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), KeyBool);
		CHECK(ResultBool != std::end(KeyList));

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), KeyDouble);
		CHECK(ResultDouble != std::end(KeyList));

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), KeyInteger);
		CHECK(ResultInt != std::end(KeyList));

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), KeyString);
		CHECK(ResultString == std::end(KeyList));
	}
}

TEST_CASE_METHOD(YAIPTestFixtureSectionKill, "Kill section", "[sectionkill]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	IniParser.SectionKill(Section);
	std::vector<std::string> SectionList = IniParser.SectionListGet();

	auto ResultSection = std::find(std::begin(SectionList), std::end(SectionList), Section);
	CHECK(ResultSection == std::end(SectionList));
}
