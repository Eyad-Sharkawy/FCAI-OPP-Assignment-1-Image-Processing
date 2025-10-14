# CLion Setup Guide for Photo Smith

## Quick Setup

1. **Run the setup script:**
   ```bash
   ./setup_clion.bat
   ```

2. **Open in CLion:**
   - Open CLion
   - File → Open → Select the project directory
   - CLion should automatically detect the CMake configuration

## Manual Setup

If the automatic setup doesn't work, follow these steps:

### Step 1: Clean Build Directories
```bash
# Remove any existing build directories
rmdir /s /q cmake-build-debug
rmdir /s /q cmake-build-release
```

### Step 2: Configure CMake
```bash
# Configure with Ninja generator (recommended)
cmake -S . -B cmake-build-debug -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake -S . -B cmake-build-release -G "Ninja" -DCMAKE_BUILD_TYPE=Release
```

### Step 3: Open in CLion
1. Open CLion
2. File → Open → Select project directory
3. If you get generator errors:
   - File → Reload CMake Project
   - File → Invalidate Caches and Restart

## Troubleshooting

### Generator Compatibility Issues

**Error:** "Cannot generate into ... It was created with incompatible generator"

**Solution:**
1. Delete the build directory manually
2. Run the setup script again
3. Or manually configure with the correct generator

### Qt Compatibility Issues

**Error:** "cannot open file 'mingw32.lib'"

**Solution:**
- This happens when using Visual Studio generator with MinGW Qt
- Use Ninja generator instead (recommended)
- Or install Qt MSVC version

### CLion Not Detecting CMake

**Solution:**
1. Check that `.clion/cmake.xml` exists
2. File → Reload CMake Project
3. File → Invalidate Caches and Restart
4. Check CLion's CMake settings (File → Settings → Build → CMake)

## Build Commands

```bash
# Build debug version
cmake --build cmake-build-debug

# Build release version
cmake --build cmake-build-release

# Run the application
cmake-build-debug/bin/PhotoSmith.exe
```

## Project Structure

```
Photo Smith/
├── src/                    # Source code
├── assets/                 # Assets (icons, etc.)
├── docs/                   # Documentation
├── cmake-build-debug/      # Debug build output
├── cmake-build-release/    # Release build output
├── CMakeLists.txt          # CMake configuration
├── CMakePresets.json       # CMake presets
└── setup_clion.bat         # CLion setup script
```

## Supported Generators

- **Ninja** (Recommended for CLion) ✅
- **Visual Studio 17 2022** (Requires Qt MSVC)
- **MinGW Makefiles** (Command line builds)

## Need Help?

If you're still having issues:
1. Check the build logs in CLion
2. Try the manual setup steps
3. Ensure Qt 6.8.1 is properly installed
4. Verify MinGW tools are in your PATH
