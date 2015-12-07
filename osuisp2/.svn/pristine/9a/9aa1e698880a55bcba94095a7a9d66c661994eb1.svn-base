@echo off
:START
cls

make clean hex
IF ERRORLEVEL 1 GOTO ExitError
GOTO ExitNormal

:ExitError
echo There was an error!
pause
GOTO START

:ExitNormal
echo Compile fine



set /p yn=May I compile again? [y/n/c, default=y, c=clean and quit]
if /I "%yn%"=="y" (GOTO START)
if /I "%yn%"=="n" (GOTO DONE)
if /I "%yn%"=="c" (GOTO CLEAN)
GOTO START

:CLEAN
make clean

:DONE