#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include "Image_Class.h"

// Ahmed Mohamed ElSayed Tolba (Small ID) Responsible for 1, 4
// ID: 20242023
//
// Eyad Mohamed Saad Ali (Middle ID) 2, 5
// ID: 20242062
//
// Tarek Sami Mohamed Mohamed (Large ID) 3, 6
// ID: 20242190

static void normalizePathSeparators(std::string &p) {
    for (size_t i = 0; i < p.size(); ++i) {
        if (p[i] == '\\') p[i] = '/';
    }
}

static void lowercaseExtension(std::string &p) {
    const size_t dotPos = p.find_last_of('.');
    if (dotPos == std::string::npos) return;
    for (size_t i = dotPos; i < p.size(); ++i) {
        p[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(p[i])));
    }
}

static std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::string erasedoublecaughts(std::string &r) {
    if (!r.empty() && r.front() == '"')
        r.erase(r.begin());
    if (!r.empty() && r.back() == '"')
        r.pop_back();
    return r;
}

static void readLine(std::string &out) {
    std::getline(std::cin, out);
    if (!std::cin) {
        std::cin.clear();
    }
    out = trim(out);
}

static int readIntInRange(const std::string &prompt, int minVal, int maxVal) {
    while (true) {
        std::cout << prompt;
        std::string line;
        readLine(line);
        std::istringstream iss(line);
        int value;
        char extra;
        if (iss >> value && !(iss >> extra) && value >= minVal && value <= maxVal) return value;
        std::cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << "\n";
    }
}

static int readIntFromSet(const std::string &prompt, const std::initializer_list<int> &valid) {
    while (true) {
        std::cout << prompt;
        std::string line;
        readLine(line);
        std::istringstream iss(line);
        int value;
        char extra;
        if (iss >> value && !(iss >> extra)) {
            for (int v: valid) if (v == value) return value;
        }
        std::cout << "Invalid input. Please enter one of the allowed values.\n";
    }
}

static char readCharChoice(const std::string &prompt, const std::string &validChars) {
    while (true) {
        std::cout << prompt;
        std::string line;
        readLine(line);
        if (line.size() == 1) {
            char c = static_cast<char>(std::tolower(static_cast<unsigned char>(line[0])));
            if (validChars.find(c) != std::string::npos) return c;
        }
        std::cout << "Invalid input. Please enter one of: " << validChars << "\n";
    }
}

static size_t readSizeT(const std::string &prompt, size_t minVal = 1) {
    while (true) {
        std::cout << prompt;
        std::string line;
        readLine(line);
        std::istringstream iss(line);
        long long v;
        char extra;
        if (iss >> v && !(iss >> extra) && v >= static_cast<long long>(minVal)) return static_cast<size_t>(v);
        std::cout << "Invalid input. Please enter an integer >= " << minVal << "\n";
    }
}

static void readTwoSizeT(size_t &a, size_t &b, const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        readLine(line);
        std::istringstream iss(line);
        long long v1, v2;
        char extra;
        if (iss >> v1 >> v2 && !(iss >> extra) && v1 > 0 && v2 > 0) {
            a = static_cast<size_t>(v1);
            b = static_cast<size_t>(v2);
            return;
        }
        std::cout << "Invalid input. Please enter two positive integers separated by space.\n";
    }
}

static void readFourSizeT(size_t &a, size_t &b, size_t &c, size_t &d, const std::string &prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        readLine(line);
        std::istringstream iss(line);
        long long v1, v2, v3, v4;
        char extra;
        if (iss >> v1 >> v2 >> v3 >> v4 && !(iss >> extra) && v1 >= 0 && v2 >= 0 && v3 > 0 && v4 > 0) {
            a = static_cast<size_t>(v1);
            b = static_cast<size_t>(v2);
            c = static_cast<size_t>(v3);
            d = static_cast<size_t>(v4);
            return;
        }
        std::cout << "Invalid input. Please enter four integers: x y w h (w,h > 0).\n";
    }
}

// Filter 1
Image blackAndWhite(const Image &image); // Ahmed

// Filter 2
Image pureBlackAndWhite(const Image &image); // Eyad

// Filter 3
Image invert(const Image &image); // Tarek

// Filter 4
Image merge(const Image &image1, const Image &image2); // Ahmed

// Filter 5
Image flipHorizontally(Image image); //Eyad
Image flipVertically(const Image &image); //Eyad

// Filter 6
Image rotate90(const Image &image); // Tarek
Image rotate180(const Image &image); // Tarek
Image rotate270(const Image &image); // Tarek

//Filter 7
Image darkandlight(Image &image);//Ahmed

//Filter 8
Image crop(Image image, size_t x, size_t y, size_t w, size_t h);//Eyad

//Filter9

//Filter 10
Image edges(Image &image);//Ahmed

//Filter 11
Image resize(Image image, size_t w, size_t h);//Eyad

//filter 12


int main() {
    Image image;
    Image result;
    bool hasImage = false;
    bool running = true;
    bool unsavedChanges = false;
    std::string file;
    std::string imagePath;
    std::cout << "===================================================\n";
    std::cout << "=       Welcome to the Image Processing App       =\n";
    std::cout << "===================================================\n";
    std::cout << "Press Enter to continue...\n";
    std::cin.ignore();

    while (!hasImage) {
        std::cout << "Enter image path to load: ";
        std::getline(std::cin, imagePath);
        normalizePathSeparators(imagePath);
        lowercaseExtension(imagePath);
        erasedoublecaughts(imagePath);
        try {
            image = Image(imagePath);
            result = image;
            hasImage = true;
            std::cout << "Image loaded successfully.\n";
            std::cout << "=============================================\n";
        } catch (const std::exception &e) {
            std::cout << "Failed to load image: " << e.what() << "\n";
            std::cout << "Please try again.\n";
            std::cout << "=============================================\n";
        }
    }
    while (running) {
        std::cout << "Menu Options:\n";
        std::cout << "  0.  Load a new image\n";
        std::cout << "  1.  Grayscale\n";
        std::cout << "  2.  Black and White\n";
        std::cout << "  3.  Invert Colors\n";
        std::cout << "  4.  Merge with Another Image\n";
        std::cout << "  5.  Flip\n";
        std::cout << "  6.  Rotate\n";
        std::cout << "  7.  Darkandlight \n";
        std::cout << "  9.  Frame \n";
        std::cout << "  10. Detect Image Edges  \n";
        std::cout << "  11. Resizing Images \n";
        std::cout << "  12. Blur Images \n";
        std::cout << "  13. Save current image\n";
        std::cout << "  14. Exit\n";
        int choice = readIntInRange("Enter your choice: ", 0, 14);
        switch (choice) {
            case 0: {
                if (unsavedChanges) {
                    char ans = readCharChoice("You have unsaved changes. Save before loading new image? (y/n): ",
                                              "yn");
                    if ('y' == ans) {
                        bool saveSuccess = false;
                        std::string savePath;
                        while (!saveSuccess) {
                            std::cout << "Enter the image path to save in: ";
                            readLine(savePath);
                            normalizePathSeparators(savePath);
                            lowercaseExtension(savePath);
                            erasedoublecaughts(savePath);
                            try {
                                result.saveImage(savePath);
                                saveSuccess = true;
                                unsavedChanges = false;
                                std::cout << "Image saved successfully as " << savePath << std::endl;
                                std::cout << "=============================================\n";
                            } catch (const std::exception &e) {
                                std::cout << "Failed to save image: " << e.what() << "\n";
                                std::cout << "Please try a different path.\n";
                                std::cout << "=============================================\n";
                            }
                        }
                    }
                }
                bool loadSuccess = false;
                while (!loadSuccess) {
                    std::cout << "Enter image path to load: ";
                    readLine(imagePath);
                    normalizePathSeparators(imagePath);
                    lowercaseExtension(imagePath);
                    erasedoublecaughts(imagePath);
                    try {
                        image = Image(imagePath);
                        result = image;
                        hasImage = true;
                        loadSuccess = true;
                        unsavedChanges = false;
                        std::cout << "Image loaded successfully.\n";
                        std::cout << "=============================================\n";
                    } catch (const std::exception &e) {
                        std::cout << "Failed to load image: " << e.what() << "\n";
                        std::cout << "Please try again.\n";
                        std::cout << "=============================================\n";
                    }
                }
                break;
            }
            case 1:
                if (hasImage) {
                    result = blackAndWhite(result);
                    unsavedChanges = true;
                    std::cout << "Applied Grayscale.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
            break;
            case 2:
                if (hasImage) {
                    result = pureBlackAndWhite(result);
                    unsavedChanges = true;
                    std::cout << "Applied Black & White.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
            break;
            case 3:
                if (hasImage) {
                    result = invert(result);
                    unsavedChanges = true;
                    std::cout << "Applied Invert.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
            break;

            case 4:
                if (hasImage) {
                    std::string tempPath;
                    bool loadSuccess = false;
                    while (!loadSuccess) {
                        std::cout << "Enter the second image path to merge: ";
                        readLine(tempPath);
                        normalizePathSeparators(tempPath);
                        lowercaseExtension(tempPath);
                        erasedoublecaughts(tempPath);
                        try {
                            Image image2(tempPath);
                            result = merge(result, image2);
                            loadSuccess = true;
                            unsavedChanges = true;
                            std::cout << "Merged images.\n";
                            std::cout << "=============================================\n";
                        } catch (const std::exception &e) {
                            std::cout << "Failed to load second image: " << e.what() << "\n";
                            std::cout << "Please try again.\n";
                            std::cout << "=============================================\n";
                        }
                    }
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
                 break;

            case 5:
                if (hasImage) {
                    while (true) {
                        char op = readCharChoice(
                            "Which way do you want to flip the image\n V (Vertical) or H (horizontal)? ", "vh");
                        if (op == 'v') {
                            result = flipVertically(result);
                            break;
                        } else if (op == 'h') {
                            result = flipHorizontally(result);
                            break;
                        } else {
                            std::cout << "Error!\nInput a correct option" << std::endl;
                        }
                    }
                    unsavedChanges = true;
                    std::cout << "Flipped image.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
            break;
            case 6:
                if (hasImage) {
                    while (true) {
                        int op = readIntFromSet("How many degree (90, 180, 270): ", {90, 180, 270});
                        if (op == 90) {
                            result = rotate90(result);
                            break;
                        } else if (op == 180) {
                            result = rotate180(result);
                            break;
                        } else if (op == 270) {
                            result = rotate270(result);
                            break;
                        } else {
                            std::cout << "Error!\nInput a correct option" << std::endl;
                        }
                    }
                    unsavedChanges = true;
                    std::cout << "Rotated image.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
            break;
            case 7:
                if (hasImage) {
                    result = darkandlight(result);
                    unsavedChanges = true;
                    std::cout << "Applied darkandlight edit.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
                    break;
            case 8:
                if (hasImage) {
                    size_t x, y, w, h;
                    readFourSizeT(x, y, w, h, "Enter crop x y w h: ");
                    if (x + w > static_cast<size_t>(result.width) || y + h > static_cast<size_t>(result.height)) {
                        std::cout << "Crop rectangle out of bounds\n";
                        break;
                    }
                    result = crop(result, x, y, w, h);
                    unsavedChanges = true;
                    std::cout << "Cropped image.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                }
                break;
            case 9:
                break;
            case 10:
                if (hasImage) {
                    result = edges(result);
                    unsavedChanges = true;
                    std::cout << "Applied edge detecting .\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
                break;
            case 11:
                if (hasImage) {
                        size_t w, h;
                        readTwoSizeT(w, h, "Enter new width and height: ");
                        result = resize(result, w, h);
                        unsavedChanges = true;
                        std::cout << "Resized image to " << w << "x" << h << "\n";
                        std::cout << "=============================================\n";
                    } else {
                        std::cout << "error" << std::endl;
                        std::cout << "please load an image" << std::endl;
                    }
                    break;
            case 12:
                break;
            case 13:
                        if (hasImage) {
                            char ans = readCharChoice("Save to same file or new file? (s/n): ", "sn");
                            std::string savePath;
                            if (ans == 's') {
                                savePath = imagePath;
                            } else {
                                std::cout << "Enter the image path to save in: ";
                                readLine(savePath);
                                normalizePathSeparators(savePath);
                                lowercaseExtension(savePath);
                                erasedoublecaughts(savePath);
                            }
                            bool saveSuccess = false;
                            while (!saveSuccess) {
                                try {
                                    result.saveImage(savePath);
                                    saveSuccess = true;
                                    std::cout << "Image saved as " << savePath << std::endl;
                                    unsavedChanges = false;
                                    std::cout << "=============================================\n";
                                } catch (const std::exception &e) {
                                    std::cout << "Failed to save image: " << e.what() << "\n";
                                    std::cout << "Please enter a new path to save: ";
                                    readLine(savePath);
                                    normalizePathSeparators(savePath);
                                    lowercaseExtension(savePath);
                                    erasedoublecaughts(savePath);
                                    std::cout << "=============================================\n";
                                }
                            }
                        } else {
                            std::cout << "error" << std::endl;
                            std::cout << "please load an image" << std::endl;
                        }
                    break;
                    case 14: {
                        if (unsavedChanges) {
                            char ans = readCharChoice("You have unsaved changes. Save before exiting? (y/n): ",
                                                      "yn");
                            if ('y' == ans) {
                                // Modified: Add retry loop for saving unsaved changes before exit
                                bool saveSuccess = false;
                                std::string savePath;
                                while (!saveSuccess) {
                                    std::cout << "Enter the image path to save in: ";
                                    readLine(savePath);
                                    normalizePathSeparators(savePath);
                                    lowercaseExtension(savePath);
                                    erasedoublecaughts(savePath);
                                    try {
                                        result.saveImage(savePath);
                                        saveSuccess = true;
                                        unsavedChanges = false;
                                        std::cout << "Image saved successfully as " << savePath << std::endl;
                                        std::cout << "=============================================\n";
                                    } catch (const std::exception &e) {
                                        std::cout << "Failed to save image: " << e.what() << "\n";
                                        std::cout << "Please try a different path.\n";
                                        std::cout << "=============================================\n";
                                    }
                                }
                            }
                        }running = false;
                        std::cout << "Exiting program.\n";
                        break;
                    }
                    default: {
                        std::cout << "Invalid choice! Try again.\n";
                    }
                }
        }

    return 0;
}

//Filter 1
Image blackAndWhite(const Image &image) {
    Image result(image.width, image.height);

    for (size_t i = 0; i < result.width; ++i) {
        for (size_t j = 0; j < result.height; ++j) {
            unsigned int avg = 0;
            for (size_t k = 0; k < result.channels; ++k) {
                avg += image(i, j, k);
            }

            avg /= 3;

            for (size_t k = 0; k < image.channels; ++k) {
                result(i, j, k) = avg;
            }
        }
    }
    return result;
}

//Filter 2
Image pureBlackAndWhite(const Image &image){
    Image result = blackAndWhite(image);

    for (size_t i = 0; i < result.width; ++i) {
        for (size_t j = 0; j < result.height; ++j) {
            for (size_t k = 0; k < image.channels; ++k) {
                result(i, j, k) = result(i, j, k) > 128 ? 255 : 0;
            }
        }
    }
    return result;
}

// Filter 3
Image invert(const Image &image) {
    Image result = image;

    for (int i = 0; i < result.width; ++i) {
        for (int j = 0; j < result.height; ++j) {
            for (int k = 0; k < result.channels; ++k) {
                result(i, j, k) = 255 - result(i, j, k);
            }
        }
    }
    return result;
}

// Filter 4
Image resize(Image image, size_t w, size_t h);

Image merge(const Image &image1, const Image &image2) {
    int w = std::min(image1.width, image2.width);
    int h = std::min(image1.height, image2.height);
    Image resized1 = resize(image1, w, h);
    Image resized2 = resize(image2, w, h);
    Image result(w, h);

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            for (int k = 0; k < result.channels; ++k) {
                result(i, j, k) = (resized1(i, j, k) + resized2(i, j, k)) / 2;
            }
        }
    }
    return result;
}

//Filter 5
Image flipHorizontally(Image image) {
    Image result(image.width, image.height);
    size_t right = 0;
    size_t left = result.width - 1;

    while (right <= left) {
        for (size_t i = 0; i < result.height; ++i) {
            for (size_t j = 0; j < result.channels; ++j) {
                result(right, i, j) = image(left, i, j);
                result(left, i, j) = image(right, i, j);
            }
        }
        ++right;
        --left;
    }
    return result;
}

Image flipVertically(const Image &image) {
    Image result(image.width, image.height);
    size_t up = 0;
    size_t down = result.height - 1;

    while (up <= down) {
        for (size_t i = 0; i < result.width; ++i) {
            for (size_t j = 0; j < result.channels; ++j) {
                result(i, up, j) = image(i, down, j);
                result(i, down, j) = image(i, up, j);
            }
        }
        ++up;
        --down;
    }
    return result;
}

//Filter 6
Image rotate90(const Image &image) {
    Image rotatedImage = Image(image.height, image.width);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                rotatedImage(j, image.width - 1 - i, k) = image(i, j, k);
            }
        }
    }
    return rotatedImage;
}

Image rotate180(const Image &image) {
    Image rotatedImage = Image(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                rotatedImage(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
            }
        }
    }
    return rotatedImage;
}

Image rotate270(const Image &image) {
    Image rotatedImage = Image(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                rotatedImage(image.height - 1 - j, i, k) = image(i, j, k);
            }
        }
    }
    return rotatedImage;
}

//Filter7
    Image darkandlight(Image &image) {
    std::cout << "Do you want to dark or light \n";
    std::string choice;
    std::cin >> choice;
    Image result(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int p = image(i, j, k);
                if (choice == "dark") {
                    p = p/3;
                }
                else if (choice == "light") {
                    p = p * 2;
                    if (p > 255)
                    {p = 255;}
                }
                result(i, j, k) = p;
            }
        }
    }
    return result;
}

//Filter 8
Image crop(Image image, size_t x, size_t y, size_t w, size_t h) {
    Image result(w, h);
    for (size_t i = 0; i < w; ++i) {
        for (size_t j = 0; j < h; ++j) {
            for (size_t k = 0; k < static_cast<size_t>(image.channels); ++k) {
                result(i, j, static_cast<int>(k)) = image(static_cast<int>(i + x), static_cast<int>(j + y),
                                                          static_cast<int>(k));
            }
        }
    }
    return result;
}

//Filter 9

//Filter 10
Image edges(Image &image) {
    Image blackimage=pureBlackAndWhite(image);
    Image edge(image.width,image.height);
    for (int i = 0; i < blackimage.width - 1; ++i) {
        for (int j = 0; j <blackimage.height - 1; ++j) {
            int current = blackimage(i, j, 0);
            int right   = blackimage(i + 1, j, 0);
            int down    = blackimage(i, j + 1, 0);
            int diff = abs(current - right) + abs(current - down);
            if (diff > 0) {
                edge(i, j, 0) = edge(i, j, 1) = edge(i, j, 2) = 0;
            } else {
                edge(i, j, 0) = edge(i, j, 1) = edge(i, j, 2) = 255;
            }
        }
    }
    return edge;
}

//Filter 11
Image resize(Image image, size_t w, size_t h) {
    Image result(w, h);

    const double xScale = static_cast<double>(image.width) / w;
    const double yScale = static_cast<double>(image.height) / h;

    for (size_t i = 0; i < w; ++i) {
        for (size_t j = 0; j < h; ++j) {
            size_t src_x = static_cast<size_t>(i * xScale);
            size_t src_y = static_cast<size_t>(j * yScale);

            if (src_x >= static_cast<size_t>(image.width)) src_x = static_cast<size_t>(image.width - 1);
            if (src_y >= static_cast<size_t>(image.height)) src_y = static_cast<size_t>(image.height - 1);

            for (size_t k = 0; k < static_cast<size_t>(image.channels); ++k) {
                result(i, j, static_cast<int>(k)) = image(static_cast<int>(src_x), static_cast<int>(src_y),
                                                          static_cast<int>(k));
            }
        }
    }
    return result;
}

//Filter 12
