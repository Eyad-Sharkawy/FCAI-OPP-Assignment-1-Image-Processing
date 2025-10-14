@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo Building Photo Smith (portable)...

REM Set Qt environment
set PATH=C:\Qt\6.8.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%
set QTDIR=C:\Qt\6.8.1\mingw_64
set CMAKE_GENERATOR=MinGW Makefiles

REM Set compiler environment variables for proper icon embedding
set CMAKE_MAKE_PROGRAM=C:\Qt\Tools\mingw1310_64\bin\mingw32-make.exe
set CMAKE_C_COMPILER=C:\Qt\Tools\mingw1310_64\bin\gcc.exe
set CMAKE_CXX_COMPILER=C:\Qt\Tools\mingw1310_64\bin\g++.exe

REM Clean previous portable build
if exist "build_portable" rmdir /s /q build_portable
if exist "cmake-build-release" rmdir /s /q cmake-build-release

REM Configure and build with CMake (Release)
cmake -S . -B cmake-build-release -G "%CMAKE_GENERATOR%" -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM="%CMAKE_MAKE_PROGRAM%" -DCMAKE_C_COMPILER="%CMAKE_C_COMPILER%" -DCMAKE_CXX_COMPILER="%CMAKE_CXX_COMPILER%"
cmake --build cmake-build-release -j 8

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Creating portable package...
    
    REM Create portable directory structure
    mkdir build_portable\PhotoSmith_Portable
    mkdir build_portable\PhotoSmith_Portable\bin
    
    REM Copy executable
    copy cmake-build-release\bin\PhotoSmith.exe build_portable\PhotoSmith_Portable\bin\
    
    REM Use windeployqt to automatically deploy all Qt dependencies
    cd build_portable\PhotoSmith_Portable\bin
    windeployqt PhotoSmith.exe
    cd ..\..\..
    
    REM Copy assets
    if exist "%PROJ_DIR%assets" (
        xcopy "%PROJ_DIR%assets" build_portable\PhotoSmith_Portable\assets\ /E /I
    )
    
    REM Create launcher script
    echo @echo off > build_portable\PhotoSmith_Portable\PhotoSmith.bat
    echo cd /d "%%~dp0bin" >> build_portable\PhotoSmith_Portable\PhotoSmith.bat
    echo echo Starting PhotoSmith... >> build_portable\PhotoSmith_Portable\PhotoSmith.bat
    echo PhotoSmith.exe %%* >> build_portable\PhotoSmith_Portable\PhotoSmith.bat
    
    REM Create README for portable version
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
    
    echo.
    echo Portable package created in: build_portable\PhotoSmith_Portable\
    echo.
    echo Creating ZIP file...
    
    REM Create ZIP file with version number
    set VERSION=2.0.0
    set ZIP_NAME=build_portable\PhotoSmith_Portable_v%VERSION%-gui.zip
    
    REM Remove existing ZIP if it exists
    if exist "%ZIP_NAME%" del "%ZIP_NAME%"
    
    REM Create ZIP using PowerShell
    powershell -Command "Compress-Archive -Path 'build_portable\PhotoSmith_Portable' -DestinationPath 'build_portable\PhotoSmith_Portable_v3.0.1-gui.zip' -Force"
    
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo ✓ ZIP file created successfully: build_portable\PhotoSmith_Portable_v3.0.1-gui.zip
        echo ✓ Portable package ready for distribution!
    ) else (
        echo.
        echo ⚠ Warning: Could not create ZIP file automatically.
        echo   You can create it manually by running:
        echo   powershell Compress-Archive -Path "build_portable\PhotoSmith_Portable" -DestinationPath "build_portable\PhotoSmith_Portable_v3.0.1-gui.zip"
    )
    echo.
) else (
    echo.
    echo Build failed. You may need to use Qt Creator instead.
    echo.
)

popd

pause
