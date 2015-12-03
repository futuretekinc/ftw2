@echo off
:START
echo.
echo. GS Module Program script ver 1.0 for SPI at 1.3MHz
echo. -----------------------------------------------------
echo.

echo. Part1
echo. -----
echo. Erasing the GS Module
echo. Put the GS Module in PROGRAM mode and perform power cycle
pause.
:PART1
echo.
echo. Erasing the GS2011 Module
echo.
gs_flashprogram.exe -E 0x00000 0x400000 -v
if %errorlevel%==0 (
 goto :Part2
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :PART1
)

:PART2

echo.
echo.
echo. Part2
echo. -----
echo. Programming the GS Module
echo.


:SINGLEIMAGE
gs_flashprogram.exe -c1 -n1 -1 gs2000_SingleImage.bin -2 superblock.bin -v
if %errorlevel%==0 (
goto :END
)
if %errorlevel%==1 (
echo. Do you want to Retry again [ y/n ]
set /p op=
if %op%==y goto :END
)


:END
echo.
echo. GS Module is successfully programmed
pause
