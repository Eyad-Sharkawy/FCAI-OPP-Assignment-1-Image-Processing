# Image Studio v2.0.0

A modern Qt-based image processing application with a clean, intuitive interface.

## 🏗️ Project Structure

```
ImageStudio/
├── src/
│   ├── gui/                    # GUI-related source files
│   │   ├── image_studio.cpp   # Main application class
│   │   └── mainwindow.ui      # Qt Designer UI file
│   └── core/                  # Core functionality
│       └── Image_Class.h      # Image processing class
├── third_party/               # Third-party libraries
│   └── stb/                   # STB image library
│       ├── stb_image.h
│       └── stb_image_write.h
├── assets/                    # Application assets
│   └── icons/                 # Icon files
├── docs/                      # Essential documentation
│   ├── README.md              # Documentation hub
│   ├── USER_GUIDE.md          # Complete user manual
│   ├── DEVELOPER_GUIDE.md     # Development documentation
│   └── INSTALLATION.md        # Installation guide
├── scripts/                   # Build scripts
│   ├── build_release.bat
│   └── build_portable.bat
├── build_release/             # Release build output
├── build_portable/            # Portable build output
├── CMakeLists.txt            # CMake build configuration
├── ImageStudio.pro           # Qt project file
└── README.md                 # This file
```

## 🚀 Features

- **Image Loading**: Support for common image formats (JPEG, PNG, BMP, etc.)
- **Real-time Processing**: Live preview of all filters
- **Smart Resizing**: Aspect ratio preservation with dynamic window sizing
- **Professional Filters**:
  - Grayscale conversion
  - Black & White
  - Color inversion
  - Image merging
  - Flipping and rotation
  - Brightness adjustment
  - Frame addition
  - Cropping with selection
  - Edge detection (Sobel algorithm)
  - Resizing
  - Blur effects
  - Infrared effect
  - Purple filter
  - TV/CRT filter
- **Undo/Redo**: Full history management
- **Drag & Drop**: Easy image loading
- **Portable Build**: Standalone executable

## 🛠️ Building

### Using Qt Creator
1. Open `ImageStudio.pro` in Qt Creator
2. Configure the project
3. Build and run

### Using CMake
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Using Qt qmake
```bash
qmake ImageStudio.pro
make
```

## 📋 Requirements

- Qt 6.8.1 or later
- C++20 compatible compiler
- Windows (tested on Windows 10/11)

## 🎨 UI Design

The application uses Qt Designer for UI layout, providing:
- Clean, modern interface
- Responsive button grid
- Scrollable image display
- Progress indicators
- Status bar information

## 🔧 Technical Details

- **Framework**: Qt 6 with C++20
- **Image Processing**: Custom Image_Class with STB library
- **UI**: Qt Designer (.ui files)
- **Build System**: CMake + Qt qmake
- **Architecture**: MVC pattern with separation of concerns

## 📚 Documentation

Essential documentation is available in the `docs/` folder:

- **[User Guide](docs/USER_GUIDE.md)** - Complete user manual with step-by-step instructions
- **[Developer Guide](docs/DEVELOPER_GUIDE.md)** - Architecture, build system, and development guide
- **[Installation Guide](docs/INSTALLATION.md)** - Installation instructions for all platforms
- **[Documentation Hub](docs/README.md)** - Central documentation index

## 📝 License

This project is part of a C++ assignment and is for educational purposes.
