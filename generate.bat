@echo off
setlocal
set "DIR_BASE=%~dp0"
call "%DIR_BASE%antlr4.bat" -Dlanguage=Cpp -o grammar -encoding UTF8 -listener -visitor "%DIR_BASE%Hello.g4"
endlocal
