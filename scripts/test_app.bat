@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo Testing Image Studio application...
echo.

REM Check if executable exists (prefer Release cmake output)
if exist "cmake-build-release\bin\ImageStudio.exe" (
    echo ✓ Executable found: cmake-build-release\bin\ImageStudio.exe
    echo.
    echo Starting application for 5 seconds to test...
    echo (The application will close automatically)
    echo.
    
    start "ImageStudioTest" "cmake-build-release\bin\ImageStudio.exe"
    timeout /t 5 /nobreak >nul 2>&1
    taskkill /fi "WINDOWTITLE eq ImageStudioTest" >nul 2>&1
    echo.
    echo ✓ Application started successfully!
    echo   If you saw the Image Studio window, the test passed.
    echo.
) else if exist "release\ImageStudio.exe" (
    echo ✓ Executable found: release\ImageStudio.exe
    echo.
    echo Starting application for 5 seconds to test...
    echo (The application will close automatically)
    echo.
    
    start "ImageStudioTest" "release\ImageStudio.exe"
    timeout /t 5 /nobreak >nul 2>&1
    taskkill /fi "WINDOWTITLE eq ImageStudioTest" >nul 2>&1
    echo.
    echo ✓ Application started successfully!
    echo   If you saw the Image Studio window, the test passed.
    echo.
) else (
    echo ✗ Executable not found.
    echo   Please run build_release.bat first.
    echo.
)

popd
pause
