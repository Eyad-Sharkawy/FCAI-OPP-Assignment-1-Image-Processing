@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo ========================================
echo    Image Studio - Complete Build
echo ========================================
echo.

REM Set Qt environment
set PATH=C:\Qt\6.8.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%
set QTDIR=C:\Qt\6.8.1\mingw_64

echo [1/4] Cleaning previous builds...
if exist "build_release" rmdir /s /q build_release
if exist "build_portable" rmdir /s /q build_portable
if exist "release" rmdir /s /q release
echo ✓ Cleaned previous builds
echo.

echo [2/4] Building release version...
qmake "%PROJ_DIR%ImageStudio.pro"
mingw32-make -f Makefile.Release

if %ERRORLEVEL% NEQ 0 (
    echo ✗ Release build failed!
    popd
    pause
    exit /b 1
)
echo ✓ Release build successful
echo.

echo [3/4] Creating portable package...
mkdir build_portable\ImageStudio_Portable
mkdir build_portable\ImageStudio_Portable\bin

copy release\ImageStudio.exe build_portable\ImageStudio_Portable\bin\

cd build_portable\ImageStudio_Portable\bin
windeployqt ImageStudio.exe
cd ..\..\..

if exist "%PROJ_DIR%assets" (
    xcopy "%PROJ_DIR%assets" build_portable\ImageStudio_Portable\assets\ /E /I
)

echo @echo off > build_portable\ImageStudio_Portable\ImageStudio.bat
echo cd /d "%%~dp0bin" >> build_portable\ImageStudio_Portable\ImageStudio.bat
echo echo Starting ImageStudio... >> build_portable\ImageStudio_Portable\ImageStudio.bat
echo ImageStudio.exe %%* >> build_portable\ImageStudio_Portable\ImageStudio.bat

echo Image Studio - Portable Version > build_portable\ImageStudio_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo This is a portable version of Image Studio that includes all necessary >> build_portable\ImageStudio_Portable\README.txt
echo Qt libraries and dependencies. >> build_portable\ImageStudio_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo To run: >> build_portable\ImageStudio_Portable\README.txt
echo 1. Double-click ImageStudio.bat >> build_portable\ImageStudio_Portable\README.txt
echo 2. Or run bin\ImageStudio.exe directly >> build_portable\ImageStudio_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo Features: >> build_portable\ImageStudio_Portable\README.txt
echo - All image processing filters >> build_portable\ImageStudio_Portable\README.txt
echo - Drag and drop image loading >> build_portable\ImageStudio_Portable\README.txt
echo - Undo/Redo functionality >> build_portable\ImageStudio_Portable\README.txt
echo - Responsive UI >> build_portable\ImageStudio_Portable\README.txt
echo - Professional interface >> build_portable\ImageStudio_Portable\README.txt
echo. >> build_portable\ImageStudio_Portable\README.txt
echo No installation required! >> build_portable\ImageStudio_Portable\README.txt

echo ✓ Portable package created
echo.

echo [4/4] Creating distribution ZIP...
set VERSION=2.0.0
set ZIP_NAME=build_portable\ImageStudio_Portable_v%VERSION%-gui.zip

if exist "%ZIP_NAME%" del "%ZIP_NAME%"

powershell -Command "Compress-Archive -Path 'build_portable\ImageStudio_Portable' -DestinationPath 'build_portable\ImageStudio_Portable_v2.0.0-gui.zip' -Force"

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
echo ✓ release\ImageStudio.exe (Release executable)
echo ✓ build_portable\ImageStudio_Portable\ (Portable package)
echo ✓ build_portable\ImageStudio_Portable_v2.0.0-gui.zip (Distribution ZIP)
echo.
echo You can now:
echo - Run the application: release\ImageStudio.exe
echo - Test the portable version: build_portable\ImageStudio_Portable\ImageStudio.bat
echo - Distribute the ZIP file to users
echo.

popd
pause
