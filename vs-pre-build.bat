@echo off
setlocal
set "SOLUTIONDIR=%~1"
set "PLATFORM=%~2"
set "CONFIGURATION=%~3"
set "GRAMMAR=%~4"
echo.Prebuild trigger of YAIP
echo.Using [%SOLUTIONDIR%] as solution dir
echo.Using [%PLATFORM%] as platform
echo.Using [%CONFIGURATION%] as configuration
echo.------------------------------
echo.Copying ANTLR4 runtime files
@rem echo.xcopy /y /v /c /f "%SOLUTIONDIR%bin\vs-2019\%PLATFORM%\%CONFIGURATION% DLL\antlr4-runtime.*" "%SOLUTIONDIR%bin\%CONFIGURATION%\"
xcopy /y /v /c /f "%SOLUTIONDIR%bin\vs-2019\%PLATFORM%\%CONFIGURATION% DLL\antlr4-runtime.*" "%SOLUTIONDIR%bin\%CONFIGURATION%\"
echo.------------------------------
@rem echo."%SOLUTIONDIR%generate.bat" "%GRAMMAR%"
call "%SOLUTIONDIR%generate.bat" "%GRAMMAR%"
echo.------------------------------
endlocal
