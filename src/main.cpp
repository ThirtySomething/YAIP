#include <iostream>
#include "YAIP++.h"

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

int main()
{
	YAIP::YAIP IniParser;
	std::string IniSection;
	std::string IniKey;
	std::string IniValue;
	std::string IniComment;

	std::cout << "Test of YAIP" << std::endl;

	IniParser.INIFileLoad("sample.ini");

	// Display content
	IniComment = "Original";
	DisplayINI(IniParser, IniComment);

	// Add new section/key/value
	IniSection = "Section";
	IniKey = "Key";
	IniValue = "Value";
	IniParser.SectionKeyValueSet(IniSection, IniKey, IniValue);

	// Add to existing section a new key value
	IniSection = "Section01";
	IniParser.SectionKeyValueSet(IniSection, IniKey, IniValue);

	// Update existing section/key/value
	IniSection = "Section01";
	IniKey = "Entry02";
	IniValue = "2nd";
	IniParser.SectionKeyValueSet(IniSection, IniKey, IniValue);

	// Display content
	IniComment = "Modified";
	DisplayINI(IniParser, IniComment);

	// Delete a key
	IniSection = "Section01";
	IniKey = "Key";
	IniParser.SectionKeyKill(IniSection, IniKey);

	// Delete a section
	IniSection = "Section";
	IniParser.SectionKill(IniSection);

	// Display content
	IniComment = "Deleted";
	DisplayINI(IniParser, IniComment);

	// Save new INI file
	IniParser.INIFileSave("sample_yaip.ini");

	return 0;
}
