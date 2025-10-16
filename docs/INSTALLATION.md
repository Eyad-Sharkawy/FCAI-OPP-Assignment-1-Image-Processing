# Image Studio v3.0.1 - Installation Guide

## 📖 Table of Contents
1. [Quick Start](#quick-start)
2. [System Requirements](#system-requirements)
3. [Download Options](#download-options)
4. [Installation Methods](#installation-methods)
5. [Build from Source](#build-from-source)
6. [Troubleshooting](#troubleshooting)
7. [Uninstallation](#uninstallation)

## 🚀 Quick Start

### For End Users (Recommended)
1. Download `ImageStudio_Portable_v3.0.1-gui.zip`
2. Extract to any folder
3. Run `ImageStudio.bat`
4. Start processing images!

### For Developers
1. Clone the repository
2. Install Qt 6.8.1+
3. Build using CMake (recommended) or qmake
4. Run the application

## 💻 System Requirements

### Minimum Requirements
- **Operating System**: Windows 10 (64-bit)
- **Processor**: Intel Core i3 or AMD equivalent
- **Memory**: 4GB RAM
- **Storage**: 100MB free space
- **Graphics**: DirectX 11 compatible

### Recommended Requirements
- **Operating System**: Windows 11 (64-bit)
- **Processor**: Intel Core i5 or AMD equivalent
- **Memory**: 8GB RAM
- **Storage**: 500MB free space
- **Graphics**: Dedicated graphics card

### Development Requirements
- **Qt**: 6.8.1 or later
- **Compiler**: C++20 compatible (GCC 10+, MSVC 2019+, Clang 10+)
- **CMake**: 3.20+ (optional)
- **Git**: For version control

## 📦 Download Options

### Option 1: Portable Version (Recommended for Users)
- **File**: `ImageStudio_Portable_v3.0.1-gui.zip`
- **Size**: ~25MB
- **Includes**: Executable + all dependencies
- **Installation**: None required
- **Best for**: End users, quick testing

### Option 2: Source Code (For Developers)
- **Repository**: GitHub repository
- **Size**: ~5MB (source only)
- **Includes**: Source code, build files, documentation
- **Installation**: Build required
- **Best for**: Developers, customization

### Option 3: Release Build (For Advanced Users)
- **File**: `ImageStudio_v3.0.1.exe`
- **Size**: ~15MB
- **Includes**: Executable only
- **Installation**: Requires Qt runtime
- **Best for**: Users with Qt installed

## 🔧 Installation Methods

### Method 1: Portable Installation (Easiest)

#### Step 1: Download
1. Go to the Releases page of the repository
2. Download `ImageStudio_Portable_v3.0.1-gui.zip`

#### Step 2: Extract
1. Right-click the ZIP file
2. Select "Extract All..."
3. Choose destination folder (e.g., `C:\Programs\ImageStudio\`)
4. Click "Extract"

#### Step 3: Run
1. Navigate to the extracted folder
2. Double-click `ImageStudio.bat`
3. The application will start

#### Step 4: Create Shortcut (Optional)
1. Right-click `ImageStudio.bat`
2. Select "Create shortcut"
3. Move shortcut to Desktop or Start Menu

### Method 2: System Installation

#### Prerequisites
- Install Qt 6.8.1+ from [qt.io](https://www.qt.io/download)
- Add Qt to system PATH

#### Installation Steps
1. Download release build
2. Place executable in desired location
3. Ensure Qt libraries are accessible
4. Run the application

### Method 3: Package Manager (Future)

#### Chocolatey (Windows)
```powershell
# Future implementation
choco install imagestudio
```

#### Scoop (Windows)
```powershell
# Future implementation
scoop install imagestudio
```

## 🛠️ Build from Source

### Prerequisites Installation

#### Windows with Qt Creator
1. Download Qt Creator from [qt.io](https://www.qt.io/download)
2. Install Qt 6.8.1 with MinGW compiler
3. Ensure CMake is installed (optional)

#### Windows with Visual Studio
1. Install Visual Studio 2019+ with C++ support
2. Install Qt 6.8.1 with MSVC compiler
3. Install CMake 3.20+

#### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake qt6-base-dev qt6-tools-dev

# Install Qt Creator (optional)
sudo apt install qtcreator
```

#### macOS
```bash
# Install using Homebrew
brew install qt6 cmake

# Or download from qt.io
```

### Build Process

#### Method 1: Qt Creator (qmake project)
1. Open Qt Creator
2. Open `ImageStudio.pro`
3. Configure project (select kit)
4. Build (Ctrl+B)
5. Run (Ctrl+R)

#### Method 2: Command Line (qmake)
```bash
# Generate Makefile
qmake ImageStudio.pro

# Build (Windows)
mingw32-make

# Build (Linux/macOS)
make
```

#### Method 3: CMake (Recommended)
Windows (Visual Studio generator):
```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release   # or Debug
```

Linux/macOS or MinGW (single-config generators):
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build build -j 8

# Run (from build dir)
./bin/PhotoSmith       # Linux/macOS (name may vary)
bin/PhotoSmith.exe     # Windows
```

#### Method 4: Build Scripts (Windows)
```bat
scripts\build_release.bat    # CMake Release -> cmake-build-release\bin\ImageStudio.exe
scripts\build_portable.bat   # Build + windeployqt + ZIP
scripts\build_all.bat        # Clean, build, deploy, zip (one-click)
scripts\test_app.bat         # Quick smoke test launcher
```

### Build Configuration Options

#### Debug Build
```bash
# CMake
cmake -S . -B cmake-build-debug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build cmake-build-debug -j 8
```

#### Release Build
```bash
# CMake
cmake -S . -B cmake-build-release -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build cmake-build-release -j 8
```

#### Custom Configuration
```bash
# CMake with custom options
cmake -DCMAKE_BUILD_TYPE=Release \
      -DQT_DIR=/path/to/qt \
      -DCMAKE_INSTALL_PREFIX=/usr/local \
      ..
```

## 🔍 Troubleshooting

### Common Installation Issues

#### "Application won't start"
**Symptoms**: Double-clicking does nothing or shows error
**Solutions**:
1. Check Windows version (64-bit required)
2. Install Visual C++ Redistributable
3. Run as administrator
4. Check antivirus settings

#### "Missing DLL files"
**Symptoms**: Error about missing .dll files
**Solutions**:
1. Use portable version (includes all DLLs)
2. Install Qt runtime libraries
3. Add Qt bin directory to PATH

#### "Qt not found"
**Symptoms**: Build fails with Qt-related errors
**Solutions**:
1. Install Qt 6.8.1+
2. Set QTDIR environment variable
3. Add Qt to system PATH
4. Use Qt Creator instead

#### "Compiler not found"
**Symptoms**: Build fails with compiler errors
**Solutions**:
1. Install MinGW or Visual Studio
2. Check compiler PATH
3. Use Qt Creator (includes compiler)

### Build Issues

#### "C++20 not supported"
**Solutions**:
1. Update compiler to C++20 compatible version
2. Use Qt Creator with newer compiler
3. Check CMake configuration

#### "Memory allocation failed"
**Solutions**:
1. Close other applications
2. Use smaller images
3. Check available RAM
4. Build in Release mode

#### "Linker errors"
**Solutions**:
1. Check library paths
2. Ensure all dependencies are installed
3. Clean and rebuild
4. Check Qt installation

### Runtime Issues

#### "Image won't load"
**Solutions**:
1. Check file format (JPEG, PNG, BMP supported)
2. Verify file is not corrupted
3. Check file permissions
4. Try different image

#### "Application crashes"
**Solutions**:
1. Run in debug mode
2. Check image dimensions (very large images)
3. Update graphics drivers
4. Report bug with details

#### "Slow performance"
**Solutions**:
1. Use smaller images
2. Close other applications
3. Check available memory
4. Update hardware drivers

### Getting Help

#### Check Logs
- Look for error messages in console
- Check Windows Event Viewer
- Enable debug output in Qt Creator

#### Common Solutions
1. **Restart**: Close and reopen application
2. **Rebuild**: Clean and rebuild project
3. **Reinstall**: Download fresh copy
4. **Update**: Check for newer version

#### Report Issues
When reporting issues, include:
- Operating system version
- Image Studio version
- Error messages
- Steps to reproduce
- System specifications

## 🗑️ Uninstallation

### Portable Version
1. Delete the Image Studio folder
2. Remove any shortcuts created
3. No registry entries to clean

### System Installation
1. Delete executable file
2. Remove Qt libraries (if not used by other apps)
3. Clean up any shortcuts
4. Remove from PATH (if added)

### Development Environment
1. Uninstall Qt Creator
2. Remove Qt installation directory
3. Clean up environment variables
4. Remove build directories

### Complete Cleanup
```bash
# Remove all build artifacts
rm -rf build*/
rm -rf cmake-build-*/
rm -f *.pro.user
rm -f Makefile*

# Remove Qt Creator files
rm -rf .qt/
```

## 📋 Installation Checklist

### For End Users
- [ ] Downloaded portable version
- [ ] Extracted to desired location
- [ ] Created desktop shortcut (optional)
- [ ] Tested with sample image
- [ ] Verified all features work

### For Developers
- [ ] Installed Qt 6.8.1+
- [ ] Installed C++20 compiler
- [ ] Cloned repository
- [ ] Built successfully
- [ ] Ran tests
- [ ] Verified functionality

### For System Administrators
- [ ] Verified system requirements
- [ ] Installed on test system
- [ ] Verified network compatibility
- [ ] Created deployment package
- [ ] Documented installation process

---

**Installation Guide v3.0.1** - Get Image Studio running in minutes! 🚀

For additional help, check the [User Guide](USER_GUIDE.md) or [Developer Guide](DEVELOPER_GUIDE.md).
