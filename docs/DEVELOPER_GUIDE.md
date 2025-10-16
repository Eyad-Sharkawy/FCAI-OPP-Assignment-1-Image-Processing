# Photo Smith v3.0.1 - Developer Guide

## 📖 Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Build System](#build-system)
4. [Code Structure](#code-structure)
5. [Adding New Features](#adding-new-features)
6. [Testing](#testing)
7. [Debugging](#debugging)
8. [Contributing](#contributing)

## 🏗️ Project Overview

Photo Smith is a Qt6-based image processing application built with C++20. It provides a modern GUI for various image manipulation operations using a custom image processing library.

### Key Technologies
- **Framework**: Qt 6.8.1
- **Language**: C++20
- **Build Systems**: CMake (primary), qmake (legacy)
- **Image Library**: STB (stb_image, stb_image_write)
- **UI Design**: Qt Designer (.ui files)

## 🏛️ Architecture

### High-Level Architecture
```
┌───────────────────────────────────────────────────────────┐
│                    Presentation Layer                     │
│  ┌─────────────────┐  ┌─────────────────────────────────┐ │
│  │   Main Window   │  │        Qt Designer UI           │ │
│  │  (QMainWindow)  │  │      (mainwindow.ui)            │ │
│  └─────────────────┘  └─────────────────────────────────┘ │
└───────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────┐
│                   Application Layer                      │
│  ┌─────────────────────────────────────────────────────┐ │
│  │            SimpleImageApp Class                     │ │
│  │  - Signal/Slot Management                           │ │
│  │  - UI Event Handling                                │ │
│  │  - Image State Management                           │ │
│  └─────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────┐
│                    Business Logic                        │
│  ┌─────────────────────────────────────────────────────┐ │
│  │              Image_Class                            │ │
│  │  - Image Data Structure                             │ │
│  │  - Processing Algorithms                            │ │
│  │  - File I/O Operations                              │ │
│  └─────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
┌──────────────────────────────────────────────────────────┐
│                    Data Access Layer                     │
│  ┌─────────────────────────────────────────────────────┐ │
│  │                STB Library                          │ │
│  │  - Image Loading (stb_image.h)                      │ │
│  │  - Image Saving (stb_image_write.h)                 │ │
│  └─────────────────────────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
```

### Design Patterns
- **MVC (Model-View-Controller)**: Separation of UI, logic, and data
- **Observer Pattern**: Qt's signal/slot mechanism
- **Command Pattern**: Undo/Redo system
- **Factory Pattern**: Image processing operations

## 🔨 Build System

### Prerequisites
- Qt 6.8.1 or later
- C++20 compatible compiler (GCC 10+, MSVC 2019+, Clang 10+)
- CMake 3.20+ (optional)
- Windows 10/11 (64-bit)

### Qt qmake Build (Legacy)
```bash
# Generate Makefile
qmake ImageStudio.pro

# Build (Windows)
mingw32-make

# Build (Linux/macOS)
make
```

### CMake Build (Recommended)
```bash
# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .
```

### Build Scripts
- `scripts/build_release.bat` - Release build
- `scripts/build_portable.bat` - Portable build with ZIP creation
- `scripts/build_all.bat` - Clean, build, deploy Qt libraries, and zip
- `scripts/test_app.bat` - Quick smoke test runner

## 📁 Code Structure

### Directory Layout
```
ImageStudio/
├── src/
│   ├── gui/                    # GUI Components
│   │   ├── image_studio.cpp   # Main application class
│   │   └── mainwindow.ui      # Qt Designer UI file
│   └── core/                  # Core Functionality
│       ├── filters/           # Image processing filters (progress + cancel)
│       │   ├── ImageFilters.h
│       │   └── ImageFilters.cpp
│       ├── image/             # Image container + STB-backed I/O
│       │   ├── Image_Class.h
│       │   └── Image_Class.cpp
│       ├── history/           # Undo/redo management
│       │   └── HistoryManager.h
│       └── io/                # File I/O helpers
│           └── ImageIO.h
├── third_party/               # External Libraries
│   └── stb/                   # STB image library
├── docs/                      # Documentation
├── assets/                    # Resources
├── scripts/                   # Build Scripts
└── build_*/                   # Build Output
```

### Key Classes

#### SimpleImageApp (image_studio.cpp)
```cpp
class SimpleImageApp : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow ui;              // UI components
    Image currentImage;             // Current image data
    bool hasImage;                  // Image loaded flag
    HistoryManager history{20};     // Undo/redo history abstraction
    
    // Delegates to ImageFilters (see src/core/filters/ImageFilters.h)
};
```

#### Image_Class (Image_Class.h)
```cpp
class Image
{
private:
    int width, height, channels;
    unsigned char* data;
    
public:
    // Constructors/Destructors
    Image(int w, int h, int c);
    ~Image();
    
    // Pixel access
    unsigned char& operator()(int x, int y, int channel);
    
    // File operations
    bool loadNewImage(const char* filename);
    bool saveImage(const char* filename);
    
    // Processing methods
    Image grayscale();
    Image flipHorizontally();
    Image flipVertically();
    // ... more processing methods
};
```

## 🚀 Adding New Features

### Adding a New Filter

#### Step 1: Add UI Button
1. Open `src/gui/mainwindow.ui` in Qt Designer
2. Add a new `QPushButton` to the button layout
3. Set appropriate properties (name, text, enabled state)

#### Step 2: Implement Filter Logic
```cpp
// In Image_Class.h
Image yourNewFilter();

// In Image_Class implementation
Image Image::yourNewFilter()
{
    Image result(width, height, channels);
    
    // Your filter algorithm here
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Process pixel at (x, y)
            // Set result pixel
        }
    }
    
    return result;
}
### Undo/Redo and I/O Architecture (v2.0.0)

To improve separation of concerns, the GUI delegates history and file I/O:

- History is managed by `src/core/HistoryManager.h`.
  - Call `history.pushUndo(currentImage)` immediately before any mutating filter.
  - Invoke `history.undo(currentImage)` and `history.redo(currentImage)` from the corresponding slots.
  - Reset history on new loads/unloads via `history.clear()`.

- Image loading/saving is wrapped by `src/core/ImageIO.h`.
  - Load: `originalImage = ImageIO::loadFromFile(path); currentImage = originalImage;`
  - Save: `ImageIO::saveToFile(currentImage, path);`

Benefits:
- Single-responsibility, testability, and consistent behavior across load/unload/drag-drop.
- Centralized bounds on history size to control memory usage.

```

#### Step 3: Connect UI to Logic
```cpp
// In SimpleImageApp constructor
connect(ui.yourNewButton, &QPushButton::clicked, 
        this, &SimpleImageApp::applyYourNewFilter);

// Implement slot
void SimpleImageApp::applyYourNewFilter()
{
    if (!hasImage) return;
    
    saveStateForUndo();
    
    statusBar()->showMessage("Applying Your New Filter...");
    QApplication::processEvents();
    
    try {
        currentImage = currentImage.yourNewFilter();
        updateImageDisplay();
        statusBar()->showMessage("Your New Filter applied");
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", 
            QString("Filter failed: %1").arg(e.what()));
    }
}
```

### Adding New File Format Support

#### Step 1: Update STB Library
1. Ensure STB library supports your format
2. Update includes if necessary

#### Step 2: Modify Image_Class
```cpp
// In Image_Class.h
bool loadNewImage(const char* filename);
bool saveImage(const char* filename);

// In implementation
bool Image::loadNewImage(const char* filename)
{
    // STB handles multiple formats automatically
    data = stbi_load(filename, &width, &height, &channels, 0);
    return data != nullptr;
}
```

### Adding Keyboard Shortcuts

```cpp
// In SimpleImageApp constructor
QShortcut* shortcut = new QShortcut(QKeySequence("Ctrl+N"), this);
connect(shortcut, &QShortcut::activated, this, &SimpleImageApp::yourFunction);
```

## 🧪 Testing

### Unit Testing
```cpp
// Example test structure
void testGrayscaleConversion()
{
    Image testImage(100, 100, 3);
    // Initialize test image with known values
    
    Image result = testImage.grayscale();
    
    // Verify results
    assert(result.width == 100);
    assert(result.height == 100);
    // Add more assertions
}
```

### Integration Testing
- Test complete filter chains
- Test undo/redo functionality
- Test file I/O operations
- Test UI responsiveness

### Manual Testing Checklist
- [ ] All filters work with various image sizes
- [ ] Undo/Redo works correctly
- [ ] File loading/saving works
- [ ] UI remains responsive during processing
- [ ] Error handling works properly

## 🐛 Debugging

### Common Debug Techniques

#### Qt Debugging
```cpp
// Enable debug output
qDebug() << "Debug message:" << variable;

// Check UI element states
qDebug() << "Button enabled:" << ui.button->isEnabled();
```

#### Image Processing Debugging
```cpp
// Check image properties
qDebug() << "Image size:" << currentImage.width << "x" << currentImage.height;
qDebug() << "Channels:" << currentImage.channels;

// Verify pixel values
unsigned char pixel = currentImage(x, y, 0);
qDebug() << "Pixel at (" << x << "," << y << "):" << (int)pixel;
```

#### Memory Debugging
```cpp
// Check for memory leaks
// Use Valgrind (Linux) or Application Verifier (Windows)

// Monitor memory usage
qDebug() << "Memory usage:" << QApplication::instance()->memoryUsage();
```

### Debug Build
```bash
# Create debug build
qmake CONFIG+=debug ImageStudio.pro
mingw32-make
```

### Common Issues

#### Build Issues
- **Missing Qt**: Ensure Qt is in PATH
- **Compiler Errors**: Check C++20 support
- **Linker Errors**: Verify library paths

#### Runtime Issues
- **UI Not Updating**: Check signal/slot connections
- **Memory Crashes**: Verify image bounds checking
- **Performance**: Profile with Qt Creator

## 🤝 Contributing

### Code Style
- **Naming**: camelCase for variables, PascalCase for classes
- **Indentation**: 4 spaces
- **Comments**: Document complex algorithms
- **Headers**: Include guards, proper includes

### Git Workflow
1. Fork the repository
2. Create feature branch: `git checkout -b feature/new-filter`
3. Make changes and commit
4. Push and create pull request

### Pull Request Guidelines
- Clear description of changes
- Test the changes thoroughly
- Update documentation if needed
- Follow existing code style

### Code Review Checklist
- [ ] Code compiles without warnings
- [ ] No memory leaks
- [ ] Proper error handling
- [ ] UI remains responsive
- [ ] Documentation updated

## 📚 Additional Resources

### Qt Documentation
- [Qt 6 Documentation](https://doc.qt.io/qt-6/)
- [Qt Designer Manual](https://doc.qt.io/qt-6/qtdesigner-manual.html)
- [Qt Creator Manual](https://doc.qt.io/qtcreator/)

### C++ Resources
- [C++20 Reference](https://en.cppreference.com/)
- [Modern C++ Best Practices](https://github.com/isocpp/CppCoreGuidelines)

### Image Processing
- [STB Library](https://github.com/nothings/stb)
- [Computer Graphics Algorithms](https://www.cs.cmu.edu/~rbd/)

---

**Happy Coding!** 🚀

For questions or support, please open an issue on the project repository.

## 📗 Generating API Documentation (Doxygen)

### Overview
Use Doxygen to generate browsable documentation from in-source comments.

### Install
- Windows (recommended): `choco install doxygen.graphviz`
- Manual: download from `https://www.doxygen.nl/download.html`

### Configure
Use the provided `Doxyfile` in the repository root. Key settings:
- `PROJECT_NAME = "Image Studio"`
- `OUTPUT_DIRECTORY = docs/api`
- `RECURSIVE = YES`
- `EXTRACT_ALL = YES`
- `GENERATE_HTML = YES`
- `GENERATE_LATEX = NO`
- `INPUT = src docs/README.md README.md`

### Generate
```bash
doxygen Doxyfile
```
Open `docs/api/html/index.html` in your browser.

### Recommended Comment Conventions

- Prefer documenting public APIs in headers.
- Start with a one-line `\brief` summary; expand with details as needed.
- Tag parameters and return values with `\param` and `\return`.
- Document error conditions and exceptions with `\throws`.
- Use `\defgroup` and `@{`/`@}` to group related APIs.

Examples:

```cpp
/// \file ImageIO.h
/// \brief File I/O utilities for reading and writing images.

/** \brief Load an image from file.
 *  \param path UTF-8 file path.
 *  \return Loaded image.
 *  \throws std::runtime_error on read failure.
 */
Image loadFromFile(const std::string& path);

/** \defgroup IO Image I/O
 *  High-level file operations.
 *  @{ */
bool saveToFile(const Image& image, const std::string& path);
/** @} */
```

### Troubleshooting Doxygen

- Diagrams missing: ensure Graphviz is installed and `HAVE_DOT = YES`.
- Empty pages: confirm `INPUT` includes `src` and markdown files; rebuild.
- Symbols not linked: add headers to `INPUT` and ensure declarations are visible.
