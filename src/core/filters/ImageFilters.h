/**
* @File  : ImageFilters.h
 * @brief : This file contains the declaration of the Image Filters.
 *
 * @authors : Eyad Sharkawy, Ahmed Tolba , Tarek Sami.
 * @copyright : FCAI Cairo University
 * @version   : v2.0.0
 * @date      : 13/10/2025
 */

#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

// Forward declaration to avoid including the full Image_Class.h implementation
class Image;
#undef pixel  // Undefine the pixel macro to avoid conflicts with Qt
class QProgressBar; // forward declaration to avoid heavy Qt includes in header
class QStatusBar;   // forward declaration
class QString;      // forward declaration
#include <atomic>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

class ImageFilters
{
public:
    ImageFilters(QProgressBar* progressBar, QStatusBar* statusBar);
    void applyGrayscale(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    void applyTVFilter(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    void applyBlackAndWhite(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    void applyInvert(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    void applyMerge(Image& currentImage, Image& mergeImage);
    void applyFlip(Image& currentImage, const QString& direction);
    void applyRotate(Image& currentImage, const QString& angle);
    void applyDarkAndLight(Image& currentImage, const QString& choice);
    void applyFrame(Image& currentImage, const QString& frameType);
    void applyEdges(Image& currentImage);
    void applyResize(Image& currentImage, int width, int height);
    void applyBlur(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    void applyInfrared(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    void applyPurpleFilter(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);

private:
    QProgressBar* progressBar;
    QStatusBar* statusBar;
    void updateProgress(int value, int total, int updateInterval = 50);
    void checkCancellation(std::atomic<bool>& cancelRequested, Image& currentImage, Image& preFilterImage, const QString& filterName);
};

#endif // IMAGEFILTERS_H


