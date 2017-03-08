#include "main_fixtures.h"
#include <climits>
#include <cfloat>

//******************************************************************************
//******************************************************************************
const std::string YAIPTestFixtureBase::INIFilename = "yaip.ini";
const std::string YAIPTestFixtureBase::Section = "Section";
const std::string YAIPTestFixtureBase::KeyBool = "Bool";
const std::string YAIPTestFixtureBase::KeyDouble = "Double";
const std::string YAIPTestFixtureBase::KeyFloat = "Float";
const std::string YAIPTestFixtureBase::KeyInteger = "Integer";
const std::string YAIPTestFixtureBase::KeyLong = "Long";
const std::string YAIPTestFixtureBase::KeyString = "String";

//******************************************************************************
//******************************************************************************
YAIPTestFixtureBase::YAIPTestFixtureBase(void)
	: IniParser()
{
}

//******************************************************************************
//******************************************************************************
const bool YAIPTestFixtureSave::ValueBool = true;
const double YAIPTestFixtureSave::ValueDouble = 12345.09876;
const float YAIPTestFixtureSave::ValueFloat = 12345.09876f;
const int YAIPTestFixtureSave::ValueInteger = INT_MAX;
const long YAIPTestFixtureSave::ValueLong = LONG_MAX;
const std::string YAIPTestFixtureSave::ValueString = "Value";

//******************************************************************************
//******************************************************************************
YAIPTestFixtureSave::YAIPTestFixtureSave(void)
	: YAIPTestFixtureBase()
{
}

//******************************************************************************
//******************************************************************************
const bool YAIPTestFixtureLoad::DefaultBool = false;
const double YAIPTestFixtureLoad::DefaultDouble = 0.0;
const float YAIPTestFixtureLoad::DefaultFloat = 0.0f;
const int YAIPTestFixtureLoad::DefaultInteger = 0;
const long YAIPTestFixtureLoad::DefaultLong = 0;
const std::string YAIPTestFixtureLoad::DefaultString = "";

//******************************************************************************
//******************************************************************************
YAIPTestFixtureLoad::YAIPTestFixtureLoad(void)
	: YAIPTestFixtureSave()
{
}

//******************************************************************************
//******************************************************************************
YAIPTestFixtureSectionList::YAIPTestFixtureSectionList(void)
	: YAIPTestFixtureBase()
{
}

//******************************************************************************
//******************************************************************************
YAIPTestFixtureSectionKeyList::YAIPTestFixtureSectionKeyList(void)
	: YAIPTestFixtureBase()
{
}

//******************************************************************************
//******************************************************************************
YAIPTestFixtureSectionKeyKill::YAIPTestFixtureSectionKeyKill(void)
	: YAIPTestFixtureBase()
{
}

//******************************************************************************
//******************************************************************************

YAIPTestFixtureSectionKill::YAIPTestFixtureSectionKill(void)
	: YAIPTestFixtureBase()
{
}
