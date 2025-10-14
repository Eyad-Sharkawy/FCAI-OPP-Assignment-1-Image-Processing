@echo off
setlocal enabledelayedexpansion

REM Determine project root from script location
set SCRIPT_DIR=%~dp0
set PROJ_DIR=%SCRIPT_DIR%..\
pushd "%PROJ_DIR%"

echo Testing Photo Smith application...
echo.

REM Check if executable exists (prefer Release cmake output)
if exist "cmake-build-release\bin\PhotoSmith.exe" (
    echo ✓ Executable found: cmake-build-release\bin\PhotoSmith.exe
    echo.
    echo Starting application for 5 seconds to test...
    echo (The application will close automatically)
    echo.
    
    start "PhotoSmithTest" "cmake-build-release\bin\PhotoSmith.exe"
    timeout /t 5 /nobreak >nul 2>&1
    taskkill /fi "WINDOWTITLE eq PhotoSmithTest" >nul 2>&1
    echo.
    echo ✓ Application started successfully!
    echo   If you saw the Photo Smith window, the test passed.
    echo.
) else if exist "release\PhotoSmith.exe" (
    echo ✓ Executable found: release\PhotoSmith.exe
    echo.
    echo Starting application for 5 seconds to test...
    echo (The application will close automatically)
    echo.
    
    start "PhotoSmithTest" "release\PhotoSmith.exe"
    timeout /t 5 /nobreak >nul 2>&1
    taskkill /fi "WINDOWTITLE eq PhotoSmithTest" >nul 2>&1
    echo.
    echo ✓ Application started successfully!
    echo   If you saw the Photo Smith window, the test passed.
    echo.
) else (
    echo ✗ Executable not found.
    echo   Please run build_release.bat first.
    echo.
)

popd
pause
