@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo Building Photo Smith (release)...

REM Set Qt environment
set PATH=C:\Qt\6.8.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%
set QTDIR=C:\Qt\6.8.1\mingw_64
set CMAKE_GENERATOR=MinGW Makefiles

REM Set compiler environment variables for proper icon embedding
set CMAKE_MAKE_PROGRAM=C:\Qt\Tools\mingw1310_64\bin\mingw32-make.exe
set CMAKE_C_COMPILER=C:\Qt\Tools\mingw1310_64\bin\gcc.exe
set CMAKE_CXX_COMPILER=C:\Qt\Tools\mingw1310_64\bin\g++.exe

REM Clean previous CMake release build
if exist "cmake-build-release" rmdir /s /q cmake-build-release

REM Compile resource file
windres app.rc -o app.res

REM Configure with CMake (Release) using MinGW Makefiles
cmake -S . -B cmake-build-release -G "%CMAKE_GENERATOR%" -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="%CMAKE_MAKE_PROGRAM%" -DCMAKE_C_COMPILER="%CMAKE_C_COMPILER%" -DCMAKE_CXX_COMPILER="%CMAKE_CXX_COMPILER%"

REM Build with CMake (single-config generator)
cmake --build cmake-build-release -j 8

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Executable should be in cmake-build-release\bin\
    echo.
) else (
    echo.
    echo Build failed. You may need to use Qt Creator instead.
    echo.
)

popd

pause


