:START
echo.
echo. GS Module Program script ver 1.0
echo. ---------------------------------------
echo.

@echo off
echo. Enter the COM PORT Number: 
set /p comport= 
echo.
echo. Selected COM Port Number is: COM%comport%

echo.
echo. Creating App Flash image
echo. ---------------------------------------


type NUL > ..\bin\gs2000_app_dummy.bin

echo.

echo.
echo. Creating SINGLE image
echo. ---------------------------------------

echo. ..\..\..\tools\GS_SingleImageBuilder_tool\gs2kSingleImageBuilder.exe ..\..\..\tools\Super_Control_block\ctlblock_ram_web.bin ..\bin\gs2000_app_dummy.bin ..\..\..\wfw\bin\gs2000_wlan.bin ..\..\..\tools\Super_Control_block\webImage.bin ..\bin\gs2000_SingleImage.bin



..\..\..\tools\GS_SingleImageBuilder_tool\gs2kSingleImageBuilder.exe ..\..\..\tools\Super_Control_block\ctlblock_ram_web.bin ..\bin\gs2000_app_dummy.bin ..\..\..\wfw\bin\gs2000_wlan.bin ..\..\..\tools\Super_Control_block\webImage.bin ..\bin\gs2000_SingleImage.bin

echo.
echo.
echo. Part1
echo. -----
echo. Erasing the GS Module
echo. Put the GS Module in PROGRAM mode and perform power cycle
pause.
:PART1
echo.
echo. Erasing the GS2000 Module
echo.
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x00 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :E2
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :PART1
)

:E2
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x80000 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :E3
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :E2
)

:E3
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x100000 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :E4
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :E3
)

:E4
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x180000 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :E5
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :E4
)

:E5
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x200000 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :E6
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :E5
)

:E6
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x280000 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :E7
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :E6
)

:E7
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x300000 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :E8
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :E7
)

:E8
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -e 0x380000 0x80000 -S%comport% -v

REM echo. Debug Level = %errorlevel%
if %errorlevel%==0 (
 goto :PART2
)
if %errorlevel%==-1  (
echo.
echo. Please check Module connection setup
pause
goto :E8
)

:PART2

REM Program super block at 0x00, control block at 0x1000 and 0xff000
REM and app flash image at 0x2000 and wlan at 0x80000.

echo.
echo.
echo. Part2
echo. -----
echo. Programming the GS Module
echo.


:SINGLEIMAGE
..\..\..\tools\GS_programming_tool\DOS_Files\gs_flashprogram.exe -c1 -n1 -1 ..\bin\gs2000_SingleImage.bin -2 ..\..\..\tools\Super_Control_block\superblock_2MB_3_Copy.bin -S%comport% -vvv

REM echo. Debug Level = %errorlevel%
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
