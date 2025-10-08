# Image Studio – Qt GUI Image Processing App

Modern Qt-based GUI for image manipulation and filters, plus the original console app.

## GUI Features (Image Studio)

- **Drag & Drop Loading**: Drop JPG/JPEG/PNG/BMP/TGA files into the window
- **Responsive Preview**: Image scales smoothly when resizing the window
- **Undo / Redo**: Stack-based history for all filter actions
- **Mouse Crop**: Click Crop, drag a rectangle, release to crop
- **Load/Save**: Multiple formats supported
- **All Filters**: Full parity with the original console app

### Filters

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
  
> Note: All filters support Undo/Redo.

## Requirements (GUI)

- Windows with Qt 6 (tested on 6.8.1 MinGW)
- MinGW toolchain (comes with Qt for Windows)

## Build (GUI)

1) Ensure `assets/icon.ico` exists (for EXE icon). Window icon also set via `assets/icon.jpg`.
2) From repo root, run:

```bat
build_release.bat
```

Artifacts:
- `build_release/release/ImageStudio.exe`

## Usage (GUI)

1. Run `build_release/release/ImageStudio.exe`
2. Drag & drop an image or click Load Image
3. Apply filters via buttons or the Filters menu
4. Use Undo/Redo as needed
5. Crop: Click Crop, drag a rectangle on the image, release to apply
6. Save your processed image

## Console Application (Legacy)

The repository still includes the original console app (`main.cpp`).
It provides the same filters via a text menu and can be built separately if needed.

## Authors

- Ahmed Mohamed ElSayed Tolba (ID: 20242023) - Filters 1, 4, 7, 10, 17 (bonus), menu
- Eyad Mohamed Saad Ali (ID: 20242062) - Filters 2, 5, 8, 11, 15 (bonus), menu
- Tarek Sami Mohamed Mohamed (ID: 20242190) - Filters 3, 6, 9, 12, 16 (bonus), menu

## Dependencies

- Qt 6 (Widgets)
- `stb_image.h` - Image loading
- `stb_image_write.h` - Image writing

## License

Educational project for FCAI Cairo University
