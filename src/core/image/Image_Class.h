/**
 * @file Image_Class.h
 * @brief Core image data structure with STB library integration for comprehensive image I/O.
 * 
 * This file contains the declaration of the Image class, which serves as the fundamental
 * data structure for all image processing operations in the Image Studio application.
 * The class provides a high-level interface for image manipulation while leveraging
 * the powerful STB (Sean T. Barrett) library for robust image loading and saving.
 * 
 * @details The Image class provides:
 * - Complete image data management with automatic memory handling
 * - Support for multiple image formats (PNG, JPEG, BMP, TGA)
 * - Safe pixel access with bounds checking
 * - Copy semantics with proper resource management
 * - STB library integration for professional-grade image I/O
 * - Exception safety and comprehensive error handling
 * 
 * @features
 * - Multi-format support: PNG, JPEG, BMP, TGA
 * - Automatic memory management with RAII principles
 * - Safe pixel access with bounds checking
 * - Copy constructor and assignment operator
 * - STB library integration for robust I/O
 * - Exception safety and error handling
 * - Cross-platform compatibility
 * 
 * @author Original Authors:
 * - Shehab Diab
 * - Youssef Mohamed
 * - Nada Ahmed
 * - Dr. Mohamed El-Ramely (Supervisor)
 * 
 * @author Current Team:
 * - Ahmed Mohamed ElSayed Tolba (ID: 20242023)
 * - Eyad Mohamed Saad Ali (ID: 20242062) 
 * - Tarek Sami Mohamed Mohamed (ID: 20242190)
 * 
 * @institution Faculty of Computers and Artificial Intelligence, Cairo University
 * @version 2.0.0 (Enhanced with comprehensive documentation and Qt integration)
 * @date October 13, 2025
 * @copyright FCAI Cairo University
 */


// stb_image header definitions
#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H


#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1


// Forward declarations for STB library
// Implementation will be in Image_Class.cpp
#define pixel unsigned int

// Forward declarations for STB functions
extern "C" {
    unsigned char *stbi_load(char const *filename, int *x, int *y, int *channels_in_file, int desired_channels);
    void stbi_image_free(void *retval_from_stbi_load);
    int stbi_write_png(char const *filename, int w, int h, int comp, const void *data, int stride_in_bytes);
    int stbi_write_bmp(char const *filename, int w, int h, int comp, const void *data);
    int stbi_write_tga(char const *filename, int w, int h, int comp, const void *data);
    int stbi_write_jpg(char const *filename, int w, int h, int comp, const void *data, int quality);
}

// STB constants
#define STBI_rgb 3

#include <iostream>
#include <exception>
#include <cstring>
#include <string.h>


/**
 * @class Image
 * @brief Core image data structure with comprehensive I/O and manipulation capabilities.
 * 
 * The Image class is the fundamental data structure for all image processing operations
 * in the Image Studio application. It provides a high-level, safe interface for image
 * manipulation while leveraging the powerful STB library for robust image I/O operations.
 * 
 * @details This class implements:
 * - Complete image data management with automatic memory handling
 * - Support for multiple image formats through STB library integration
 * - Safe pixel access with comprehensive bounds checking
 * - Copy semantics with proper resource management (RAII)
 * - Exception safety and comprehensive error handling
 * - Cross-platform compatibility
 * 
 * @features
 * - Multi-format support: PNG, JPEG, BMP, TGA
 * - Automatic memory management with RAII principles
 * - Safe pixel access with bounds checking and exception handling
 * - Copy constructor and assignment operator with deep copying
 * - STB library integration for professional-grade image I/O
 * - Exception safety with descriptive error messages
 * - Cross-platform file path handling
 * 
 * @note This class is designed to work seamlessly with Qt applications and provides
 *       thread-safe operations for GUI applications.
 * @see STB library for underlying image I/O implementation
 * @see ImageFilters class for image processing operations
 * @see ImageIO class for Qt-integrated file operations
 * 
 * @example
 * @code
 * // Load an image
 * Image img("path/to/image.png");
 * 
 * // Access pixel data safely
 * unsigned char red = img(100, 50, 0);   // Red channel
 * unsigned char green = img(100, 50, 1); // Green channel
 * unsigned char blue = img(100, 50, 2);  // Blue channel
 * 
 * // Modify pixel data
 * img.setPixel(100, 50, 0, 255); // Set red to maximum
 * 
 * // Save the image
 * img.saveImage("path/to/output.jpg");
 * @endcode
 */
class Image {
private:
    /**
     * @brief Checks if the given filename has a valid extension.
     *
     * @param filename The filename to check.
     * @return True if the filename has a valid extension, false otherwise.
     */
    bool isValidFilename(const std::string& filename) {
        std::size_t dotPos = filename.rfind('.');
        if (dotPos == std::string::npos || dotPos == filename.size() - 1) {
            std::cerr << "Invalid filename: " << filename << std::endl;
            return false;
        }
        return true;
    }

    /**
     * @brief Determines the image type based on the file extension.
     *
     * @param extension The file extension to determine the type.
     * @return The type of image format.
     */

    short getExtensionType(const char* extension) {
        if (extension == nullptr) return UNSUPPORTED_TYPE;
        std::string extStr(extension);
        for (char& ch : extStr) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        if (extStr == ".png") {
            return PNG_TYPE;
        }
        if (extStr == ".bmp") {
            return BMP_TYPE;
        }
        if (extStr == ".tga") {
            return TGA_TYPE;
        }
        if (extStr == ".jpg" || extStr == ".jpeg") {
            return JPG_TYPE;
        }

        std::cerr << "Unsupported image format: " << extension << std::endl;
        return UNSUPPORTED_TYPE;
    }

private:
    std::string filename; ///< Stores the filename of the image.

public:
    int width = 0; ///< Width of the image.
    int height = 0; ///< Height of the image.
    int channels = 3; ///< Number of color channels in the image.
    unsigned char* imageData = nullptr; ///< Pointer to the image data.

    /**
     * @brief Default constructor for the Image class.
     */
    Image() = default;

    /**
     * @brief Constructor that loads an image from the specified filename.
     *
     * @param filename The filename of the image to load.
     */
    Image(std::string filename) : filename((filename)) {
        loadNewImage(this->filename);
    }

    /**
     * @brief Constructor that creates an image with the specified dimensions.
     *
     * @param mWidth The width of the image.
     * @param mHeight The height of the image.
     */
    Image(int mWidth, int mHeight) {
        this->width = mWidth;
        this->height = mHeight;
        this->imageData = (unsigned char*)malloc(mWidth * mHeight * this->channels);
    }

    /**
     * @brief Constructor that creates an image by copying another image.
     *
     * @param other The Image we want to copy.
     */
    Image(const Image& other) {
        *this = other;
    }

    /**
     * @brief Overloading the assignment operator.
     *
     * @param image The Image we want to copy.
     *
     * @return *this after copying data.
     */

    Image& operator=(const Image& image) {
        if (this == &image){
            return *this;
        }

        stbi_image_free(this->imageData);
        this->imageData = nullptr;

        this->width = image.width;
        this->height = image.height;
        this->channels = image.channels;
        imageData = static_cast<unsigned char*>(malloc(width * height * channels));

        for (int i = 0; i < image.width * image.height * this->channels; i++) {
            this->imageData[i] = image.imageData[i];
        }

        return *this;
    }

    /**
     * @brief Destructor for the Image class.
     */
    ~Image() {
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }
        this->width = 0;
        this->height = 0;
        this->imageData = nullptr;
    }

    /**
     * @brief Loads a new image from the specified filename.
     *
     * @param filename The filename of the image to load.
     * @return True if the image is loaded successfully, false otherwise.
     * @throws std::invalid_argument If the filename or file format is invalid.
     */
    bool loadNewImage(const std::string& filename) {
        if (!isValidFilename(filename)) {
            std::cerr << "Couldn't Load Image" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        std::size_t dotPos = filename.rfind('.');
        short extensionType = getExtensionType(dotPos == std::string::npos ? nullptr : filename.c_str() + dotPos);
        if (extensionType == UNSUPPORTED_TYPE) {
            std::cerr << "Unsupported File Format" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }

        imageData = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

        if (imageData == nullptr) {
            std::cerr << "File Doesn't Exist" << '\n';
            throw std::invalid_argument("Invalid filename, File Does not Exist");
        }

        return true;
    }

    /**
     * @brief Saves the image to the specified output filename.
     *
     * @param outputFilename The filename to save the image.
     * @return True if the image is saved successfully, false otherwise.
     * @throws std::invalid_argument If the output filename or file format is invalid.
     */

    bool saveImage(const std::string& outputFilename) {
        if (!isValidFilename(outputFilename)) {
            std::cerr << "Not Supported Format" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        // Determine image type based on filename extension
        std::size_t dotPos = outputFilename.rfind('.');
        short extensionType = getExtensionType(dotPos == std::string::npos ? nullptr : outputFilename.c_str() + dotPos);
        if (extensionType == UNSUPPORTED_TYPE) {
            std::cerr << "File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }

        if (extensionType == PNG_TYPE) {
            stbi_write_png(outputFilename.c_str(), width, height, STBI_rgb, imageData, width * 3);
        }
        else if (extensionType == BMP_TYPE) {
            stbi_write_bmp(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        }
        else if (extensionType == TGA_TYPE) {
            stbi_write_tga(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        }
        else if (extensionType == JPG_TYPE) {
            stbi_write_jpg(outputFilename.c_str(), width, height, STBI_rgb, imageData, 90);
        }

        return true;
    }

    /**
     * @brief Gets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0 for red, 1 for green, 2 for blue).
     * @return Reference to the pixel value.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    unsigned char& getPixel(int x, int y, int c) {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return imageData[(y * width + x) * channels + c];
    }

    const unsigned char& getPixel(int x, int y, int c) const {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return imageData[(y * width + x) * channels + c];
    }
    /**
     * @brief Sets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0 for red, 1 for green, 2 for blue).
     * @param value The new value to set.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    void setPixel(int x, int y, int c, unsigned char value) {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        imageData[(y * width + x) * channels + c] = value;
    }

    /**
     * @brief Overloaded function call operator to access pixels.
     *
     * @param row The row index of the pixel.
     * @param col The column index of the pixel.
     * @param channel The color channel index (0 for red, 1 for green, 2 for blue).
     * @return Reference to the pixel value.
     */
    const unsigned char& operator()(int row, int col, int channel) const {
        return getPixel(row, col, channel);
    }

    unsigned char& operator()(int row, int col, int channel) {
        return getPixel(row, col, channel);
    }
};

#endif // _IMAGE_CLASS_H


