#ifndef IMAGEFILTERS_H
#define IMAGEFILTERS_H

/**
 * @class ImageFilters
 * @brief Encapsulates all image-processing filters used by the GUI.
 *
 * @details Separates image-processing concerns from UI logic and exposes a set
 * of synchronous, CPU-bound operations that mutate an Image instance in-place.
 *
 * @note Long-running filters accept a shared cancellation flag
 * (std::atomic<bool>) that the GUI sets when the user requests cancellation.
 *
 * @note Progress is reported via the provided QProgressBar and messages via
 * QStatusBar. These pointers are non-owning and must remain valid for the
 * lifetime of ImageFilters.
 *
 * @warning All functions assume the passed-in Image objects are valid and
 * appropriately sized unless otherwise noted.
 *
 * @par Threading
 * Functions are intended to run on the GUI thread and cooperatively yield via
 * QApplication::processEvents() in their implementations. If executing on a
 * worker thread, ensure UI interactions are marshalled to the UI thread.
 */

// Forward declaration to avoid including the full Image_Class.h implementation
class Image;
#undef pixel  // Undefine the pixel macro to avoid conflicts with Qt
#include <QProgressBar>
#include <QStatusBar>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <atomic>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

class ImageFilters
{
public:
    /**
     * @brief Constructs a filter engine that reports through the given UI widgets.
     * @param progressBar Progress bar to update (may be nullptr to disable).
     * @param statusBar Status bar for user messages (may be nullptr to disable).
     */
    ImageFilters(QProgressBar* progressBar, QStatusBar* statusBar);
    
    /**
     * @name Filter functions
     * @brief Mutate currentImage in-place. Many accept a pre-operation snapshot
     *        (preFilterImage) used to restore on cancellation.
     * @note On failure (including cancellation), functions may throw
     *       std::exception-derived errors; callers should handle and notify users.
     */
    ///@{
    /** @brief Converts the image to grayscale using average luminance.
     *  @param currentImage Image to mutate in-place.
     *  @param preFilterImage Snapshot used to restore if cancelled.
     *  @param cancelRequested Cooperative cancellation flag.
     *  @throws std::exception On failure or cancellation.
     */
    void applyGrayscale(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    /** @brief Applies a TV noise/static effect overlay.
     *  @param currentImage Image to mutate in-place.
     *  @param preFilterImage Snapshot used to restore if cancelled.
     *  @param cancelRequested Cooperative cancellation flag.
     *  @throws std::exception On failure or cancellation.
     */
    void applyTVFilter(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    /** @brief Converts to high-contrast black & white.
     *  @param currentImage Image to mutate in-place.
     *  @param preFilterImage Snapshot used to restore if cancelled.
     *  @param cancelRequested Cooperative cancellation flag.
     *  @throws std::exception On failure or cancellation.
     */
    void applyBlackAndWhite(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    /** @brief Inverts all pixel channels.
     *  @param currentImage Image to mutate in-place.
     *  @param preFilterImage Snapshot used to restore if cancelled.
     *  @param cancelRequested Cooperative cancellation flag.
     *  @throws std::exception On failure or cancellation.
     */
    void applyInvert(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    /** @brief Blends mergeImage into currentImage (blend mode defined in impl).
     *  @param currentImage Base image to mutate.
     *  @param mergeImage Source image to blend in.
     *  @throws std::exception On failure.
     */
    void applyMerge(Image& currentImage, Image& mergeImage);
    /** @brief Flips image horizontally or vertically.
     *  @param currentImage Image to mutate in-place.
     *  @param direction Flip direction (e.g., "Horizontal", "Vertical").
     *  @throws std::exception On failure.
     */
    void applyFlip(Image& currentImage, const QString& direction);
    /** @brief Rotates the image by a right-angle increment.
     *  @param currentImage Image to mutate in-place.
     *  @param angle Rotation degrees as string (e.g., "90", "180", "270").
     *  @throws std::exception On failure.
     */
    void applyRotate(Image& currentImage, const QString& angle);
    /** @brief Adjusts global brightness.
     *  @param currentImage Image to mutate in-place.
     *  @param choice Adjustment mode (e.g., "Lighten", "Darken").
     *  @throws std::exception On failure.
     */
    void applyDarkAndLight(Image& currentImage, const QString& choice);
    /** @brief Draws a decorative frame around the image.
     *  @param currentImage Image to mutate in-place.
     *  @param frameType Frame style identifier.
     *  @throws std::exception On failure.
     */
    void applyFrame(Image& currentImage, const QString& frameType);
    /** @brief Performs simple edge detection.
     *  @param currentImage Image to mutate in-place.
     *  @throws std::exception On failure.
     */
    void applyEdges(Image& currentImage);
    /** @brief Resizes the image.
     *  @param currentImage Image to mutate in-place.
     *  @param width Target width in pixels.
     *  @param height Target height in pixels.
     *  @throws std::exception On failure.
     */
    void applyResize(Image& currentImage, int width, int height);
    /** @brief Applies a blur (box/gaussian-like) effect; cancellable.
     *  @param currentImage Image to mutate in-place.
     *  @param preFilterImage Snapshot used to restore if cancelled.
     *  @param cancelRequested Cooperative cancellation flag.
     *  @throws std::exception On failure or cancellation.
     */
    void applyBlur(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    /** @brief Applies an infrared-like color mapping; cancellable.
     *  @param currentImage Image to mutate in-place.
     *  @param preFilterImage Snapshot used to restore if cancelled.
     *  @param cancelRequested Cooperative cancellation flag.
     *  @throws std::exception On failure or cancellation.
     */
    void applyInfrared(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    /** @brief Applies a purple-tinted color mapping; cancellable.
     *  @param currentImage Image to mutate in-place.
     *  @param preFilterImage Snapshot used to restore if cancelled.
     *  @param cancelRequested Cooperative cancellation flag.
     *  @throws std::exception On failure or cancellation.
     */
    void applyPurpleFilter(Image& currentImage, Image& preFilterImage, std::atomic<bool>& cancelRequested);
    ///@}

private:
    /** @brief UI elements for progress and status feedback (non-owning). */
    QProgressBar* progressBar;
    QStatusBar* statusBar;
    
    /**
     * @brief Updates the progress bar.
     * @param value Current progress value.
     * @param total Total units of work.
     * @param updateInterval UI update cadence (rows/steps).
     */
    void updateProgress(int value, int total, int updateInterval = 50);
    /**
     * @brief Checks cancellation and restores on cancel.
     * @param cancelRequested Cooperative cancellation flag.
     * @param currentImage Image being mutated; restored on cancel.
     * @param preFilterImage Snapshot to restore from.
     * @param filterName Name used in user-facing status messages.
     * @throws std::exception When cancellation is detected to abort work.
     */
    void checkCancellation(std::atomic<bool>& cancelRequested, Image& currentImage, Image& preFilterImage, const QString& filterName);
};

#endif // IMAGEFILTERS_H
