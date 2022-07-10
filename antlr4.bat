@echo off
setlocal
set "DIR_BASE=%~dp0"
call "%DIR_BASE%base.bat"
java org.antlr.v4.Tool %*
endlocal
