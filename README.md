# Photo Smith v3.5.0

A modern, professional Qt-based image processing application with a clean, intuitive interface and comprehensive image manipulation capabilities.

## 🎯 Overview

Photo Smith is a powerful desktop application built with Qt 6 and C++20 that provides a complete suite of image processing tools. It features a modern GUI with drag-and-drop support, real-time progress tracking, and comprehensive undo/redo functionality. The application supports multiple image formats and provides both basic and advanced image processing filters.

## ✨ Key Features

- **🖼️ Multi-Format Support**: Load and save images in PNG, JPEG, BMP, and TGA formats
- **🎨 15+ Professional Filters**: From basic color adjustments to advanced effects
- **⚡ Real-Time Processing**: Live preview with progress tracking and cancellation support
- **🔄 Unlimited Undo/Redo**: Complete history management with configurable memory limits
- **🖱️ Drag & Drop**: Easy image loading with intuitive drag-and-drop interface
- **📱 Responsive UI**: Smart resizing with aspect ratio preservation
- **🚀 High Performance**: Optimized algorithms with Qt integration
- **📦 Portable**: Standalone executable with no installation required

## 🏗️ Project Structure

```
PhotoSmith/
├── src/                            # Source code
│   ├── gui/                        # GUI components
│   │   ├── image_studio.cpp        # Main Qt application class
│   │   └── mainwindow.ui           # Qt Designer UI layout
│   └── core/                       # Core functionality
│       ├── image/                  # Image data structure + STB I/O
│       │   ├── Image_Class.h       # Core image class with STB integration
│       │   └── Image_Class.cpp     # STB library implementation
│       ├── filters/                # Image processing filters
│       │   ├── ImageFilters.h      # Filter algorithms with Qt integration
│       │   └── ImageFilters.cpp    # Filter implementations
│       ├── history/                # Undo/redo management
│       │   └── HistoryManager.h    # Stack-based history system
│       └── io/                     # File I/O utilities
│           └── ImageIO.h           # Qt-integrated file operations
├── third_party/                    # External libraries
│   └── stb/                        # STB image library
│       ├── stb_image.h             # Image loading
│       └── stb_image_write.h       # Image saving
├── assets/                         # Application resources
│   └── icons/                      # Icon files
├── docs/                           # Comprehensive documentation
│   ├── README.md                   # Documentation hub
│   ├── USER_GUIDE.md               # Complete user manual
│   ├── DEVELOPER_GUIDE.md          # Development documentation
│   └── INSTALLATION.md             # Installation guide
├── scripts/                        # Build automation (Windows)
│   ├── build_release.bat           # CMake Release build
│   ├── build_portable.bat          # Build + deploy + ZIP
│   ├── build_all.bat               # One-click build and package
│   └── test_app.bat                # Quick smoke test
├── cmake-build-*/                  # CMake build outputs
├── build_portable/                 # Portable build output
├── CMakeLists.txt                  # CMake build configuration
├── PhotoSmith.pro                  # Qt project file (legacy)
└── README.md                       # This file
```

## 🎨 Image Processing Filters

### Basic Color Operations
- **Grayscale**: Convert color images to grayscale using average RGB values
- **Black & White**: Binary conversion with threshold-based processing
- **Invert**: Color inversion for negative effects
- **Dark & Light**: Brightness adjustment with configurable intensity

### Geometric Transformations
- **Flip**: Horizontal and vertical image flipping
- **Rotate**: 90°, 180°, and 270° rotation support
- **Resize**: Custom dimension resizing with nearest-neighbor interpolation
- **Crop**: Interactive selection-based cropping with rubber band selection

### Advanced Effects
- **Edge Detection**: Sobel algorithm with Gaussian blur preprocessing
- **Blur**: 15x15 average blur kernel for soft effects
- **Infrared**: Simulated infrared photography with red channel emphasis
- **Purple Filter**: Color tint with enhanced red/blue channels
- **TV/CRT Filter**: Vintage monitor simulation with scan lines and noise

### Special Features
- **Frame**: Decorative borders with simple and decorated styles
- **Merge**: Image combination by averaging pixel values
- **Reset**: Restore original image state
- **Undo/Redo**: Complete history management with configurable limits

## 🛠️ Technical Features

- **Real-Time Processing**: Live preview with progress tracking
- **Cancellation Support**: Long-running operations can be cancelled
- **Memory Management**: Efficient image state storage with RAII principles
- **Exception Safety**: Comprehensive error handling throughout
- **Cross-Platform**: Qt-based design for broad compatibility
- **Thread Safety**: Atomic operations for cancellation support

## 🛠️ Building

### Using Qt Creator
1. Open `PhotoSmith.pro` in Qt Creator
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
qmake PhotoSmith.pro
make
```

### Using Windows build scripts
```bat
scripts\build_release.bat   
scripts\build_portable.bat  
scripts\build_all.bat       
scripts\test_app.bat        
```

## 📋 System Requirements

### Minimum Requirements
- **Operating System**: Windows 10 (64-bit)
- **Memory**: 4GB RAM
- **Storage**: 100MB free space
- **Graphics**: DirectX 11 compatible

### Recommended Requirements
- **Operating System**: Windows 11 (64-bit)
- **Memory**: 8GB RAM
- **Storage**: 500MB free space
- **Graphics**: Dedicated graphics card

### Development Requirements
- **Qt**: 6.8.1 or later
- **Compiler**: C++20 compatible (GCC 10+, MSVC 2019+, Clang 10+)
- **CMake**: 3.20+ (optional)
- **Git**: For version control

## 🎨 User Interface

The application features a modern, intuitive interface designed with Qt Designer:

- **Clean Layout**: Organized button grid with logical grouping
- **Responsive Design**: Smart resizing with aspect ratio preservation
- **Drag & Drop**: Intuitive image loading with visual feedback
- **Progress Tracking**: Real-time progress bars for long operations
- **Status Updates**: Informative status bar with operation details
- **Menu Integration**: Complete menu system with keyboard shortcuts

## 🔧 Technical Architecture

### Core Technologies
- **Framework**: Qt 6.8.1 with C++20
- **Image Library**: STB (Sean T. Barrett) for robust I/O
- **Build System**: CMake (primary), qmake (legacy)
- **UI Framework**: Qt Designer with signal/slot architecture

### Key Components
- **Image Class**: Core data structure with STB integration
- **ImageFilters**: Processing algorithms with Qt integration
- **HistoryManager**: Stack-based undo/redo system
- **ImageIO**: Qt-integrated file operations
- **MainWindow**: Qt application with comprehensive event handling

### Design Patterns
- **MVC Architecture**: Clear separation of concerns
- **RAII**: Automatic resource management
- **Observer Pattern**: Qt's signal/slot mechanism
- **Command Pattern**: Undo/redo implementation

## 📚 Documentation

Comprehensive documentation is available in the `docs/` folder:

- **[Documentation Hub](docs/README.md)** - Central documentation index and overview
- **[User Guide](docs/USER_GUIDE.md)** - Complete user manual with step-by-step instructions
- **[Developer Guide](docs/DEVELOPER_GUIDE.md)** - Architecture, build system, and development guide
- **[Installation Guide](docs/INSTALLATION.md)** - Installation instructions for all platforms

### API Documentation (Doxygen)
Generate browsable API docs from source comments. A ready-to-use `Doxyfile` is included.

1) Install tools (any one method)

- Chocolatey (Windows):
  - `choco install doxygen.install graphviz -y`
- Winget (Windows):
  - `winget install Doxygen.Doxygen`
  - `winget install Graphviz.Graphviz`
- Manual installers:
  - Doxygen: `https://www.doxygen.nl/download.html`
  - Graphviz: `https://graphviz.org/download/`

2) Verify installation

```powershell
doxygen -v
dot -V
```

3) Generate docs (from repository root)

```powershell
doxygen Doxyfile
```

4) Open docs

- `docs/api/html/index.html`

Notes:
- Graphviz enables class/dir diagrams; it is optional but recommended.
- If PATH isn’t updated, start a new terminal or call the full exe path (e.g., `"C:\\Program Files\\doxygen\\bin\\doxygen.exe"`).

#### Comment Style Quick Reference

Add Doxygen-style comments in headers and important implementation files.

```cpp
/// \file ImageFilters.h
/// \brief Image processing filters and utilities.

/** \class ImageFilters
 *  \brief A collection of static image processing functions.
 */
class ImageFilters {
public:
    /** \brief Convert an image to grayscale.
     *  \param input The input image.
     *  \return A new grayscale image.
     */
    static Image grayscale(const Image& input);
};

/** \brief Apply a box blur.
 *  \param input Source image.
 *  \param kernelSize Odd kernel size (e.g. 3, 5, 15).
 *  \return Blurred image.
 *  \throws std::invalid_argument if kernelSize is not odd or < 3.
 */
Image blur(const Image& input, int kernelSize);
```

Grouping related APIs into modules improves navigation:

```cpp
/** \defgroup Filters Image Filters
 *  High-level filter operations.
 *  @{ */
Image grayscale(const Image& input);
Image invert(const Image& input);
/** @} */
```

Qt-specific tips:
- Prefer documenting in headers (`.h`) where symbols are declared.
- Use `\brief` first sentence for summaries shown in lists.
- Document signals/slots like regular functions.

#### Cleaning/Regenerating

```powershell
Remove-Item -Recurse -Force docs/api/html -ErrorAction SilentlyContinue
doxygen Doxyfile
```

#### Troubleshooting
- Ensure `HAVE_DOT = YES` in `Doxyfile` to enable diagrams.
- If diagrams are missing, verify `dot -V` works and Graphviz is on PATH.
- If pages are empty, confirm `INPUT` in `Doxyfile` includes `src` and `README.md`.

## 🤝 Contributing

### Development Team
- **Ahmed Mohamed ElSayed Tolba** (ID: 20242023)
- **Eyad Mohamed Saad Ali** (ID: 20242062)
- **Tarek Sami Mohamed Mohamed** (ID: 20242190)

### Getting Started
1. Read the [Developer Guide](docs/DEVELOPER_GUIDE.md)
2. Set up your development environment
3. Fork the repository
4. Create a feature branch
5. Make your changes
6. Submit a pull request

### Code Style
- **Language**: C++20
- **Framework**: Qt 6
- **Naming**: camelCase for variables, PascalCase for classes
- **Indentation**: 4 spaces
- **Comments**: Comprehensive documentation for all public APIs

## 📝 License

This project is developed as part of a C++ Object-Oriented Programming assignment at the Faculty of Computers and Artificial Intelligence, Cairo University. It is intended for educational purposes and demonstrates modern C++ and Qt development practices.

## 🔗 Links

- **GitHub Repository**: [Image Studio on GitHub](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Processing)
- **Releases**: [Latest Releases](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Processing/releases)
- **Issues**: [Report Issues](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Processing/issues)

---

**Photo Smith v3.5.0** - Professional Image Processing Made Simple! 🎨

*Last updated: October 14, 2025*
