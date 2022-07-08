@echo off
setlocal
set "DIR_BASE=%~dp0"
set "GRAMMAR=%~dpnx1"
if exist "%GRAMMAR%" (
    echo.Create code from [%GRAMMAR%]
    call "%DIR_BASE%antlr4.bat" -Dlanguage=Cpp -o "%DIR_BASE%\src\generated" -encoding UTF8 -listener -visitor "%GRAMMAR%"
) else (
    echo.Grammar file [%GRAMMAR%] does not exist.
)
endlocal
