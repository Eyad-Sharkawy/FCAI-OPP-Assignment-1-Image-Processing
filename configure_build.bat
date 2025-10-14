@echo off
echo ========================================
echo    Photo Smith - Build Configuration
echo ========================================
echo.

REM Clean any existing build directories
if exist "cmake-build-debug" rmdir /s /q cmake-build-debug
if exist "cmake-build-release" rmdir /s /q cmake-build-release

echo Available build configurations:
echo 1. Ninja (Recommended for CLion)
echo 2. Visual Studio 2022
echo 3. MinGW Makefiles
echo.

set /p choice="Select build configuration (1-3): "

if "%choice%"=="1" (
    echo Configuring with Ninja generator...
    cmake -S . -B cmake-build-debug -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
    cmake -S . -B cmake-build-release -G "Ninja" -DCMAKE_BUILD_TYPE=Release
    echo ✓ Ninja configuration complete
) else if "%choice%"=="2" (
    echo Configuring with Visual Studio 2022 generator...
    cmake -S . -B cmake-build-debug -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Debug
    cmake -S . -B cmake-build-release -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release
    echo ✓ Visual Studio configuration complete
) else if "%choice%"=="3" (
    echo Configuring with MinGW Makefiles generator...
    cmake -S . -B cmake-build-debug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
    cmake -S . -B cmake-build-release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
    echo ✓ MinGW Makefiles configuration complete
) else (
    echo Invalid choice. Using default Ninja configuration...
    cmake -S . -B cmake-build-debug -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
    cmake -S . -B cmake-build-release -G "Ninja" -DCMAKE_BUILD_TYPE=Release
)

echo.
echo ========================================
echo           CONFIGURATION COMPLETE!
echo ========================================
echo.
echo You can now:
echo - Open the project in CLion
echo - Build using: cmake --build cmake-build-debug
echo - Run the application: cmake-build-debug\bin\PhotoSmith.exe
echo.
pause
