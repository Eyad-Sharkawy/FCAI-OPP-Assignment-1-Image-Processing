@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo Building Image Studio (portable)...

REM Set Qt environment
set PATH=C:\Qt\6.8.1\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;%PATH%
set QTDIR=C:\Qt\6.8.1\mingw_64

REM Clean previous portable build
if exist "build_portable" rmdir /s /q build_portable
mkdir build_portable

REM Generate Makefile with qmake (use absolute path to .pro)
qmake "%PROJ_DIR%ImageStudio.pro"

REM Build the project using mingw32-make
mingw32-make -f Makefile.Release

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Creating portable package...
    
    REM Create portable directory structure
    mkdir build_portable\ImageStudio_Portable
    mkdir build_portable\ImageStudio_Portable\bin
    
    REM Copy executable
    copy release\ImageStudio.exe build_portable\ImageStudio_Portable\bin\
    
    REM Use windeployqt to automatically deploy all Qt dependencies
    cd build_portable\ImageStudio_Portable\bin
    windeployqt ImageStudio.exe
    cd ..\..\..
    
    REM Copy assets
    if exist "%PROJ_DIR%assets" (
        xcopy "%PROJ_DIR%assets" build_portable\ImageStudio_Portable\assets\ /E /I
    )
    
    REM Create launcher script
    echo @echo off > build_portable\ImageStudio_Portable\ImageStudio.bat
    echo cd /d "%%~dp0bin" >> build_portable\ImageStudio_Portable\ImageStudio.bat
    echo echo Starting ImageStudio... >> build_portable\ImageStudio_Portable\ImageStudio.bat
    echo ImageStudio.exe %%* >> build_portable\ImageStudio_Portable\ImageStudio.bat
    
    REM Create README for portable version
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
    
    echo.
    echo Portable package created in: build_portable\ImageStudio_Portable\
    echo.
    echo Creating ZIP file...
    
    REM Create ZIP file with version number
    set VERSION=2.0.0
    set ZIP_NAME=build_portable\ImageStudio_Portable_v%VERSION%-gui.zip
    
    REM Remove existing ZIP if it exists
    if exist "%ZIP_NAME%" del "%ZIP_NAME%"
    
    REM Create ZIP using PowerShell
    powershell -Command "Compress-Archive -Path 'build_portable\ImageStudio_Portable' -DestinationPath 'build_portable\ImageStudio_Portable_v2.0.0-gui.zip' -Force"
    
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo ✓ ZIP file created successfully: build_portable\ImageStudio_Portable_v2.0.0-gui.zip
        echo ✓ Portable package ready for distribution!
    ) else (
        echo.
        echo ⚠ Warning: Could not create ZIP file automatically.
        echo   You can create it manually by running:
        echo   powershell Compress-Archive -Path "build_portable\ImageStudio_Portable" -DestinationPath "build_portable\ImageStudio_Portable_v2.0.0-gui.zip"
    )
    echo.
) else (
    echo.
    echo Build failed. You may need to use Qt Creator instead.
    echo.
)

popd

pause
