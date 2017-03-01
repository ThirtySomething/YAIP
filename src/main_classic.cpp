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
void VectorCompareExist(const std::vector<std::string> &KeyList, const std::string &Value, const std::string Message)
{
	auto ResultValue = std::find(std::begin(KeyList), std::end(KeyList), Value);
	if (ResultValue == std::end(KeyList))
	{
		std::cout << Message << std::endl;
		exit(-1);
	}
}

//******************************************************************************
//******************************************************************************
void VectorCompareExistNot(const std::vector<std::string> &KeyList, const std::string &Value, const std::string Message)
{
	auto ResultValue = std::find(std::begin(KeyList), std::end(KeyList), Value);
	if (ResultValue != std::end(KeyList))
	{
		std::cout << Message << std::endl;
		exit(-1);
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
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyFloat, Test.ValueFloat);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyInteger, Test.ValueInteger);
	Test.IniParser.SectionKeyValueSet(Test.Section, Test.KeyLong, Test.ValueLong);
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

	TestKeyValue(Test.IniParser, Test.Section, Test.KeyBool, Test.DefaultBool, Test.ValueBool, "Error on type bool!");
	TestKeyValue(Test.IniParser, Test.Section, Test.KeyDouble, Test.DefaultDouble, Test.ValueDouble, "Error on type double!");
	TestKeyValue(Test.IniParser, Test.Section, Test.KeyFloat, Test.DefaultFloat, Test.ValueFloat, "Error on type float!");
	TestKeyValue(Test.IniParser, Test.Section, Test.KeyInteger, Test.DefaultInteger, Test.ValueInteger, "Error on type int!");
	TestKeyValue(Test.IniParser, Test.Section, Test.KeyLong, Test.DefaultLong, Test.ValueLong, "Error on type long!");
	TestKeyValue(Test.IniParser, Test.Section, Test.KeyString, Test.DefaultString, Test.ValueString, "Error on type string!");

	DisplayINI(Test.IniParser, TestName);
}

//******************************************************************************
//******************************************************************************
void TestSectionList(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureSectionList Test;

	Test.IniParser.INIFileLoad(INIFilename);
	std::vector<std::string> SectionList = Test.IniParser.SectionListGet();

	VectorCompareExist(SectionList, Test.Section, "Error on SectionList!");

	DisplayINI(Test.IniParser, TestName);
}

//******************************************************************************
//******************************************************************************
void TestSectionKeyList(std::string TestName, std::string INIFilename)
{
	YAIPTestFixtureSectionKeyList Test;

	Test.IniParser.INIFileLoad(INIFilename);
	std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

	VectorCompareExist(KeyList, Test.KeyBool, "Key for bool not found!");
	VectorCompareExist(KeyList, Test.KeyDouble, "Key for double not found!");
	VectorCompareExist(KeyList, Test.KeyFloat, "Key for float not found!");
	VectorCompareExist(KeyList, Test.KeyInteger, "Key for integer not found!");
	VectorCompareExist(KeyList, Test.KeyLong, "Key for long not found!");
	VectorCompareExist(KeyList, Test.KeyString, "Key for string not found!");

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

		VectorCompareExistNot(KeyList, Test.KeyBool, "Key for bool found!");
		VectorCompareExist(KeyList, Test.KeyDouble, "Key for double not found!");
		VectorCompareExist(KeyList, Test.KeyFloat, "Key for float not found!");
		VectorCompareExist(KeyList, Test.KeyInteger, "Key for integer not found!");
		VectorCompareExist(KeyList, Test.KeyLong, "Key for long not found!");
		VectorCompareExist(KeyList, Test.KeyString, "Key for string not found!");

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyDouble);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		VectorCompareExist(KeyList, Test.KeyBool, "Key for bool not found!");
		VectorCompareExistNot(KeyList, Test.KeyDouble, "Key for double found!");
		VectorCompareExist(KeyList, Test.KeyFloat, "Key for float not found!");
		VectorCompareExist(KeyList, Test.KeyInteger, "Key for integer not found!");
		VectorCompareExist(KeyList, Test.KeyLong, "Key for long not found!");
		VectorCompareExist(KeyList, Test.KeyString, "Key for string not found!");

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyFloat);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		VectorCompareExist(KeyList, Test.KeyBool, "Key for bool not found!");
		VectorCompareExist(KeyList, Test.KeyDouble, "Key for double not found!");
		VectorCompareExistNot(KeyList, Test.KeyFloat, "Key for float found!");
		VectorCompareExist(KeyList, Test.KeyInteger, "Key for integer not found!");
		VectorCompareExist(KeyList, Test.KeyLong, "Key for long not found!");
		VectorCompareExist(KeyList, Test.KeyString, "Key for string not found!");

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyInteger);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		VectorCompareExist(KeyList, Test.KeyBool, "Key for bool not found!");
		VectorCompareExist(KeyList, Test.KeyDouble, "Key for double not found!");
		VectorCompareExist(KeyList, Test.KeyFloat, "Key for float not found!");
		VectorCompareExistNot(KeyList, Test.KeyInteger, "Key for integer found!");
		VectorCompareExist(KeyList, Test.KeyLong, "Key for long not found!");
		VectorCompareExist(KeyList, Test.KeyString, "Key for string not found!");

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyLong);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		VectorCompareExist(KeyList, Test.KeyBool, "Key for bool not found!");
		VectorCompareExist(KeyList, Test.KeyDouble, "Key for double not found!");
		VectorCompareExist(KeyList, Test.KeyFloat, "Key for float not found!");
		VectorCompareExist(KeyList, Test.KeyInteger, "Key for integer not found!");
		VectorCompareExistNot(KeyList, Test.KeyLong, "Key for long found!");
		VectorCompareExist(KeyList, Test.KeyString, "Key for string not found!");

		DisplayINI(Test.IniParser, TestName);
	}

	{
		Test.IniParser.INIFileLoad(INIFilename);
		Test.IniParser.SectionKeyKill(Test.Section, Test.KeyString);
		std::vector<std::string> KeyList = Test.IniParser.SectionKeyListGet(Test.Section);

		VectorCompareExist(KeyList, Test.KeyBool, "Key for bool not found!");
		VectorCompareExist(KeyList, Test.KeyDouble, "Key for double not found!");
		VectorCompareExist(KeyList, Test.KeyFloat, "Key for float not found!");
		VectorCompareExist(KeyList, Test.KeyInteger, "Key for integer not found!");
		VectorCompareExist(KeyList, Test.KeyLong, "Key for long not found!");
		VectorCompareExistNot(KeyList, Test.KeyString, "Key for string found!");

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

	VectorCompareExistNot(SectionList, Test.Section, "Section found!");

	DisplayINI(Test.IniParser, TestName);
}
