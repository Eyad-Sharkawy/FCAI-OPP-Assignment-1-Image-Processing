/**
 * @file ImageIO.h
 * @brief Qt-integrated image file I/O operations with comprehensive error handling.
 * 
 * This file provides a high-level interface for loading and saving images using Qt's
 * file system integration. It wraps the underlying Image class functionality with
 * proper error handling, file validation, and Qt string compatibility.
 * 
 * @details The ImageIO class provides:
 * - Safe file loading with existence and format validation
 * - Safe file saving with path validation
 * - Qt QString integration for cross-platform path handling
 * - Comprehensive error handling with descriptive exceptions
 * - Support for all image formats supported by the Image class
 * 
 * @features
 * - File existence validation before loading
 * - Path validation for both load and save operations
 * - Exception safety with descriptive error messages
 * - Qt integration for seamless GUI application use
 * - Support for multiple image formats (PNG, JPEG, BMP, TGA)
 * 
 * @author Team Members:
 * - Ahmed Mohamed ElSayed Tolba (ID: 20242023)
 * - Eyad Mohamed Saad Ali (ID: 20242062) 
 * - Tarek Sami Mohamed Mohamed (ID: 20242190)
 * 
 * @institution Faculty of Computers and Artificial Intelligence, Cairo University
 * @version 2.0.0
 * @date October 13, 2025
 * @copyright FCAI Cairo University
 */

#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <QString>
#include <QFileInfo>
#include <stdexcept>
#include "../image/Image_Class.h"

/**
 * @class ImageIO
 * @brief Static utility class for Qt-integrated image file I/O operations.
 * 
 * This class provides a high-level, Qt-friendly interface for loading and saving
 * images. It handles file validation, error checking, and provides clear error
 * messages for common I/O issues.
 * 
 * @details The class uses static methods to provide a simple, stateless interface
 * for image I/O operations. All methods include comprehensive error handling and
 * validation to ensure robust operation in GUI applications.
 * 
 * @note This class is designed to work with the Image class and requires Qt 6.8.1 or later.
 * @see Image class for the underlying image data structure and STB integration
 * @see QFileInfo for file system operations
 */
class ImageIO {
public:
    /**
     * @brief Loads an image from the specified file path.
     * 
     * This method validates the file path, checks for file existence, and loads
     * the image using the underlying Image class. It provides comprehensive
     * error handling for common I/O issues.
     * 
     * @param path Qt string containing the file path to load
     * @return Image object containing the loaded image data
     * 
     * @throws std::invalid_argument if:
     *   - The path is empty
     *   - The file does not exist
     *   - The path does not point to a regular file
     *   - The file format is not supported
     *   - The file is corrupted or cannot be read
     * 
     * @note Supported formats: PNG, JPEG, BMP, TGA
     * @see Image::loadNewImage() for underlying loading implementation
     * @see QFileInfo for file validation
     * 
     * @example
     * @code
     * try {
     *     Image img = ImageIO::loadFromFile("C:/path/to/image.png");
     *     // Use the loaded image
     * } catch (const std::invalid_argument& e) {
     *     QMessageBox::critical(this, "Error", e.what());
     * }
     * @endcode
     */
    static Image loadFromFile(const QString& path)
    {
        if (path.isEmpty()) {
            throw std::invalid_argument("Empty file path");
        }
        QFileInfo fi(path);
        if (!fi.exists() || !fi.isFile()) {
            throw std::invalid_argument("File does not exist");
        }
        Image img;
        img.loadNewImage(path.toStdString());
        return img;
    }

    /**
     * @brief Saves an image to the specified file path.
     * 
     * This method validates the save path and saves the image using the underlying
     * Image class. It handles format detection based on file extension and provides
     * comprehensive error handling.
     * 
     * @param image Const reference to the Image object to save
     * @param path Qt string containing the file path where to save the image
     * 
     * @throws std::invalid_argument if:
     *   - The path is empty
     *   - The file extension is not supported
     *   - The directory does not exist or is not writable
     *   - There is insufficient disk space
     *   - The image data is invalid
     * 
     * @note Supported formats: PNG, JPEG, BMP, TGA
     * @note The format is determined by the file extension
     * @see Image::saveImage() for underlying saving implementation
     * 
     * @example
     * @code
     * try {
     *     ImageIO::saveToFile(currentImage, "C:/path/to/output.jpg");
     *     statusBar()->showMessage("Image saved successfully");
     * } catch (const std::invalid_argument& e) {
     *     QMessageBox::critical(this, "Error", e.what());
     * }
     * @endcode
     */
    static void saveToFile(const Image& image, const QString& path)
    {
        if (path.isEmpty()) {
            throw std::invalid_argument("Empty file path");
        }
        Image copy = image; // saveImage is non-const in current API
        copy.saveImage(path.toStdString());
    }
};

#endif // IMAGEIO_H


