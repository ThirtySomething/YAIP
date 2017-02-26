#include "main_fixtures.h"

const std::string YAIPTestFixtureBase::INIFilename = "yaip.ini";
const std::string YAIPTestFixtureBase::Section = "Section";
const std::string YAIPTestFixtureBase::KeyBool = "Bool";
const std::string YAIPTestFixtureBase::KeyDouble = "Double";
const std::string YAIPTestFixtureBase::KeyInteger = "Integer";
const std::string YAIPTestFixtureBase::KeyString = "String";

const bool YAIPTestFixtureSave::ValueBool = true;
const double YAIPTestFixtureSave::ValueDouble = 1.23;
const int YAIPTestFixtureSave::ValueInt = 123;
const std::string YAIPTestFixtureSave::ValueString = "Value";

const bool YAIPTestFixtureLoad::DefaultBool = false;
const double YAIPTestFixtureLoad::DefaultDouble = 0.0;
const int YAIPTestFixtureLoad::DefaultInt = 0;
const std::string YAIPTestFixtureLoad::DefaultString = "";