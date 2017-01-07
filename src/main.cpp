#define CATCH_CONFIG_MAIN
#include "./../externals/Catch/single_include/catch.hpp"
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
	YAIP::YAIP IniParser;

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
	 * Name of key for integer
	 */
	static const std::string KeyInteger;

	/**
	 * Name of key for string
	 */
	static const std::string KeyString;
};

const std::string YAIPTestFixtureBase::INIFilename = "yaip.ini";
const std::string YAIPTestFixtureBase::Section = "Section";
const std::string YAIPTestFixtureBase::KeyBool = "Bool";
const std::string YAIPTestFixtureBase::KeyDouble = "Double";
const std::string YAIPTestFixtureBase::KeyInteger = "Integer";
const std::string YAIPTestFixtureBase::KeyString = "String";

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
	 * Value for integer
	 */
	static const int ValueInt;

	/**
	 * Value for string
	 */
	static const std::string ValueString;
};

const bool YAIPTestFixtureSave::ValueBool = true;
const double YAIPTestFixtureSave::ValueDouble = 1.23;
const int YAIPTestFixtureSave::ValueInt = 123;
const std::string YAIPTestFixtureSave::ValueString = "Value";

TEST_CASE_METHOD(YAIPTestFixtureSave, "Create sample INI file", "[create]")
{
	struct stat FileDataRaw;

	CHECK(IniParser.SectionKeyValueSet(Section, KeyBool, ValueBool));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyDouble, ValueDouble));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyInteger, ValueInt));
	CHECK(IniParser.SectionKeyValueSet(Section, KeyString, ValueString));
	CHECK(IniParser.INIFileSave(INIFilename));
	CHECK(0 == stat(INIFilename.c_str(), &FileDataRaw));
}

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
	 * Default value for integer
	 */
	static const int DefaultInt;

	/**
	 * Default value for string
	 */
	static const std::string DefaultString;
};

const bool YAIPTestFixtureLoad::DefaultBool = false;
const double YAIPTestFixtureLoad::DefaultDouble = 0.0;
const int YAIPTestFixtureLoad::DefaultInt = 0;
const std::string YAIPTestFixtureLoad::DefaultString = "";

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

/**
 * Class for fixtures and tests for reading section list
 */
class YAIPTestFixtureSectionList : public YAIPTestFixtureBase
{
};

TEST_CASE_METHOD(YAIPTestFixtureSectionList, "Get section list", "[sectionlist]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	std::vector<std::string> SectionList = IniParser.SectionListGet();

	auto ResultSection = std::find(std::begin(SectionList), std::end(SectionList), Section);
	CHECK(ResultSection != std::end(SectionList));
}

/**
 * Class for fixtures and tests for reading section key list
 */
class YAIPTestFixtureSectionKeyList : public YAIPTestFixtureBase
{
};

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

/**
 * Class for fixtures and tests for removing section key
 */
class YAIPTestFixtureSectionKeyKill : public YAIPTestFixtureBase
{
};

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

/**
 * Class for fixtures and tests for removing section
 */
class YAIPTestFixtureSectionKill : public YAIPTestFixtureBase
{
};

TEST_CASE_METHOD(YAIPTestFixtureSectionKill, "Kill section", "[sectionkill]")
{
	CHECK(IniParser.INIFileLoad(INIFilename));
	IniParser.SectionKill(Section);
	std::vector<std::string> SectionList = IniParser.SectionListGet();

	auto ResultSection = std::find(std::begin(SectionList), std::end(SectionList), Section);
	CHECK(ResultSection == std::end(SectionList));
}