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
pushd build_portable

REM Generate Makefile with qmake (use absolute path to .pro)
qmake "%PROJ_DIR%ImageStudio.pro"

REM Build the project using mingw32-make
mingw32-make -f Makefile.Release

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Build successful! Creating portable package...
    
    REM Create portable directory structure
    mkdir ImageStudio_Portable
    mkdir ImageStudio_Portable\bin
    
    REM Copy executable
    copy release\ImageStudio.exe ImageStudio_Portable\bin\
    
    REM Use windeployqt to automatically deploy all Qt dependencies
    cd ImageStudio_Portable\bin
    windeployqt ImageStudio.exe
    cd ..\..
    
    REM Copy assets
    if exist "%PROJ_DIR%assets" (
        xcopy "%PROJ_DIR%assets" ImageStudio_Portable\assets\ /E /I
    )
    
    REM Create launcher script
    echo @echo off > ImageStudio_Portable\ImageStudio.bat
    echo cd /d "%%~dp0bin" >> ImageStudio_Portable\ImageStudio.bat
    echo echo Starting ImageStudio... >> ImageStudio_Portable\ImageStudio.bat
    echo ImageStudio.exe %%* >> ImageStudio_Portable\ImageStudio.bat
    
    REM Create README for portable version
    echo Image Studio - Portable Version > ImageStudio_Portable\README.txt
    echo. >> ImageStudio_Portable\README.txt
    echo This is a portable version of Image Studio that includes all necessary >> ImageStudio_Portable\README.txt
    echo Qt libraries and dependencies. >> ImageStudio_Portable\README.txt
    echo. >> ImageStudio_Portable\README.txt
    echo To run: >> ImageStudio_Portable\README.txt
    echo 1. Double-click ImageStudio.bat >> ImageStudio_Portable\README.txt
    echo 2. Or run bin\ImageStudio.exe directly >> ImageStudio_Portable\README.txt
    echo. >> ImageStudio_Portable\README.txt
    echo Features: >> ImageStudio_Portable\README.txt
    echo - All image processing filters >> ImageStudio_Portable\README.txt
    echo - Drag and drop image loading >> ImageStudio_Portable\README.txt
    echo - Undo/Redo functionality >> ImageStudio_Portable\README.txt
    echo - Responsive UI >> ImageStudio_Portable\README.txt
    echo - Professional interface >> ImageStudio_Portable\README.txt
    echo. >> ImageStudio_Portable\README.txt
    echo No installation required! >> ImageStudio_Portable\README.txt
    
    echo.
    echo Portable package created in: build_portable\ImageStudio_Portable\
    echo.
    echo To create a ZIP file, run:
    echo powershell Compress-Archive -Path "ImageStudio_Portable" -DestinationPath "ImageStudio_Portable.zip"
    echo.
) else (
    echo.
    echo Build failed. You may need to use Qt Creator instead.
    echo.
)

popd
popd

pause
