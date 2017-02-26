// #define OLD_STYLE

#ifdef OLD_STYLE

#include "main_classic.h"

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

#include "main_catch.h"

#endif
