@echo off
echo ========================================
echo    Photo Smith - CLion Setup
echo ========================================
echo.

REM Clean existing build directories
if exist "cmake-build-debug" rmdir /s /q cmake-build-debug
if exist "cmake-build-release" rmdir /s /q cmake-build-release

echo Setting up Photo Smith for CLion...
echo.

REM Check if Qt MSVC version is available
if exist "C:\Qt\6.8.1\msvc2022_64" (
    echo Found Qt MSVC 2022 installation - using Visual Studio generator
    cmake -S . -B cmake-build-debug -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Debug
    cmake -S . -B cmake-build-release -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
) else if exist "C:\Qt\6.8.1\msvc2019_64" (
    echo Found Qt MSVC 2019 installation - using Visual Studio generator
    cmake -S . -B cmake-build-debug -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Debug
    cmake -S . -B cmake-build-release -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
) else (
    echo Qt MSVC version not found - using Ninja with MinGW Qt
    echo Note: This may cause linking issues with Visual Studio generator
    cmake -S . -B cmake-build-debug -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
    cmake -S . -B cmake-build-release -G "Ninja" -DCMAKE_BUILD_TYPE=Release
)

echo.
echo ========================================
echo           CLION SETUP COMPLETE!
echo ========================================
echo.
echo Next steps:
echo 1. Open the project in CLion
echo 2. CLion should now recognize the build configuration
echo 3. If you still get generator errors, try:
echo    - File ^> Reload CMake Project
echo    - File ^> Invalidate Caches and Restart
echo.
echo Build directories created:
if exist "cmake-build-debug" echo ✓ cmake-build-debug
if exist "cmake-build-release" echo ✓ cmake-build-release
echo.
pause
