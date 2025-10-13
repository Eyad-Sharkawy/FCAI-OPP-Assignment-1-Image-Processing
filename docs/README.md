# Image Studio v2.0.0 - Documentation Hub

Welcome to the Image Studio documentation! This is your central hub for all documentation related to Image Studio v2.0.0.

## 📚 Documentation Overview

Image Studio is a modern, feature-rich image processing application built with Qt 6 and C++20. This documentation covers everything from basic usage to advanced development.

## 🚀 Quick Start

### For Users
1. **Installation**: [Installation Guide](INSTALLATION.md) - Get started in minutes
2. **User Guide**: [User Guide](USER_GUIDE.md) - Learn all features
3. **Troubleshooting**: [User Guide - Troubleshooting](USER_GUIDE.md#troubleshooting) - Solve common issues

### For Developers
1. **Installation**: [Installation Guide](INSTALLATION.md) - Set up development environment
2. **Developer Guide**: [Developer Guide](DEVELOPER_GUIDE.md) - Architecture and development

## 📖 Documentation Structure

### User Documentation
- **[User Guide](USER_GUIDE.md)** - Complete user manual
  - Getting started
  - Interface overview
  - Image processing filters
  - Advanced features
  - Keyboard shortcuts
  - Troubleshooting
  - FAQ

- **[Installation Guide](INSTALLATION.md)** - Installation instructions
  - System requirements
  - Download options
  - Installation methods
  - Build from source
  - Troubleshooting

### Developer Documentation
- **[Developer Guide](DEVELOPER_GUIDE.md)** - Development documentation
  - Project overview
  - Architecture details
  - Build system
  - Code structure
  - ImageFilters design and cancellation/progress patterns
  - Adding new features
  - Testing
  - Debugging
  - Contributing

## 🎯 Quick Reference

### Key Features
- **Image Processing**: 15+ professional filters
- **Smart UI**: Aspect ratio preservation, dynamic resizing
- **Undo/Redo**: Unlimited history management
- **Drag & Drop**: Easy image loading
- **Multiple Formats**: JPEG, PNG, BMP, TIFF, GIF
- **Portable**: No installation required

### System Requirements
- **OS**: Windows 10/11 (64-bit)
- **RAM**: 4GB minimum, 8GB recommended
- **Storage**: 100MB free space
- **Graphics**: DirectX 11 compatible

### Download
- **Portable Version**: `ImageStudio_Portable_v2.0.0-gui.zip` (~25MB)
- **Source Code**: GitHub repository
- **Requirements**: Qt 6.8.1+, C++20 compiler

## 🛠️ Development

### Architecture
```
┌──────────────────────────────────────────────────────────┐
│                    Presentation Layer                    │
│  ┌─────────────────┐  ┌────────────────────────────────┐ │
│  │   Main Window   │  │        Qt Designer UI          │ │
│  │  (QMainWindow)  │  │      (mainwindow.ui)           │ │
│  └─────────────────┘  └────────────────────────────────┘ │
└──────────────────────────────────────────────────────────┘
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

### Project Structure
```
ImageStudio/
├── src/
│   ├── gui/                        # GUI Components
│   │   ├── image_studio.cpp        # Main application class
│   │   └── mainwindow.ui           # Qt Designer UI file
│   └── core/                       # Core Functionality
│       ├── image/                  # Image container + I/O
│       │   ├── Image_Class.h
│       │   └── Image_Class.cpp
│       ├── filters/                # Image processing filters (Qt-aware)
│       │   ├── ImageFilters.h
│       │   └── ImageFilters.cpp
│       ├── history/                # Undo/redo management
│       │   └── HistoryManager.h
│       └── io/                     # File I/O helpers
│           └── ImageIO.h
├── third_party/                    # External Libraries
│   └── stb/                        # STB image library
├── docs/                           # Documentation
├── assets/                         # Resources
├── scripts/                        # Build Scripts (Windows)
└── cmake-build-*, build_portable/  # Build Output
```

## 🤝 Contributing

### Getting Started
1. Read the [Developer Guide](DEVELOPER_GUIDE.md)
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
- **Comments**: Document complex algorithms

### Testing
- Unit tests for core functionality
- Integration tests for UI
- Manual testing checklist
- Performance testing

## 📞 Support

### Getting Help
- **Documentation**: Check relevant guide first
- **GitHub Issues**: Report bugs and request features
- **Email**: Contact development team

### Reporting Issues
When reporting issues, please include:
- Operating system version
- Image Studio version
- Steps to reproduce
- Error messages
- System specifications

## 📄 License

This project is developed as part of a C++ Object-Oriented Programming assignment at FCAI (Faculty of Computers and Artificial Intelligence).

**Team Members:**
- Ahmed Mohamed ElSayed Tolba (ID: 20242023)
- Eyad Mohamed Saad Ali (ID: 20242062)
- Tarek Sami Mohamed Mohamed (ID: 20242190)

## 🔗 Links

- **GitHub Repository**: [Image Studio on GitHub](https://github.com/your-repo/image-studio)
- **Releases**: [Latest Releases](https://github.com/your-repo/image-studio/releases)
- **Issues**: [Report Issues](https://github.com/your-repo/image-studio/issues)
- **Discussions**: [Community Discussions](https://github.com/your-repo/image-studio/discussions)

---

**Image Studio v2.0.0** - Professional Image Processing Made Simple! 🎨

*Last updated: October 13, 2024*