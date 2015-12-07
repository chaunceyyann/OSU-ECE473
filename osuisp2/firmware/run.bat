@echo off
:START
cls

make clean main.hex
IF ERRORLEVEL 1 GOTO ExitError
GOTO ExitNormal

:ExitError
echo There was an error!
pause
GOTO START

:ExitNormal
echo Compile fine



set /p yn=May I compile again? [y/n, default=y]
if /I "%yn%"=="y" (GOTO START)
if /I "%yn%"=="n" (GOTO DONE)
GOTO START


:DONE