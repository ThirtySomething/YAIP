//******************************************************************************
// Copyright 2016 ThirtySomething
//******************************************************************************
// This file is part of YAIP++.
//
// YAIP++ is free software: you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// YAIP++ is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with YAIP++. If not, see <http://www.gnu.org/licenses/>.
//******************************************************************************

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
