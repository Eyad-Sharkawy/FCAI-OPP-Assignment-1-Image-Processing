@echo off
echo Building Image Studio (release)...

REM Set Qt environment
set PATH=C:\Qt\6.8.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%
set QTDIR=C:\Qt\6.8.1\mingw_64

REM Clean previous release build
if exist "build_release" rmdir /s /q build_release
mkdir build_release
cd build_release

REM Generate Makefile with qmake
qmake ..\simple_app.pro

REM Build the project using mingw32-make
mingw32-make -f Makefile.Release

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Executable should be in build_release/release/
    echo.
) else (
    echo.
    echo Build failed. You may need to use Qt Creator instead.
    echo.
)

pause


