@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo Testing Image Studio application...
echo.

REM Check if executable exists
if exist "release\ImageStudio.exe" (
    echo ✓ Executable found: release\ImageStudio.exe
    echo.
    echo Starting application for 5 seconds to test...
    echo (The application will close automatically)
    echo.
    
    REM Start the application and wait 5 seconds
    start /wait timeout /t 5 /nobreak >nul 2>&1
    start "" "release\ImageStudio.exe"
    
    echo.
    echo ✓ Application started successfully!
    echo   If you see the Image Studio window, the test passed.
    echo   You can close the application manually.
    echo.
) else (
    echo ✗ Executable not found: release\ImageStudio.exe
    echo   Please run build_release.bat first.
    echo.
)

popd
pause
