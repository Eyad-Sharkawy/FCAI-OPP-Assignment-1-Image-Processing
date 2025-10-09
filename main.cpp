//==================================================================================
//                                       Header
//==================================================================================
// section: S33
// group: B
// lab7
// TA: Laila Mostafa
//===================================================================================
// Team members:
// Ahmed Mohamed ElSayed Tolba  // ID: 20242023
// Eyad Mohamed Saad Ali        // ID: 20242062
// Tarek Sami Mohamed Mohamed   // ID: 20242190
//===================================================================================
// Work breakdown:
// Ahmed Mohamed ElSayed Tolba (Small ID): 1, 4,7,10,(17 "bonus"), menu
//
// Eyad Mohamed Saad Ali (Middle ID): 2, 5, 8, 11, (15 "bonus"), menu
//
// Tarek Sami Mohamed Mohamed (Large ID): 3, 6, 9, 12, (16 "bonus"), menu
//===================================================================================
// Document link:
//===================================================================================
// Video link:
//===================================================================================
//                                    End of Header
//========================================Code=======================================

#include <iostream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <random>
#include <chrono>
#include <stack>
#include "Image_Class.h"
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

std::string eraseDoubleQuotes(std::string &r) {
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
Image simpleFrame(Image &image);// Tarek
Image decoratedFrame(Image &image);// Tarek

//Filter 10
Image edges(Image &image);//Ahmed

//Filter 11
Image resize(Image image, size_t w, size_t h);//Eyad

//Filter 12
Image blurImage(Image &image);// Tarek

//Filetr 16 (bonus)
Image purpleFilter(Image &image);// Tarek

//Filter 17 (bonus)
Image infraredbonus(Image &image); //Ahmed

//TV/CRT Filter
Image tvFilter(Image &image); //Eyad

static void clearStack(std::stack<Image> &s) {
    while (!s.empty()) s.pop();
}

static void saveStateForUndo(std::stack<Image> &undoStack, std::stack<Image> &redoStack, const Image &current) {
    undoStack.push(current);
    // any new action invalidates redo history
    clearStack(redoStack);
}

static bool doUndo(std::stack<Image> &undoStack, std::stack<Image> &redoStack, Image &current) {
    if (undoStack.empty()) return false;
    redoStack.push(current);
    current = undoStack.top();
    undoStack.pop();
    return true;
}

static bool doRedo(std::stack<Image> &undoStack, std::stack<Image> &redoStack, Image &current) {
    if (redoStack.empty()) return false;
    undoStack.push(current);
    current = redoStack.top();
    redoStack.pop();
    return true;
}

int main() {
    Image image;
    Image result;
    bool hasImage = false;
    bool running = true;
    bool unsavedChanges = false;
    std::stack<Image> undoStack;
    std::stack<Image> redoStack;
    std::string file;
    std::string imagePath;
    std::cout << "===================================================\n";
    std::cout << "=       Welcome to the Image Processing App       =\n";
    std::cout << "===================================================\n";
    std::cout << "Press Enter to continue...\n";
    std::cin.ignore();

    while (!hasImage) {
        std::cout << "Enter image path and name to load: ";
        std::getline(std::cin, imagePath);
        normalizePathSeparators(imagePath);
        lowercaseExtension(imagePath);
        eraseDoubleQuotes(imagePath);
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
        std::cout << "  7.  DarkAndLight\n";
        std::cout << "  8.  Crop\n";
        std::cout << "  9.  Frame\n";
        std::cout << "  10. Detect Image Edges\n";
        std::cout << "  11. Resizing Images\n";
        std::cout << "  12. Blur Images\n";
        std::cout << "  13. infrared\n";
        std::cout << "  14. purpleFilter\n";
        std::cout << "  15. TV/CRT Filter\n";
        std::cout << "  16. Reset to Original\n";
        std::cout << "  17. Undo\n";
        std::cout << "  18. Redo\n";
        std::cout << "  19. Save current image\n";
        std::cout << "  20. Exit\n";
        int choice = readIntInRange("Enter your choice: ", 0, 20);
        switch (choice) {
            case 0: {
                if (unsavedChanges) {
                    char ans = readCharChoice("You have unsaved changes. Save before loading new image? (y/n): ",
                                              "yn");
                    if ('y' == ans) {
                        bool saveSuccess = false;
                        std::string savePath;
                        while (!saveSuccess) {
                            std::cout << "Enter the image path and name to save in: ";
                            readLine(savePath);
                            normalizePathSeparators(savePath);
                            lowercaseExtension(savePath);
                            eraseDoubleQuotes(savePath);
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
                    std::cout << "Enter image path and name to load: ";
                    readLine(imagePath);
                    normalizePathSeparators(imagePath);
                    lowercaseExtension(imagePath);
                    eraseDoubleQuotes(imagePath);
                    try {
                        image = Image(imagePath);
                        result = image;
                        hasImage = true;
                        loadSuccess = true;
                        unsavedChanges = false;
                        clearStack(undoStack);
                        clearStack(redoStack);
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
                    saveStateForUndo(undoStack, redoStack, result);
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
                    saveStateForUndo(undoStack, redoStack, result);
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
                    saveStateForUndo(undoStack, redoStack, result);
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
                        std::cout << "Enter the second image path and name to merge: ";
                        readLine(tempPath);
                        normalizePathSeparators(tempPath);
                        lowercaseExtension(tempPath);
                        eraseDoubleQuotes(tempPath);
                        try {
                            Image image2(tempPath);
                            saveStateForUndo(undoStack, redoStack, result);
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
                            saveStateForUndo(undoStack, redoStack, result);
                            result = flipVertically(result);
                            break;
                        } else if (op == 'h') {
                            saveStateForUndo(undoStack, redoStack, result);
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
                            saveStateForUndo(undoStack, redoStack, result);
                            result = rotate90(result);
                            break;
                        } else if (op == 180) {
                            saveStateForUndo(undoStack, redoStack, result);
                            result = rotate180(result);
                            break;
                        } else if (op == 270) {
                            saveStateForUndo(undoStack, redoStack, result);
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
                    saveStateForUndo(undoStack, redoStack, result);
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
                    saveStateForUndo(undoStack, redoStack, result);
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
                if (hasImage) {
                    while (true) {
                        char op = readCharChoice(
                            "Do You want simple or decorated frame ? \n S/D", "sd");
                        if (op == 's') {
                            saveStateForUndo(undoStack, redoStack, result);
                            result = simpleFrame(result);
                            break;
                        } else if (op == 'd') {
                            saveStateForUndo(undoStack, redoStack, result);
                            result = decoratedFrame(result);
                            break;
                        } else {
                            std::cout << "Error!\nInput a correct option" << std::endl;
                        }
                    }
                    unsavedChanges = true;
                    std::cout << "Frame is done.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }

                break;

            case 10:
                if (hasImage) {
                    saveStateForUndo(undoStack, redoStack, result);
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
                        saveStateForUndo(undoStack, redoStack, result);
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
                if (hasImage) {
                    saveStateForUndo(undoStack, redoStack, result);
                    result = blurImage(result);
                    unsavedChanges = true;
                    std::cout << "Applied Blur.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
                break;
            case 13:
                if (hasImage) {
                    saveStateForUndo(undoStack, redoStack, result);
                    result = infraredbonus(result);
                    unsavedChanges = true;
                    std::cout << "Applied infrared.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
            break;
            case 14:
                if (hasImage) {
                    saveStateForUndo(undoStack, redoStack, result);
                    result = purpleFilter(result);
                    unsavedChanges = true;
                    std::cout << "Applied Purple.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
                break;
            case 15:
                if (hasImage) {
                    saveStateForUndo(undoStack, redoStack, result);
                    result = tvFilter(result);
                    unsavedChanges = true;
                    std::cout << "Applied TV/CRT Filter.\n";
                    std::cout << "=============================================\n";
                } else {
                    std::cout << "=============================================\n";
                    std::cout << "error" << std::endl;
                    std::cout << "please load an image" << std::endl;
                    std::cout << "=============================================\n";
                }
                break;
            case 16: { // Reset
                        if (hasImage) {
                            saveStateForUndo(undoStack, redoStack, result);
                            result = image; // restore to original loaded image
                            unsavedChanges = true;
                            std::cout << "Image reset to original.\n";
                            std::cout << "=============================================\n";
                        } else {
                            std::cout << "error" << std::endl;
                            std::cout << "please load an image" << std::endl;
                        }
                        break; }
            case 17: { // Undo
                        if (hasImage) {
                            if (doUndo(undoStack, redoStack, result)) {
                                unsavedChanges = true;
                                std::cout << "Undo done.\n";
                            } else {
                                std::cout << "Nothing to undo.\n";
                            }
                            std::cout << "=============================================\n";
                        } else {
                            std::cout << "error" << std::endl;
                            std::cout << "please load an image" << std::endl;
                        }
                        break; }
            case 18: { // Redo
                        if (hasImage) {
                            if (doRedo(undoStack, redoStack, result)) {
                                unsavedChanges = true;
                                std::cout << "Redo done.\n";
                            } else {
                                std::cout << "Nothing to redo.\n";
                            }
                            std::cout << "=============================================\n";
                        } else {
                            std::cout << "error" << std::endl;
                            std::cout << "please load an image" << std::endl;
                        }
                        break; }
            case 19:
                        if (hasImage) {
                            char ans = readCharChoice("Save to same file or new file? (s/n): ", "sn");
                            std::string savePath;
                            if (ans == 's') {
                                savePath = imagePath;
                            } else {
                                std::cout << "Enter the image path and name to save in: ";
                                readLine(savePath);
                                normalizePathSeparators(savePath);
                                lowercaseExtension(savePath);
                                eraseDoubleQuotes(savePath);
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
                                    eraseDoubleQuotes(savePath);
                                    std::cout << "=============================================\n";
                                }
                            }
                        } else {
                            std::cout << "error" << std::endl;
                            std::cout << "please load an image" << std::endl;
                        }
                    break;
                    case 20: {
                        if (unsavedChanges) {
                            char ans = readCharChoice("You have unsaved changes. Save before exiting? (y/n): ",
                                                      "yn");
                            if ('y' == ans) {
                                // Modified: Add retry loop for saving unsaved changes before exit
                                bool saveSuccess = false;
                                std::string savePath;
                                while (!saveSuccess) {
                                    std::cout << "Enter the image path and name to save in: ";
                                    readLine(savePath);
                                    normalizePathSeparators(savePath);
                                    lowercaseExtension(savePath);
                                    eraseDoubleQuotes(savePath);
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
                        running = false;
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

Image simpleFrame(Image &image) {
    int frameSize = 10;
    Image editedImage(image.width + 2* frameSize ,image.height + 2* frameSize);
    for (int y = 0; y < editedImage.height ; y++)
    {
        for (int x = 0; x < editedImage.width; x++)
        {

                editedImage.setPixel(x, y, 0, 0);
                editedImage.setPixel(x, y, 1, 0);
                editedImage.setPixel(x, y, 2, 255);

        }
    }

    for (int y = 0; y < image.height ; y++) {
        for (int x = 0; x < image.width; x++) {
            for (int c = 0; c < 3; c++) {
                int pixelValue = image(x,y,c);
                editedImage.setPixel(x + frameSize, y + frameSize, c, pixelValue);
            }
        }
    }
    return editedImage;
}


Image decoratedFrame(Image &image) {
    int frameSize = 10;
    int innerFrame = 5;
    Image editedImage(image.width + 2* frameSize ,image.height + 2* frameSize);
    for (int y = 0; y < editedImage.height ; y++)
    {
        for (int x = 0; x < editedImage.width; x++)
        {

            editedImage.setPixel(x, y, 0, 0);
            editedImage.setPixel(x, y, 1, 0);
            editedImage.setPixel(x, y, 2, 255);

        }
    }

    for (int y = 0; y < image.height ; y++) {
        for (int x = 0; x < image.width; x++) {
            for (int c = 0; c < 3; c++) {
                int pixelValue = image(x,y,c);
                editedImage.setPixel(x + frameSize, y + frameSize, c, pixelValue);
            }
        }
    }
    int gap = 5;
    for (int y = frameSize+gap ; y < frameSize + image.height -gap; y++)
    {
        for (int x = frameSize +gap; x < frameSize + image.width -gap; x++)
        {

            bool isWhiteBorder =
                          (x < frameSize + gap + innerFrame ||
                           x >= frameSize + image.width - gap - innerFrame ||
                           y < frameSize + gap + innerFrame ||
                           y >= frameSize + image.height - gap - innerFrame);

            if (isWhiteBorder) {
                editedImage.setPixel(x, y, 0, 255); // R
                editedImage.setPixel(x, y, 1, 255); // G
                editedImage.setPixel(x, y, 2, 255); // B
            }
        }
    }
     return editedImage;
}

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
Image blurImage(Image &image) {
        int blurSize = 15;
        Image blurred(image.width, image.height);

        for (int y = 0; y < image.height; y++) {
            for (int x = 0; x < image.width; x++) {

                int R = 0, G = 0, B = 0;
                int count = 0;

                for (int i = -blurSize; i <= blurSize; i++) {
                    for (int j = -blurSize; j <= blurSize; j++) {
                        int nx = x + j;
                        int ny = y + i;


                        if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height) {
                            R += image(nx, ny, 0);
                            G += image(nx, ny, 1);
                            B += image(nx, ny, 2);
                            count++;
                        }
                    }
                }


                blurred.setPixel(x, y, 0, R / count);
                blurred.setPixel(x, y, 1, G / count);
                blurred.setPixel(x, y, 2, B / count);
            }
        }

      return blurred;
    }

// Filter 16 (bonus)
Image purpleFilter(Image &image) {
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            int r = image(x, y, 0);
            int g = image(x, y, 1);
            int b = image(x, y, 2);


            r = std::min(255, (int)(r * 1.3));
            g = std::max(0,   (int)(g * 0.5));
            b = std::min(255, (int)(b * 1.3));


            image.setPixel(x, y, 0, r);
            image.setPixel(x, y, 1, g);
            image.setPixel(x, y, 2, b);
        }
    }
    return image;
}
//Filter 17 (bonus)
Image infraredbonus(Image &image) {
    for (int x = 0; x < image.width; ++x) {
        for (int y = 0; y < image.height; ++y) {

            int red   = image(x, y, 0);
            int green = image(x, y, 1);
            int blue  = image(x, y, 2);

            float brightness = (red + green + blue) / 3.0f;

            float inverted = 255 - brightness;

            int R = 255;
            unsigned int G = int(inverted);
            unsigned int B = int(inverted);

            image(x, y, 0) = R;
            image(x, y, 1) = G;
            image(x, y, 2) = B;
        }
    }
    return image;
}

//TV/CRT Filter - Creates retro TV monitor effect
Image tvFilter(Image &image) {
    // Create a copy to work with
    Image result = image;
    
    // Initialize random number generator with time-based seed
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> noise_dist(-10, 10);
    
    for (int y = 0; y < result.height; y++) {
        for (int x = 0; x < result.width; x++) {
            // Get original pixel values
            int r = result(x, y, 0);
            int g = result(x, y, 1);
            int b = result(x, y, 2);
            
            // 1. Add horizontal scanlines (dark lines every few pixels)
            float scanlineIntensity = 1.0f;
            if (y % 3 == 0) {  // Every 3rd row gets darker
                scanlineIntensity = 0.7f;
            }
            
            // 2. Color shift and glow effect
            // Enhance blues and purples, add warm orange highlights
            float brightness = (r + g + b) / 3.0f / 255.0f;
            
            // Add blue/purple tint to darker areas
            if (brightness < 0.5f) {
                r = std::min(255, static_cast<int>(r * 0.8f));
                g = std::min(255, static_cast<int>(g * 0.7f));
                b = std::min(255, static_cast<int>(b * 1.2f));
            }
            
            // Add warm orange glow to bright areas
            if (brightness > 0.7f) {
                r = std::min(255, static_cast<int>(r * 1.3f));
                g = std::min(255, static_cast<int>(g * 1.1f));
                b = std::max(0, static_cast<int>(b * 0.9f));
            }

            // 3. Apply scanline effect
            r = static_cast<int>(r * scanlineIntensity);
            g = static_cast<int>(g * scanlineIntensity);
            b = static_cast<int>(b * scanlineIntensity);
            
            // 5. Add slight noise/grain for authentic TV feel
            int noise = noise_dist(rng); // -10 to +10
            r = std::min(255, std::max(0, r + noise));
            g = std::min(255, std::max(0, g + noise));
            b = std::min(255, std::max(0, b + noise));
            
            // Set the final pixel
            result.setPixel(x, y, 0, r);
            result.setPixel(x, y, 1, g);
            result.setPixel(x, y, 2, b);
        }
    }
    
    return result;
}
