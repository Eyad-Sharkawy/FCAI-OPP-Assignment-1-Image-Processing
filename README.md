# Image Studio

A comprehensive image processing application with both console and GUI interfaces, featuring advanced image manipulation and filtering operations.

## 🚀 Quick Start - Download Portable Version

**Ready to use! No installation required.**

### 📦 Download Image Studio Portable
1. Go to the [Releases](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Processing/releases) page
2. Download `ImageStudio_Portable.zip` (11.9 MB)
3. Extract the ZIP file to any folder
4. Run `ImageStudio.bat` or `bin\ImageStudio.exe`
5. Enjoy! 🎉

**Features of the Portable Version:**
- ✅ **No Installation Required** - Just extract and run
- ✅ **All Dependencies Included** - Qt libraries bundled
- ✅ **Professional GUI** - Modern Qt interface with menu bar
- ✅ **Drag & Drop** - Load images by dragging into window
- ✅ **Undo/Redo** - Full state management with Ctrl+Z/Ctrl+Y
- ✅ **Responsive Design** - Image scales with window size
- ✅ **All Filters** - Complete set of 15+ image processing filters

## Features

### 🖼️ Image Processing Filters
- **Load Images**: Support for JPG, JPEG, PNG, BMP, and TGA formats
- **Grayscale Conversion**: Convert images to grayscale
- **Black & White**: Convert images to pure black and white
- **Color Inversion**: Invert image colors
- **Image Merging**: Blend two images together
- **Image Flipping**: Flip images horizontally or vertically
- **Image Rotation**: Rotate images by 90°, 180°, or 270°
- **Dark and Light**: Adjust image brightness and contrast
- **Frame Effects**: Add simple or decorated frames to images
- **Edge Detection**: Detect and highlight image edges
- **Image Resizing**: Resize images to different dimensions
- **Blur Effects**: Apply blur filters to images
- **Infrared Effect**: Create infrared-style images
- **Purple Filter**: Apply purple color enhancement
- **TV/CRT Filter**: Create retro TV monitor effects with scanlines and color distortion
- **Interactive Crop**: Crop images with mouse selection
- **Save Images**: Save processed images in various formats

### 🎨 GUI Features
- **Modern Interface**: Professional Qt-based GUI
- **Menu Bar**: File and Filters menus with keyboard shortcuts
- **Status Bar**: Real-time image information and feedback
- **Drag & Drop**: Load images by dragging files into the window
- **Undo/Redo System**: Full state management with visual feedback
- **Responsive Layout**: Image display scales with window size
- **Custom Icon**: Professional application icon

## 🛠️ Building from Source

### Prerequisites
- **C++20 compatible compiler** (GCC, Clang, or MSVC)
- **Qt 6.8.1** with MinGW 64-bit
- **CMake 3.30** or higher (for console version)
- **Windows/Linux/macOS**

### Console Version (Original)
```bash
mkdir build
cd build
cmake ..
make
```

### GUI Version (Qt)
```bash
# Build release version
scripts/build_release.bat

# Build portable version
scripts/build_portable.bat
```

## 📖 Usage

### GUI Version (Recommended)
1. **Download** the portable version or build from source
2. **Run** `ImageStudio.exe`
3. **Load** an image by dragging it into the window or using File → Open
4. **Apply** filters using the buttons or menu
5. **Save** your processed image using File → Save

### Console Version
1. Run the executable
2. Load an image when prompted
3. Select from the menu options to apply filters
4. Save your processed image

## 🎮 Console Menu Options

- `0` - Load a new image
- `1` - Apply grayscale filter
- `2` - Apply black & white filter
- `3` - Invert colors
- `4` - Merge with another image
- `5` - Flip image (horizontal/vertical)
- `6` - Rotate image (90°/180°/270°)
- `7` - Dark and light adjustment
- `9` - Frame effects (simple/decorated)
- `10` - Detect image edges
- `11` - Resize images
- `12` - Blur images
- `13` - Infrared effect
- `14` - Purple filter
- `15` - TV/CRT filter (retro monitor effect)
- `16` - Save current image
- `17` - Exit

## 🎯 GUI Features

### File Menu
- **Open** - Load an image file
- **Save** - Save current image (Ctrl+S)
- **Undo** - Undo last action (Ctrl+Z)
- **Redo** - Redo last undone action (Ctrl+Y)
- **Exit** - Close application

### Filters Menu
- **Grayscale** - Convert to grayscale
- **TV/CRT Filter** - Retro monitor effect
- **Black & White** - Convert to black and white
- **Invert** - Invert colors
- **Merge** - Blend with another image
- **Flip** - Flip horizontally/vertically
- **Rotate** - Rotate by 90°/180°/270°
- **Dark & Light** - Adjust brightness/contrast
- **Frame** - Add decorative frames
- **Edge Detection** - Detect and highlight edges
- **Resize** - Change image dimensions
- **Blur** - Apply blur effects
- **Infrared** - Create infrared effect
- **Purple Filter** - Apply purple enhancement
- **Crop** - Interactive image cropping

## 📁 Project Structure

```
assignment-1/
├── src/                    # Source code
│   └── simple_qt_app.cpp  # Main GUI application
├── include/               # Header files
│   └── Image_Class.h     # Image processing class
├── third_party/          # Third-party libraries
│   └── stb/              # STB image libraries
├── assets/               # Application assets
│   └── icon.jpg         # Application icon
├── scripts/              # Build scripts
│   ├── build_release.bat # Release build script
│   └── build_portable.bat # Portable build script
├── ImageStudio.pro       # Qt project file
├── main.cpp             # Console application
└── README.md            # This file
```

## 👥 Authors

- **Ahmed Mohamed ElSayed Tolba** (ID: 20242023) - Filters 1, 4, 7, 10, 17 (bonus), menu
- **Eyad Mohamed Saad Ali** (ID: 20242062) - Filters 2, 5, 8, 11, 15 (bonus), menu, GUI implementation
- **Tarek Sami Mohamed Mohamed** (ID: 20242190) - Filters 3, 6, 9, 12, 16 (bonus), menu

## 📚 Dependencies

- **stb_image.h** - Image loading library
- **stb_image_write.h** - Image writing library
- **Qt 6.8.1** - GUI framework (for GUI version)
- **MinGW 64-bit** - Compiler toolchain

## 📄 License

Educational project for FCAI Cairo University - Object-Oriented Programming Course

## 🔗 Links

- **Repository**: [FCAI-OPP-Assignment-1-Image-Processing](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Processing)
- **Releases**: [Download Portable Version](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Processing/releases)
- **GUI Branch**: [View GUI Implementation](https://github.com/Eyad-Sharkawy/FCAI-OPP-Assignment-1-Image-Processing/tree/gui)
