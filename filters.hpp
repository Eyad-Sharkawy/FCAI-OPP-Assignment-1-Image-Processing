//
// Created by Eyad on 2025-09-21.
//
#ifndef FILTERS_HPP
#define FILTERS_HPP
#include "Image_Class.h"

//Filter 1
Image blackAndWhite(const Image& image) {
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
Image pureBlackAndWhite (const Image& image) {
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

    for (int i=0;i<result.width;++i) {
        for (int j=0;j<result.height;++j) {
            for (int k=0;k<result.channels;++k) {
                result(i,j,k) = 255 - result(i,j,k);
            }
        }
    }
    return result;
}

// Filter 4
Image resize(Image image, size_t w, size_t h);

Image merge(const Image& image1, const Image& image2) {
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

Image flipVertically(const Image& image) {
    Image result(image.width, image.height);
    size_t up = 0;
    size_t down = result.height - 1;

    while (up <= down) {
        for (size_t i = 0; i < result.width; ++i) {
            for (size_t j = 0; j < result.channels; ++j) {
                Image temp(1, 1);

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
Image rotate90 (const Image &image) {
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

Image rotate180 (const Image &image) {
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

Image rotate270 (const Image &image) {
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


//Filter 8
Image crop(Image image, size_t x, size_t y, size_t w, size_t h) {
    Image result(w, h);

    for (size_t i = 0; i < w; ++i) {
        for (size_t j = 0; j < h; ++j) {
            for (size_t k = 0; k < 3; ++k) {
                result(i, j, k) = image(i + x, j + y, k);
            }
        }
    }
    return result;
}


//Filter 11
Image resize(Image image, size_t w, size_t h) {
    Image result(w, h);

    const double xScale = static_cast<double>(image.width) / w;
    const double yScale = static_cast<double>((image.height)) / h;

    for (size_t i = 0; i < w; ++i) {
        for (size_t j = 0; j < h; ++j) {
            size_t src_x = static_cast<size_t>(i * xScale);
            size_t src_y = static_cast<size_t>(j * yScale);

            if (src_x >= image.width) src_x = image.width - 1;
            if (src_y >= image.height) src_y = image.height - 1;

            for (size_t k = 0; k < image.channels; ++k) {
                result(i, j, k) = image(src_x, src_y, k);
            }
        }
    }

    return result;
}


// case 7: if (hasImage) {
//     size_t w, h;
//     readTwoSizeT(w, h, "Enter new width and height: ");
//     result = resize(result, w, h);
//     unsavedChanges = true;
//     std::cout << "Resized image to " << w << "x" << h << "\n";
//     std::cout << "=============================================\n";
// } else {
//     std::cout << "error" << std::endl;
//     std::cout << "please load an image" << std::endl;
// }
// break;
// case 8: if (hasImage) {
//     size_t x, y, w, h;
//     readFourSizeT(x, y, w, h, "Enter crop x y w h: ");
//     if (x + w > static_cast<size_t>(result.width) || y + h > static_cast<size_t>(result.height)) {
//         std::cout << "Crop rectangle out of bounds\n";
//         break;
//     }
//     result = crop(result, x, y, w, h);
//     unsavedChanges = true;
//     std::cout << "Cropped image.\n";
//     std::cout << "=============================================\n";
// } else {
//     std::cout << "error" << std::endl;
//     std::cout << "please load an image" << std::endl;
// }
// break;

#endif //FILTERS_HPP
