@echo off
setlocal
set "DIR_BASE=%~dp0"
call "%DIR_BASE%base.bat"
javac %*
endlocal
