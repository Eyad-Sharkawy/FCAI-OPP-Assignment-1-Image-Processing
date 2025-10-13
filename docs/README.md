# 🎨 Image Studio GUI - Professional Image Processing Application

<p align="center">
  <img width="600" height="400" alt="Image Studio GUI" src="https://github.com/user-attachments/assets/32dfecd3-89bb-45da-a8b3-812a811e3e43" />
</p>

<p align="center">
  <strong>A comprehensive Qt-based image processing application with advanced filters, real-time preview, and professional user interface.</strong>
</p>

<p align="center">
  <a href="#-quick-start">Quick Start</a> •
  <a href="#-features">Features</a> •
  <a href="#-downloads">Downloads</a> •
  <a href="#-building">Building</a> •
  <a href="#-usage">Usage</a> •
  <a href="#-technical-details">Technical Details</a>
</p>

---

## 🚀 Quick Start

### 📦 Download & Run (Recommended)
1. **Download** the latest portable version from [Releases](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Studio/releases)
2. **Extract** `ImageStudio_Portable_v1.1.0-gui.zip` to any folder
3. **Run** `ImageStudio.bat` or `bin\ImageStudio.exe`
4. **Drag & drop** an image or use File → Open
5. **Apply filters** and enjoy! 🎉

**✨ No installation required - all Qt dependencies included!**

---

## ✨ Features

### 🖼️ **Complete Image Processing Suite**
- **15+ Professional Filters**: Grayscale, Black & White, Invert, Merge, Flip, Rotate, Crop, Dark & Light, Frame (Simple & Decorated), Edge Detection, Resize, Blur, Infrared, Purple, TV/CRT
- **Real-time Preview**: See changes instantly as you apply filters
- **Batch Processing**: Apply multiple filters in sequence
- **Format Support**: JPG, JPEG, PNG, BMP, TGA

### ⏹️ **Advanced Cancel System**
- **Cancel Any Operation**: Stop long-running filters mid-process
- **Progress Tracking**: Visual progress bars for all operations
- **Responsive UI**: Interface remains interactive during processing
- **Thread-Safe**: Built with `std::atomic` for reliable cancellation

### 🎨 **Professional User Interface**
- **Modern Qt Design**: Clean, intuitive interface
- **Drag & Drop**: Load images by dragging files into the window
- **Menu System**: Complete File and Filters menus with keyboard shortcuts
- **Status Bar**: Real-time image information and operation feedback
- **Responsive Layout**: Image display scales with window size

### 🔄 **State Management**
- **Undo/Redo**: Full state management with Ctrl+Z/Ctrl+Y
- **Save Prompts**: Automatic prompts for unsaved changes
- **Unload Image**: Clear current image with save confirmation
- **Exit Confirmation**: Save unsaved changes before closing

### 🛠️ **Developer Features**
- **Modular Architecture**: Clean, maintainable code structure
- **Error Handling**: Comprehensive error handling and user feedback
- **Build System**: Automated build scripts for release and portable versions
- **Cross-Platform**: Windows, Linux, macOS support

---

## 📥 Downloads

### 🎯 **Latest Release: v1.1.0-gui**

| Version | Type | Size | Requirements | Description |
|---------|------|------|--------------|-------------|
| **Portable** | ZIP | ~50MB | Windows 10/11 (64-bit) | Complete package with all dependencies |
| **Release** | EXE | ~2MB | Windows 10/11 + Qt 6.8.1 | Optimized executable (requires Qt) |

### 📋 **System Requirements**
- **OS**: Windows 10/11 (64-bit)
- **RAM**: 4GB minimum, 8GB recommended
- **Storage**: 100MB free space
- **Display**: 1024x768 minimum resolution

---

## 🛠️ Building from Source

### Prerequisites
- **Qt 6.8.1** with MinGW 64-bit
- **C++20 compatible compiler** (GCC 13.1.0+)
- **CMake 3.30+** (for console version)
- **Windows/Linux/macOS**

### Quick Build
```bash
# Clone the repository
git clone https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Studio.git
cd FCAI-OPP-Assignment-1-Image-Studio

# Switch to GUI branch
git checkout gui

# Build release version
scripts/build_release.bat

# Build portable version
scripts/build_portable.bat
```

### Build Outputs
- **Release Build**: `build_release/release/ImageStudio.exe`
- **Portable Package**: `build_portable/ImageStudio_Portable/`
- **Portable ZIP**: `build_portable/ImageStudio_Portable_v1.1.0-gui.zip`

---

## 📖 Usage Guide

### 🖱️ **Basic Operations**

#### Loading Images
1. **Drag & Drop**: Drag image files directly into the window
2. **File Menu**: File → Open → Select image file
3. **Supported Formats**: JPG, JPEG, PNG, BMP, TGA

#### Applying Filters
1. **Button Interface**: Click filter buttons in the main window
2. **Menu Interface**: Use Filters menu for all operations
3. **Real-time Preview**: See changes instantly
4. **Cancel Operations**: Use Cancel button for long-running filters

#### Saving Images
1. **File Menu**: File → Save (Ctrl+S)
2. **Format Selection**: Choose from JPG, PNG, BMP, TGA
3. **Quality Settings**: Adjust compression for JPG files

### ⌨️ **Keyboard Shortcuts**

| Shortcut | Action |
|----------|--------|
| `Ctrl+O` | Open image |
| `Ctrl+S` | Save image |
| `Ctrl+Z` | Undo |
| `Ctrl+Y` | Redo |
| `Ctrl+Q` | Exit application |
| `Escape` | Cancel current operation |

### 🎯 **Filter Categories**

#### **Basic Filters**
- **Grayscale**: Convert to grayscale
- **Black & White**: Convert to pure black and white
- **Invert**: Invert image colors

#### **Transform Filters**
- **Flip**: Flip horizontally or vertically
- **Rotate**: Rotate by 90°, 180°, or 270°
- **Resize**: Change image dimensions
- **Crop**: Interactive cropping with mouse selection

#### **Effect Filters**
- **Blur**: Apply blur effects (radius-15 average kernel)
- **Edge Detection**: Detect and highlight edges (BW-diff method)
- **Dark & Light**: Adjust brightness and contrast

#### **Special Filters**
- **Infrared**: Create infrared-style images
- **Purple Filter**: Apply purple color enhancement
- **TV/CRT Filter**: Create retro TV monitor effects with scanlines
- **Merge**: Blend with another image

#### **Frame Filters**
- **Simple Frame**: Blue outer border with inner white border
- **Decorated Frame**: Brown/beige design with accent patterns

---

## 🔧 Technical Details

### **Architecture**
- **Framework**: Qt 6.8.1 with MinGW 64-bit
- **Language**: C++20 with modern features
- **Image Processing**: Custom `Image_Class` with pixel-level manipulation
- **Threading**: `std::atomic` for thread-safe cancellation
- **Memory Management**: RAII principles with smart pointers

### **Key Components**

#### **Main Application Class**
```cpp
class SimpleImageApp : public QMainWindow
{
    // UI Components
    QLabel* imageLabel;
    QPushButton* filterButtons[15];
    QProgressBar* progressBar;
    QPushButton* cancelButton;
    
    // State Management
    std::stack<Image> undoStack;
    std::stack<Image> redoStack;
    std::atomic<bool> cancelRequested;
    
    // Image Processing
    Image currentImage;
    bool hasImage;
    bool hasUnsavedChanges;
};
```

#### **Filter Implementation**
- **Modular Design**: Each filter is a separate method
- **Progress Tracking**: Real-time progress updates
- **Cancellation Support**: Thread-safe cancellation for all filters
- **Error Handling**: Comprehensive error handling and user feedback

### **Build System**
- **qmake**: Qt project configuration
- **mingw32-make**: Build automation
- **windeployqt**: Automatic Qt dependency deployment
- **Custom Scripts**: Automated build and packaging

### **Dependencies**
- **Qt 6.8.1**: Core, Gui, Widgets, Concurrent
- **STB Libraries**: stb_image.h, stb_image_write.h
- **MinGW 64-bit**: Compiler toolchain
- **Windows API**: Platform-specific functionality

---

## 📁 Project Structure

```
Image-Studio-GUI/
├── src/
│   └── simple_qt_app.cpp          # Main GUI application
├── include/
│   └── Image_Class.h              # Image processing class
├── third_party/
│   └── stb/                       # STB image libraries
│       ├── stb_image.h
│       └── stb_image_write.h
├── scripts/
│   ├── build_release.bat          # Release build script
│   └── build_portable.bat         # Portable build script
├── build_portable/
│   └── ImageStudio_Portable/      # Portable package
│       ├── bin/
│       │   ├── ImageStudio.exe    # Main executable
│       │   ├── platforms/         # Qt platform plugins
│       │   ├── styles/            # Qt style plugins
│       │   └── translations/      # Qt translation files
│       └── ImageStudio.bat        # Launcher script
├── build_release/
│   └── release/
│       └── ImageStudio.exe        # Release executable
├── ImageStudio.pro                # Qt project file
├── main.cpp                       # Console application
└── README_GUI.md                  # This file
```

---

## 🚀 Recent Updates (v1.1.0-gui)

### **🔧 Major Improvements**
- **Fixed Portable Version**: Using `windeployqt` for proper Qt deployment
- **Enhanced Cancel System**: Added cancellation to ALL filters
- **Progress Tracking**: Visual progress bars for long-running operations
- **Improved UI**: Better positioning and responsive design

### **🎯 New Features**
- **Unload Image**: Clear current image with save prompts
- **Exit Confirmation**: Save unsaved changes before closing
- **Enhanced Error Handling**: Better user feedback and error messages
- **Professional Interface**: Improved visual design and layout

### **🛠️ Technical Enhancements**
- **Thread Safety**: Using `std::atomic` for cancellation flags
- **Automated Builds**: Improved build scripts with `windeployqt`
- **Code Organization**: Better modular structure and maintainability
- **Performance**: Optimized filter implementations

---

## 👥 Development Team

- **Ahmed Mohamed ElSayed Tolba** (ID: 20242023)
  - Filters: Grayscale, Merge, Dark & Light, Edge Detection, TV/CRT
  - Menu system and core architecture

- **Eyad Mohamed Saad Ali** (ID: 20242062)
  - Filters: Black & White, Flip, Resize, Infrared
  - GUI implementation and Qt integration

- **Tarek Sami Mohamed Mohamed** (ID: 20242190)
  - Filters: Invert, Rotate, Frame, Blur, Purple
  - Image processing algorithms and optimization

---

## 📄 License

Educational project for **FCAI Cairo University** - Object-Oriented Programming Course

---

## 🔗 Links

- **Repository**: [FCAI-OPP-Assignment-1-Image-Studio](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Studio)
- **Releases**: [Download Latest Version](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Studio/releases)
- **GUI Branch**: [View GUI Implementation](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Studio/tree/gui)
- **Issues**: [Report Bugs or Request Features](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Studio/issues)

---

<p align="center">
  <strong>Made with ❤️ by FCAI Students</strong>
</p>

<p align="center">
  <em>Professional image processing made simple and accessible</em>
</p>
