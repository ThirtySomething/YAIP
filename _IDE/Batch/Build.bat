@ECHO OFF
SET "SCRIPTDIR=%~DP0"
CD .\..\..\src\
CMake .
