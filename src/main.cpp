// #define OLD_STYLE

#include "YAIP++.h"
#include <sys/stat.h>
#include <iostream>

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

/**
 * Class for fixtures and tests for reading section list
 */
class YAIPTestFixtureSectionList : public YAIPTestFixtureBase
{
};

/**
 * Class for fixtures and tests for reading section key list
 */
class YAIPTestFixtureSectionKeyList : public YAIPTestFixtureBase
{
};

/**
 * Class for fixtures and tests for removing section key
 */
class YAIPTestFixtureSectionKeyKill : public YAIPTestFixtureBase
{
};

/**
 * Class for fixtures and tests for removing section
 */
class YAIPTestFixtureSectionKill : public YAIPTestFixtureBase
{
};

#ifdef OLD_STYLE

#include <iostream>

/**
* Simple function to display content of INI file
* \param IniParser An instance of YAIP
* \param Comment A remark printed on top
*/
void DisplayINI(YAIP::YAIP &IniParser, std::string &Comment)
{
	std::cout << "----- " << Comment << " -----" << std::endl;

	YAIP::tVectorString SectionList = IniParser.SectionListGet();
	for (YAIP::tVectorString::iterator LoopSection = SectionList.begin(); LoopSection != SectionList.end(); ++LoopSection)
	{
		std::string Section = *LoopSection;
		if (0 < Section.length())
		{
			std::cout << "[" << Section << "]" << std::endl;
		}

		YAIP::tVectorString KeyList = IniParser.SectionKeyListGet(Section);
		int SectionCount = 0;
		for (YAIP::tVectorString::iterator LoopKey = KeyList.begin(); LoopKey != KeyList.end(); ++LoopKey)
		{
			std::string Default = "Default";
			std::string Key = *LoopKey;
			std::string Value = IniParser.SectionKeyValueGet(Section, Key, Default);
			std::cout << Key << "=" << Value << std::endl;
			SectionCount++;
		}
	}
}

void TestSave(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureSave Test;

	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyBool, Test.ValueBool);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyDouble, Test.ValueDouble);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyInteger, Test.ValueInt);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyString, Test.ValueString);
	Test.IniParser.INIFileSave(INIFilename);

	DisplayINI(Test.IniParser, TestName);
}

void TestLoad(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureLoad Test;

	Test.IniParser.INIFileLoad(INIFilename);

	bool ResultBool = Test.IniParser.SectionKeyValueGet(Test.Section, Test.KeyBool, Test.DefaultBool);
	if ((ResultBool == Test.DefaultBool) ||
		(ResultBool != Test.ValueBool))
	{
		std::cout << "Fehler bei bool!" << std::endl;
	}

	double ResultDouble = Test.IniParser.SectionKeyValueGet(Test.Section, Test.KeyDouble, Test.DefaultDouble);
	if ((ResultDouble == Test.DefaultDouble) ||
		(ResultDouble != Test.ValueDouble))
	{
		std::cout << "Fehler bei double!" << std::endl;
	}

	int ResultInt = Test.IniParser.SectionKeyValueGet(Test.Section, Test.KeyInteger, Test.DefaultInt);
	if ((ResultInt == Test.DefaultInt) ||
		(ResultInt != Test.ValueInt))
	{
		std::cout << "Fehler bei int!" << std::endl;
	}

	std::string ResultString = Test.IniParser.SectionKeyValueGet(Test.Section, Test.KeyString, Test.DefaultString);
	if ((0 == ResultString.compare(Test.DefaultString)) ||
		(0 != ResultString.compare(Test.ValueString)))
	{
		std::cout << "Fehler bei string!" << std::endl;
	}

	DisplayINI(Test.IniParser, TestName);
}

void TestSectionList(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureSectionList Test;

	Test.IniParser.INIFileLoad(INIFilename);
	std::vector<std::string> SectionList = Test.IniParser.SectionListGet();

	auto ResultSection = std::find(std::begin(SectionList), std::end(SectionList), Test.Section);
	if (ResultSection == std::end(SectionList))
	{
		std::cout << "Fehler bei SectionList!" << std::endl;
	}

	DisplayINI(Test.IniParser, TestName);
}

void TestSectionKeyList(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureSectionKeyList Test;

	Test.IniParser.INIFileLoad(INIFilename);
	std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

	auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyBool);
	if (ResultBool == std::end(KeyList))
	{
		std::cout << "Key for bool not found!" << std::endl;
	}

	auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyDouble);
	if (ResultDouble == std::end(KeyList))
	{
		std::cout << "Key for double not found!" << std::endl;
	}

	auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyInteger);
	if (ResultInt == std::end(KeyList))
	{
		std::cout << "Key for int not found!" << std::endl;
	}

	auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyString);
	if (ResultString == std::end(KeyList))
	{
		std::cout << "Key for string not found!" << std::endl;
	}

	DisplayINI(Test.IniParser, TestName);
}

void TestSectionKeyKill(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureSectionKeyKill Test;

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyBool);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyBool);
		if (ResultBool != std::end(KeyList))
		{
			std::cout << "Key for bool found!" << std::endl;
		}

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyDouble);
		if (ResultDouble == std::end(KeyList))
		{
			std::cout << "Key for double not found!" << std::endl;
		}

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyInteger);
		if (ResultInt == std::end(KeyList))
		{
			std::cout << "Key for int not found!" << std::endl;
		}

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyString);
		if (ResultString == std::end(KeyList))
		{
			std::cout << "Key for string not found!" << std::endl;
		}

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyDouble);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyBool);
		if (ResultBool == std::end(KeyList))
		{
			std::cout << "Key for bool not found!" << std::endl;
		}

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyDouble);
		if (ResultDouble != std::end(KeyList))
		{
			std::cout << "Key for double found!" << std::endl;
		}

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyInteger);
		if (ResultInt == std::end(KeyList))
		{
			std::cout << "Key for int not found!" << std::endl;
		}

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyString);
		if (ResultString == std::end(KeyList))
		{
			std::cout << "Key for string not found!" << std::endl;
		}

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyInteger);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyBool);
		if (ResultBool == std::end(KeyList))
		{
			std::cout << "Key for bool not found!" << std::endl;
		}

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyDouble);
		if (ResultDouble == std::end(KeyList))
		{
			std::cout << "Key for double not found!" << std::endl;
		}

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyInteger);
		if (ResultInt != std::end(KeyList))
		{
			std::cout << "Key for int found!" << std::endl;
		}

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyString);
		if (ResultString == std::end(KeyList))
		{
			std::cout << "Key for string not found!" << std::endl;
		}

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyString);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		auto ResultBool = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyBool);
		if (ResultBool == std::end(KeyList))
		{
			std::cout << "Key for bool not found!" << std::endl;
		}

		auto ResultDouble = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyDouble);
		if (ResultDouble == std::end(KeyList))
		{
			std::cout << "Key for double not found!" << std::endl;
		}

		auto ResultInt = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyInteger);
		if (ResultInt == std::end(KeyList))
		{
			std::cout << "Key for int not found!" << std::endl;
		}

		auto ResultString = std::find(std::begin(KeyList), std::end(KeyList), Test.KeyString);
		if (ResultString != std::end(KeyList))
		{
			std::cout << "Key for string found!" << std::endl;
		}

		DisplayINI(Test.IniParser, TestName);
	}
}

void TestSectionKill(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureSectionKill Test;

	Test.IniParser.INIFileLoad(INIFilename);
	Test.IniParser.SectionKill(Test.Section);
	std::vector<std::string> SectionList = Test.IniParser.SectionListGet();

	auto ResultSection = std::find(std::begin(SectionList), std::end(SectionList), Test.Section);
	if (ResultSection != std::end(SectionList))
	{
		std::cout << "Section found!" << std::endl;
	}

	DisplayINI(Test.IniParser, TestName);
}

int main(int argc, char *argv[])
{
	std::string INIFile = YAIPTestFixtureBase::INIFilename;

	if (1 < argc)
	{
		INIFile = argv[1];
		INIFile = INIFile + YAIPTestFixtureBase::INIFilename;
	}

	TestSave(">>> create", INIFile);
	TestLoad(">>> load", INIFile);
	TestSectionList(">>> sectionlist", INIFile);
	TestSectionKeyList(">>> sectionkeylist", INIFile);
	TestSectionKeyKill(">>> sectionkeykill", INIFile);
	TestSectionKill(">>> sectionkill", INIFile);

	return 0;
}

#else

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

#endif
