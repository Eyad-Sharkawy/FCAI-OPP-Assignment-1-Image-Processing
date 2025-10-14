# Image Studio v2.0.0 - User Guide

## 📖 Table of Contents
1. [Getting Started](#getting-started)
2. [Interface Overview](#interface-overview)
3. [Loading Images](#loading-images)
4. [Image Processing Filters](#image-processing-filters)
5. [Advanced Features](#advanced-features)
6. [Keyboard Shortcuts](#keyboard-shortcuts)
7. [Troubleshooting](#troubleshooting)
8. [FAQ](#faq)

## 🚀 Getting Started

### System Requirements
- **Operating System**: Windows 10/11 (64-bit)
- **Memory**: 4GB RAM minimum, 8GB recommended
- **Storage**: 100MB free space
- **Graphics**: DirectX 11 compatible

### Installation
1. Download `ImageStudio_Portable_v2.0.0-gui.zip`
2. Extract the ZIP file to your desired location
3. Run `ImageStudio.bat` or `bin/ImageStudio.exe`
4. No additional installation required!

## 🖥️ Interface Overview

### Main Window Layout
```
┌─────────────────────────────────────────────────────────┐
│ File Menu: Load | Save | Exit                           │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  [Load] [Save] [Undo] [Redo] [Crop] [Merge]             │
│                                                         │
│  [Grayscale] [B&W] [Invert] [Flip H] [Flip V] [Rotate]  │
│                                                         │
│  [Dark] [Light] [Frame] [Edges] [Resize] [Blur]         │
│                                                         │
│  [Infrared] [Purple] [TV Filter]                        │
│                                                         │
│  ┌─────────────────────────────────────────────────┐    │
│  │                                                 │    │
│  │            Image Display Area                   │    │
│  │                                                 │    │
│  └─────────────────────────────────────────────────┘    │
│                                                         │
│  Status: Ready | Image: 1920x1080 | Aspect: 16:9        │
└─────────────────────────────────────────────────────────┘
```

### Key Components
- **Button Grid**: All image processing filters organized in rows
- **Image Display**: Scrollable area showing your current image
- **Status Bar**: Shows current image information and processing status
- **Progress Bar**: Appears during long operations

## 📸 Loading Images

### Supported Formats
- **JPEG** (.jpg, .jpeg)
- **PNG** (.png)
- **BMP** (.bmp)
- **TGA** (.tga)

### Loading Methods

#### Method 1: Load Button
1. Click the **Load** button
2. Navigate to your image file
3. Select the file and click **Open**

#### Method 2: Drag & Drop
1. Open File Explorer
2. Drag your image file directly onto the Image Studio window
3. Release to load the image

#### Method 3: File Menu
1. Use the **File** menu (if available)
2. Select **Load Image**
3. Choose your file

## 🎨 Image Processing Filters

### Basic Filters

#### Grayscale
- **Purpose**: Converts color images to grayscale
- **Usage**: Click **Grayscale** button
- **Effect**: Removes color information, keeping only brightness

#### Black & White
- **Purpose**: Creates pure black and white images
- **Usage**: Click **B&W** button
- **Effect**: Converts to binary (black/white only)

#### Invert
- **Purpose**: Inverts all colors
- **Usage**: Click **Invert** button
- **Effect**: Black becomes white, white becomes black

### Geometric Operations

#### Flip Horizontal
- **Purpose**: Mirrors the image left-to-right
- **Usage**: Click **Flip H** button

#### Flip Vertical
- **Purpose**: Mirrors the image top-to-bottom
- **Usage**: Click **Flip V** button

#### Rotate
- **Purpose**: Rotates the image 90 degrees clockwise
- **Usage**: Click **Rotate** button
- **Note**: Can be applied multiple times for 180°, 270° rotations

### Advanced Filters

#### Edge Detection
- **Purpose**: Highlights edges and outlines
- **Usage**: Click **Edges** button
- **Algorithm**: Sobel edge detection with Gaussian blur
- **Result**: White edges on black background

#### Blur
- **Purpose**: Softens the image
- **Usage**: Click **Blur** button
- **Effect**: Reduces sharpness and detail

#### Infrared Effect
- **Purpose**: Creates infrared-like appearance
- **Usage**: Click **Infrared** button
- **Effect**: Simulates infrared photography

#### Purple Filter
- **Purpose**: Applies purple color tint
- **Usage**: Click **Purple** button
- **Effect**: Adds purple color overlay

#### TV/CRT Filter
- **Purpose**: Simulates old TV/CRT monitor effect
- **Usage**: Click **TV Filter** button
- **Effect**: Adds scan lines and vintage appearance

### Brightness Controls

#### Dark
- **Purpose**: Reduces image brightness
- **Usage**: Click **Dark** button
- **Effect**: Makes image darker

#### Light
- **Purpose**: Increases image brightness
- **Usage**: Click **Light** button
- **Effect**: Makes image brighter

### Special Features

#### Frame
- **Purpose**: Adds decorative border
- **Usage**: Click **Frame** button
- **Effect**: Adds colored frame around image

#### Resize
- **Purpose**: Changes image dimensions
- **Usage**: Click **Resize** button
- **Note**: Prompts for new dimensions

#### Crop
- **Purpose**: Crops image to selected area
- **Usage**: 
  1. Click **Crop** button
  2. Drag to select area
  3. Click **Apply** or press Enter

#### Merge
- **Purpose**: Combines two images
- **Usage**: 
  1. Load first image
  2. Click **Merge** button
  3. Select second image
  4. Choose merge mode

## 🔧 Advanced Features

### Undo/Redo System
- **Undo**: Click **Undo** button or press `Ctrl+Z`
- **Redo**: Click **Redo** button or press `Ctrl+Y`
- **Unlimited**: No limit on undo/redo operations
- **Memory**: All operations are stored in memory

### Smart Resizing
- **Aspect Ratio**: Automatically preserved
- **Dynamic Window**: Window adjusts to prevent scrollbars
- **No Upscaling**: Images are never made larger than original
- **Real-time**: Changes apply immediately

### Progress Tracking
- **Progress Bar**: Shows during long operations
- **Status Updates**: Real-time status messages
- **Cancellation**: Long-running filters (e.g., Grayscale, Blur, Infrared, Purple, TV) can be cancelled via the Cancel button

## ⌨️ Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `Ctrl+O` | Load Image |
| `Ctrl+S` | Save Image |
| `Ctrl+Z` | Undo |
| `Ctrl+Y` | Redo |
| `Ctrl+Q` | Quit Application |
| `Escape` | Cancel Current Operation |

## 🔍 Troubleshooting

### Common Issues

#### Image Won't Load
- **Check Format**: Ensure file is in supported format
- **File Size**: Very large images may take time to load
- **File Corruption**: Try opening in another application first

#### Application Won't Start
- **Dependencies**: Ensure all DLL files are present
- **Permissions**: Run as administrator if needed
- **Antivirus**: Check if antivirus is blocking the application

#### Filters Not Working
- **Image Loaded**: Ensure an image is loaded first
- **Memory**: Close other applications to free memory
- **File Format**: Some filters work better with certain formats

#### Performance Issues
- **Image Size**: Large images take longer to process
- **Memory**: Close other applications
- **Hardware**: Ensure adequate RAM and CPU

### Error Messages

#### "No image loaded"
- **Solution**: Load an image before applying filters

#### "Filter failed"
- **Solution**: Try a different image or restart the application

#### "Memory allocation error"
- **Solution**: Close other applications or use smaller images

## ❓ FAQ

### General Questions

**Q: Is Image Studio free?**
A: Yes, Image Studio is free and open-source.

**Q: Can I use it commercially?**
A: This is an educational project. Check the license for commercial use.

**Q: What operating systems are supported?**
A: Currently Windows 10/11 (64-bit). Other platforms may be added in future versions.

### Technical Questions

**Q: Why is the application so large?**
A: It includes all Qt libraries for portability. No separate installation needed.

**Q: Can I process multiple images at once?**
A: Currently, only one image at a time is supported.

**Q: Are my images sent anywhere?**
A: No, all processing is done locally on your computer.

### Feature Questions

**Q: Can I save in different formats?**
A: Yes, you can save in JPEG, PNG, and BMP formats.

**Q: Is there a batch processing feature?**
A: Not in the current version, but it's planned for future releases.

**Q: Can I customize the interface?**
A: The interface is fixed in this version, but themes may be added later.

## 📞 Support

### Getting Help
- **Documentation**: Check this user guide first
- **GitHub Issues**: Report bugs on the project repository
- **Email**: Contact the development team

### Reporting Bugs
When reporting bugs, please include:
- Operating system version
- Image Studio version
- Steps to reproduce the issue
- Error messages (if any)
- Sample image (if relevant)

---

**Image Studio v2.0.0** - Professional Image Processing Made Simple! 🎨
