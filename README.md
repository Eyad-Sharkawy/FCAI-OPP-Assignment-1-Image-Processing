# Image Processing Application

A C++ console application for basic image manipulation and filtering operations.

## Features

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
- **Save Images**: Save processed images in various formats

## Requirements

- C++20 compatible compiler
- CMake 3.30 or higher
- Windows/Linux/macOS

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

1. Run the executable
2. Load an image when prompted
3. Select from the menu options to apply filters
4. Save your processed image

## Menu Options

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

## Authors

- Ahmed Mohamed ElSayed Tolba (ID: 20242023) - Filters 1, 4, 7, 10, 17 (bonus), menu.
- Eyad Mohamed Saad Ali (ID: 20242062) - Filters 2, 5, 8, 11, 15 (bonus), menu.
- Tarek Sami Mohamed Mohamed (ID: 20242190) - Filters 3, 6, 9, 12, 16 (bonus), menu.

## Dependencies

- stb_image.h - Image loading library
- stb_image_write.h - Image writing library

## License

Educational project for FCAI Cairo University
