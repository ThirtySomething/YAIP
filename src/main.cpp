#include <iostream>
#include "YAIP++.h"

void DisplayINI(YAIP::YAIP &IniParser)
{
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

	std::cout << "Test of YAIP" << std::endl;

	IniParser.INIFileLoad("C:\\Windows\\system.ini");

	// Display original content
	DisplayINI(IniParser);

	// Add new section/key/value
	IniParser.SectionKeyValueSet("Section", "Key", "Value");
	// Add to existing section a new key value
	IniParser.SectionKeyValueSet("386Enh", "Key", "Value");
	// Update existing section/key/value
	IniParser.SectionKeyValueSet("drivers", "wave", "Value");

	// Display modified content
	DisplayINI(IniParser);

	// Save new INI file
	IniParser.INIFileSave("C:\\Windows\\Temp\\_YAIP.ini");

	return 0;
}