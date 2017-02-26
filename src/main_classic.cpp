#include "main_classic.h"
#include <iostream>
#include <sys/stat.h>

//******************************************************************************
//******************************************************************************
void DisplayINI(org::derpaul::yaip::YAIP &IniParser, std::string &Comment)
{
	std::cout << "----- " << Comment << " -----" << std::endl;

	org::derpaul::yaip::tVectorString SectionList = IniParser.SectionListGet();
	for (org::derpaul::yaip::tVectorString::iterator LoopSection = SectionList.begin(); LoopSection != SectionList.end(); ++LoopSection)
	{
		std::string Section = *LoopSection;
		if (0 < Section.length())
		{
			std::cout << "[" << Section << "]" << std::endl;
		}

		org::derpaul::yaip::tVectorString KeyList = IniParser.SectionKeyListGet(Section);
		int SectionCount = 0;
		for (org::derpaul::yaip::tVectorString::iterator LoopKey = KeyList.begin(); LoopKey != KeyList.end(); ++LoopKey)
		{
			std::string Default = "Default";
			std::string Key = *LoopKey;
			std::string Value = IniParser.SectionKeyValueGet(Section, Key, Default);
			std::cout << Key << "=" << Value << std::endl;
			SectionCount++;
		}
	}
}

//******************************************************************************
//******************************************************************************
void TestSave(std::string TestName, std::string INIFilename)
{
    struct stat FileDataRaw;
	YAIPTestFixtureSave Test;

	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyBool, Test.ValueBool);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyDouble, Test.ValueDouble);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyInteger, Test.ValueInt);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyString, Test.ValueString);
	Test.IniParser.INIFileSave(INIFilename);

	if (0 != stat(INIFilename.c_str(), &FileDataRaw))
    {
        std::cout << __FUNCTION__ << ": INI file not created, failure!" << std::endl;
        exit(-1);
    }

	DisplayINI(Test.IniParser, TestName);
}

//******************************************************************************
//******************************************************************************
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

//******************************************************************************
//******************************************************************************
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

//******************************************************************************
//******************************************************************************
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

//******************************************************************************
//******************************************************************************
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

//******************************************************************************
//******************************************************************************
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
