@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo ========================================
echo    Photo Smith - Complete Build
echo ========================================
echo.

REM Set Qt environment
set PATH=C:\Qt\6.8.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%
set QTDIR=C:\Qt\6.8.1\mingw_64
set CMAKE_GENERATOR=MinGW Makefiles

REM Set compiler environment variables for proper icon embedding
set CMAKE_MAKE_PROGRAM=C:\Qt\Tools\mingw1310_64\bin\mingw32-make.exe
set CMAKE_C_COMPILER=C:\Qt\Tools\mingw1310_64\bin\gcc.exe
set CMAKE_CXX_COMPILER=C:\Qt\Tools\mingw1310_64\bin\g++.exe

echo [1/4] Cleaning previous builds...
if exist "build_release" rmdir /s /q build_release
if exist "build_portable" rmdir /s /q build_portable
if exist "release" rmdir /s /q release
if exist "cmake-build-release" rmdir /s /q cmake-build-release
echo ✓ Cleaned previous builds
echo.

echo [2/4] Building release version with CMake...
cmake -S . -B cmake-build-release -G "%CMAKE_GENERATOR%" -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="%CMAKE_MAKE_PROGRAM%" -DCMAKE_C_COMPILER="%CMAKE_C_COMPILER%" -DCMAKE_CXX_COMPILER="%CMAKE_CXX_COMPILER%"
cmake --build cmake-build-release -j 8

if %ERRORLEVEL% NEQ 0 (
    echo ✗ Release build failed!
    popd
    pause
    exit /b 1
)
echo ✓ Release build successful
echo.

echo [3/4] Creating portable package...
mkdir build_portable\PhotoSmith_Portable
mkdir build_portable\PhotoSmith_Portable\bin

copy cmake-build-release\bin\PhotoSmith.exe build_portable\PhotoSmith_Portable\bin\

cd build_portable\PhotoSmith_Portable\bin
windeployqt PhotoSmith.exe
cd ..\..\..

if exist "%PROJ_DIR%assets" (
    xcopy "%PROJ_DIR%assets" build_portable\PhotoSmith_Portable\assets\ /E /I
)

echo @echo off > build_portable\PhotoSmith_Portable\PhotoSmith.bat
echo cd /d "%%~dp0bin" >> build_portable\PhotoSmith_Portable\PhotoSmith.bat
echo echo Starting PhotoSmith... >> build_portable\PhotoSmith_Portable\PhotoSmith.bat
echo PhotoSmith.exe %%* >> build_portable\PhotoSmith_Portable\PhotoSmith.bat

echo Photo Smith - Portable Version > build_portable\PhotoSmith_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo This is a portable version of Photo Smith that includes all necessary >> build_portable\PhotoSmith_Portable\README.txt
echo Qt libraries and dependencies. >> build_portable\PhotoSmith_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo To run: >> build_portable\ImageStudio_Portable\README.txt
echo 1. Double-click PhotoSmith.bat >> build_portable\PhotoSmith_Portable\README.txt
echo 2. Or run bin\PhotoSmith.exe directly >> build_portable\PhotoSmith_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo Features: >> build_portable\ImageStudio_Portable\README.txt
echo - All image processing filters >> build_portable\ImageStudio_Portable\README.txt
echo - Drag and drop image loading >> build_portable\ImageStudio_Portable\README.txt
echo - Undo/Redo functionality >> build_portable\ImageStudio_Portable\README.txt
echo - Responsive UI >> build_portable\ImageStudio_Portable\README.txt
echo - Professional interface >> build_portable\PhotoSmith_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo No installation required! >> build_portable\PhotoSmith_Portable\README.txt

echo ✓ Portable package created
echo.

echo [4/4] Creating distribution ZIP...
set VERSION=3.5.0
set ZIP_NAME=build_portable\PhotoSmith_Portable_v%VERSION%-gui.zip

if exist "%ZIP_NAME%" del "%ZIP_NAME%"

powershell -Command "Compress-Archive -Path 'build_portable\PhotoSmith_Portable' -DestinationPath 'build_portable\PhotoSmith_Portable_v%VERSION%-gui.zip' -Force"

if %ERRORLEVEL% EQU 0 (
    echo ✓ ZIP file created successfully
) else (
    echo ⚠ Warning: Could not create ZIP file automatically
)

echo.
echo ========================================
echo           BUILD COMPLETE!
echo ========================================
echo.
echo Files created:
echo ✓ release\PhotoSmith.exe (Release executable)
echo ✓ build_portable\PhotoSmith_Portable\ (Portable package)
echo ✓ build_portable\PhotoSmith_Portable_v%VERSION%-gui.zip (Distribution ZIP)
echo.
echo You can now:
echo - Run the application: release\PhotoSmith.exe
echo - Test the portable version: build_portable\PhotoSmith_Portable\PhotoSmith.bat
echo - Distribute the ZIP file to users
echo.

popd
pause
