#include <iostream>
#include "YAIP++.h"

int main()
{
	YAIP::YAIP IniParser;

	std::cout << "Test of YAIP" << std::endl;

	IniParser.INIFileLoad("C:\\Windows\\system.ini");
	YAIP::tVectorString SectionList = IniParser.GetSectionList();
	for (YAIP::tVectorString::iterator LoopSection = SectionList.begin(); LoopSection != SectionList.end(); ++LoopSection)
	{
		std::cout << "-----" << std::endl;
		std::string Section = *LoopSection;
		std::cout << Section << std::endl;
		YAIP::tVectorString KeyList = IniParser.GetSectionKeys(Section);
		for (YAIP::tVectorString::iterator LoopKey = KeyList.begin(); LoopKey != KeyList.end(); ++LoopKey)
		{
			std::string Default = "nix da!";
			std::string Key = *LoopKey;
			std::string Value = IniParser.GetSectionKeyValue(Section, Key, Default);
			std::cout << Key << "=" << Value << std::endl;
		}
	}

	return 0;
}
