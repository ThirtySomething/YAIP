#include <iostream>
#include "YAIP++.h"

void DisplayINI(YAIP::YAIP &IniParser, std::string &Comment)
{
	std::cout << "----- " << Comment << std::endl;

	YAIP::tVectorString SectionList = IniParser.SectionListGet();
	for (YAIP::tVectorString::iterator LoopSection = SectionList.begin(); LoopSection != SectionList.end(); ++LoopSection)
	{
		std::cout << "-----" << std::endl;
		std::string Section = *LoopSection;
		std::cout << Section << std::endl;

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

int main()
{
	YAIP::YAIP IniParser;
	std::string IniSection;
	std::string IniKey;
	std::string IniValue;
	std::string IniComment;

	std::cout << "Test of YAIP" << std::endl;

	IniParser.INIFileLoad("C:\\Windows\\system.ini");

	// Display original content
	IniComment = "Original";
	DisplayINI(IniParser, IniComment);

	// Add new section/key/value
	IniSection = "Section";
	IniKey = "Key";
	IniValue = "Value";
	IniParser.SectionKeyValueSet(IniSection, IniKey, IniValue);
	// Add to existing section a new key value
	IniParser.SectionKeyValueSet("386Enh", "Key", "Value");
	// Update existing section/key/value
	IniParser.SectionKeyValueSet("drivers", "wave", "Value");

	// Display modified content
	IniComment = "Modified";
	DisplayINI(IniParser, IniComment);

	IniParser.SectionKill("Section");
	IniParser.SectionKeyKill("386Enh", "Key");

	// Display modified content
	IniComment = "Deleted";
	DisplayINI(IniParser, IniComment);

	// Save new INI file
	IniParser.INIFileSave("C:\\Windows\\Temp\\_YAIP.ini");

	return 0;
}
