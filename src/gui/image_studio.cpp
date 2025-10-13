/**
 * @file image_studio.cpp
 * @brief Main Qt application class for Image Studio with comprehensive GUI and image processing capabilities.
 * 
 * This file contains the complete implementation of the ImageStudio class, which serves as the main
 * application window for the Image Studio image processing application. It provides a modern Qt-based
 * GUI with drag-and-drop support, real-time progress tracking, comprehensive undo/redo functionality,
 * and seamless integration with the core image processing filters.
 * 
 * @details The ImageStudio class implements:
 * - Complete Qt MainWindow with modern UI design
 * - Drag-and-drop image loading with format validation
 * - Real-time image processing with progress tracking and cancellation
 * - Comprehensive undo/redo system with configurable history limits
 * - Interactive cropping with rubber-band selection
 * - Smart image display with aspect ratio preservation
 * - Menu system with keyboard shortcuts
 * - Status bar with real-time operation feedback
 * - Exception safety and comprehensive error handling
 * 
 * @features
 * - Modern Qt 6 GUI with responsive design
 * - Drag-and-drop image loading (PNG, JPEG, BMP, TGA)
 * - 15+ image processing filters with progress tracking
 * - Interactive cropping with visual selection
 * - Unlimited undo/redo with memory management
 * - Real-time progress bars and status updates
 * - Keyboard shortcuts and menu integration
 * - Smart window resizing with aspect ratio preservation
 * - Comprehensive error handling and user feedback
 * - Thread-safe cancellation for long-running operations
 * 
 * @author Team Members:
 * - Ahmed Mohamed ElSayed Tolba (ID: 20242023) - Small ID: 1, 4, 7, 10, (17 "bonus"), menu
 * - Eyad Mohamed Saad Ali (ID: 20242062) - Middle ID: 2, 5, 8, 11, (15 "bonus"), menu  
 * - Tarek Sami Mohamed Mohamed (ID: 20242190) - Large ID: 3, 6, 9, 12, (16 "bonus"), menu
 * 
 * @institution Faculty of Computers and Artificial Intelligence, Cairo University
 * @section S33, Group B, Lab 7
 * @ta Laila Mostafa
 * @version 2.0.0
 * @date October 13, 2025
 * @copyright FCAI Cairo University
 */

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QPixmap>
#include <QImage>
#include <QIcon>
#include <QMenuBar>
#include <QStatusBar>
#include <QFileInfo>
#include <QDir>
#include <QResizeEvent>
#include <QTimer>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QRubberBand>
#include <QMouseEvent>
#include <QProgressBar>
#include <QCloseEvent>
#include <cmath>
#include <algorithm>
#include <stack>
#include <random>
#include <chrono>
#include <atomic>
#include <functional>
#include "../core/image/Image_Class.h"
#include "../core/filters/ImageFilters.h"
#include "ui_mainwindow.h"
#include "../core/history/HistoryManager.h"
#include "../core/io/ImageIO.h"

/**
 * @class ImageStudio
 * @brief Main Qt application window for Image Studio with comprehensive image processing capabilities.
 * 
 * The ImageStudio class serves as the primary application window and controller for the Image Studio
 * image processing application. It provides a complete Qt-based GUI with modern design patterns,
 * comprehensive image processing capabilities, and seamless integration with the core processing engine.
 * 
 * @details This class implements a complete image processing application with:
 * - Modern Qt 6 MainWindow with responsive UI design
 * - Drag-and-drop image loading with format validation and error handling
 * - Real-time image processing with progress tracking and cancellation support
 * - Comprehensive undo/redo system with configurable memory limits
 * - Interactive cropping with rubber-band selection and coordinate mapping
 * - Smart image display with aspect ratio preservation and dynamic resizing
 * - Complete menu system with keyboard shortcuts and accessibility
 * - Status bar with real-time operation feedback and image information
 * - Exception safety with comprehensive error handling and user feedback
 * - Thread-safe operations with atomic cancellation support
 * 
 * @features
 * - **GUI Components**: Complete Qt Designer integration with modern UI
 * - **Image Loading**: Drag-and-drop support for PNG, JPEG, BMP, TGA formats
 * - **Image Processing**: 15+ professional filters with real-time progress tracking
 * - **History Management**: Unlimited undo/redo with configurable memory limits
 * - **Interactive Cropping**: Visual selection with coordinate mapping
 * - **Smart Display**: Aspect ratio preservation with dynamic window resizing
 * - **Menu Integration**: Complete menu system with keyboard shortcuts
 * - **Progress Tracking**: Real-time progress bars and status updates
 * - **Error Handling**: Comprehensive exception safety and user feedback
 * - **Cancellation Support**: Thread-safe cancellation for long-running operations
 * 
 * @note This class is designed to work with Qt 6.8.1+ and requires C++20 support.
 * @see ImageFilters class for image processing operations
 * @see HistoryManager class for undo/redo functionality
 * @see ImageIO class for file operations
 * @see Image class for image data structure
 * 
 * @example
 * @code
 * QApplication app(argc, argv);
 * ImageStudio window;
 * window.show();
 * return app.exec();
 * @endcode
 */
class ImageStudio : public QMainWindow
{
    Q_OBJECT

private:
    // File filter constants for Qt file dialogs
    static constexpr const char* IMAGE_FILTER = "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*)";
    static constexpr const char* SAVE_FILTER = "PNG Files (*.png);;JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)";

public:
    /**
     * @brief Constructs the main ImageStudio application window.
     * 
     * Initializes the Qt MainWindow with comprehensive UI setup, signal/slot connections,
     * drag-and-drop support, and all necessary components for image processing operations.
     * 
     * @param parent Parent widget (default: nullptr for main window)
     * 
     * @details The constructor performs:
     * - Qt Designer UI setup and styling
     * - Signal/slot connections for all buttons and menu actions
     * - Drag-and-drop event handling setup
     * - Progress bar and status bar initialization
     * - Image filters system initialization
     * - Timer setup for smooth window resizing
     * - Event filter installation for cropping functionality
     * 
     * @note This constructor sets up the complete application state and should be
     *       called only once per application instance.
     * @see ~ImageStudio() for cleanup operations
     */
    ImageStudio(QWidget *parent = nullptr) : QMainWindow(parent), hasImage(false)
    {
        ui.setupUi(this);
        
        setWindowTitle("Image Studio");
        setWindowIcon(QIcon("assets/icon.jpg"));
        setMinimumSize(600, 400);
        
        // Set up the image label styling
        ui.imageLabel->setAlignment(Qt::AlignCenter);
        ui.imageLabel->setMinimumSize(400, 300);
        ui.imageLabel->setScaledContents(false); // Disable automatic scaling to prevent stretching
        ui.imageLabel->setStyleSheet(
            "QLabel {"
            "  border: 2px solid #9e9e9e;"
            "  background-color: #f4f4f4;"
            "  color: #2b2b2b;"
            "  font-size: 14px;"
            "}"
        );
        ui.imageLabel->setText("No image loaded\nClick 'Load Image' or drag & drop an image here");
        
        // Connect signals
        connect(ui.loadButton, &QPushButton::clicked, this, &ImageStudio::loadImage);
        connect(ui.saveButton, &QPushButton::clicked, this, &ImageStudio::saveImage);
        connect(ui.unloadButton, &QPushButton::clicked, this, &ImageStudio::unloadImage);
        connect(ui.resetButton, &QPushButton::clicked, this, &ImageStudio::resetImage);
        connect(ui.undoButton, &QPushButton::clicked, this, &ImageStudio::undo);
        connect(ui.redoButton, &QPushButton::clicked, this, &ImageStudio::redo);
        connect(ui.grayscaleButton, &QPushButton::clicked, this, &ImageStudio::applyGrayscale);
        connect(ui.blackWhiteButton, &QPushButton::clicked, this, &ImageStudio::applyBlackAndWhite);
        connect(ui.invertButton, &QPushButton::clicked, this, &ImageStudio::applyInvert);
        connect(ui.mergeButton, &QPushButton::clicked, this, &ImageStudio::applyMerge);
        connect(ui.flipButton, &QPushButton::clicked, this, &ImageStudio::applyFlip);
        connect(ui.rotateButton, &QPushButton::clicked, this, &ImageStudio::applyRotate);
        connect(ui.darkLightButton, &QPushButton::clicked, this, &ImageStudio::applyDarkAndLight);
        connect(ui.frameButton, &QPushButton::clicked, this, &ImageStudio::applyFrame);
        connect(ui.cropButton, &QPushButton::clicked, this, &ImageStudio::startCropMode);
        connect(ui.edgesButton, &QPushButton::clicked, this, &ImageStudio::applyEdges);
        connect(ui.resizeButton, &QPushButton::clicked, this, &ImageStudio::applyResize);
        connect(ui.blurButton, &QPushButton::clicked, this, &ImageStudio::applyBlur);
        connect(ui.infraredButton, &QPushButton::clicked, this, &ImageStudio::applyInfrared);
        connect(ui.purpleButton, &QPushButton::clicked, this, &ImageStudio::applyPurpleFilter);
        connect(ui.tvFilterButton, &QPushButton::clicked, this, &ImageStudio::applyTVFilter);
        connect(ui.cancelButton, &QPushButton::clicked, this, &ImageStudio::cancelFilter);
        
        // Connect menu actions
        connect(ui.actionLoadImage, &QAction::triggered, this, &ImageStudio::loadImage);
        connect(ui.actionSaveImage, &QAction::triggered, this, &ImageStudio::saveImage);
        connect(ui.actionUnloadImage, &QAction::triggered, this, &ImageStudio::unloadImage);
        connect(ui.actionResetImage, &QAction::triggered, this, &ImageStudio::resetImage);
        connect(ui.actionUndo, &QAction::triggered, this, &ImageStudio::undo);
        connect(ui.actionRedo, &QAction::triggered, this, &ImageStudio::redo);
        connect(ui.actionExit, &QAction::triggered, this, &QWidget::close);
        connect(ui.actionGrayscale, &QAction::triggered, this, &ImageStudio::applyGrayscale);
        connect(ui.actionBlackWhite, &QAction::triggered, this, &ImageStudio::applyBlackAndWhite);
        connect(ui.actionInvert, &QAction::triggered, this, &ImageStudio::applyInvert);
        connect(ui.actionMerge, &QAction::triggered, this, &ImageStudio::applyMerge);
        connect(ui.actionFlip, &QAction::triggered, this, &ImageStudio::applyFlip);
        connect(ui.actionRotate, &QAction::triggered, this, &ImageStudio::applyRotate);
        connect(ui.actionCrop, &QAction::triggered, this, &ImageStudio::startCropMode);
        connect(ui.actionDarkLight, &QAction::triggered, this, &ImageStudio::applyDarkAndLight);
        connect(ui.actionFrame, &QAction::triggered, this, &ImageStudio::applyFrame);
        connect(ui.actionEdgeDetection, &QAction::triggered, this, &ImageStudio::applyEdges);
        connect(ui.actionResize, &QAction::triggered, this, &ImageStudio::applyResize);
        connect(ui.actionBlur, &QAction::triggered, this, &ImageStudio::applyBlur);
        connect(ui.actionInfrared, &QAction::triggered, this, &ImageStudio::applyInfrared);
        connect(ui.actionPurpleFilter, &QAction::triggered, this, &ImageStudio::applyPurpleFilter);
        connect(ui.actionTVFilter, &QAction::triggered, this, &ImageStudio::applyTVFilter);
        
        // Create status bar
        statusBar()->showMessage("Ready - Drag an image here or click 'Load Image'");
        
        // Initialize resize timer for smooth resizing
        resizeTimer = new QTimer(this);
        resizeTimer->setSingleShot(true);
        resizeTimer->setInterval(100); // 100ms delay
        connect(resizeTimer, &QTimer::timeout, this, &ImageStudio::updateImageDisplay);
        
        // Enable drag and drop
        setAcceptDrops(true);
        ui.imageLabel->setAcceptDrops(true);
        ui.scrollArea->setAcceptDrops(true);
        // Install event filter on imageLabel to capture mouse events for crop
        ui.imageLabel->installEventFilter(this);
        
        // Initialize image filters
        imageFilters = new ImageFilters(ui.progressBar, statusBar());
        
        // Initially disable filter buttons
        refreshButtons(false);
    }
    
    /**
     * @brief Destructor for the ImageStudio application window.
     * 
     * Performs cleanup operations to ensure proper resource management and
     * prevent memory leaks. This includes cleaning up dynamically allocated
     * resources and Qt objects.
     * 
     * @details The destructor:
     * - Deletes the ImageFilters instance
     * - Qt automatically handles cleanup of child widgets
     * - Ensures proper resource deallocation
     * 
     * @note This destructor is automatically called when the window is closed
     *       or the application exits.
     */
    ~ImageStudio() {
        delete imageFilters;
    }

private slots:
    /**
     * @brief Open file dialog and load an image into the application.
     * @details Enables image actions, initializes history and UI state.
     */
    void loadImage()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            "Load Image", QDir::homePath(), IMAGE_FILTER);
        if (!fileName.isEmpty()) {
            loadImageFromPath(fileName, false);
        }
    }
    
    /**
     * @brief Save the current image to a file.
     * 
     * Opens a file dialog to allow the user to choose a location and format
     * for saving the current image. Validates that an image is loaded before
     * attempting to save.
     * 
     * @details This method:
     * - Checks if an image is currently loaded
     * - Shows a warning if no image is available
     * - Opens a Qt file dialog for save location selection
     * - Handles file format selection (PNG, JPEG, BMP)
     * - Updates the unsaved changes flag on successful save
     * - Provides user feedback through status bar messages
     * 
     * @note The save operation uses the ImageIO class for Qt-integrated file operations.
     * @see saveImageWithDialog() for the actual save implementation
     * @see ImageIO::saveToFile() for file writing operations
     */
    void saveImage()
    {
        if (!hasImage) {
            QMessageBox::warning(this, "Warning", "No image to save!");
            return;
        }
        (void)saveImageWithDialog();
    }
    
    /**
     * @brief Unload the current image with optional save confirmation.
     * 
     * Provides a safe way to unload the current image with proper confirmation
     * dialogs and save options. Handles unsaved changes gracefully by offering
     * the user options to save, discard, or cancel the operation.
     * 
     * @details This method:
     * - Validates that an image is currently loaded
     * - Shows appropriate confirmation dialogs based on save state
     * - Offers save option if there are unsaved changes
     * - Handles user cancellation gracefully
     * - Clears all image data and resets UI state
     * - Resets undo/redo history and button states
     * 
     * @note This method provides comprehensive state management to ensure
     *       the application remains in a consistent state after unloading.
     * @see resetUiToNoImageState() for UI state reset
     * @see saveImageWithDialog() for save operations
     */
    void unloadImage()
    {
        if (!hasImage) {
            QMessageBox::warning(this, "Warning", "No image to unload!");
            return;
        }
        
        // Ask for confirmation with save option (only if there are unsaved changes)
        QMessageBox::StandardButton reply;
        if (hasUnsavedChanges) {
            reply = QMessageBox::question(this, "Unload Image",
                "The image has unsaved changes. Do you want to save before unloading?",
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        } else {
            reply = QMessageBox::question(this, "Unload Image",
                "Are you sure you want to unload the current image?",
                QMessageBox::Yes | QMessageBox::No);
            // Convert Yes/No to Save/Discard for consistent handling
            if (reply == QMessageBox::Yes) {
                reply = QMessageBox::Discard;
            } else {
                reply = QMessageBox::Cancel;
            }
        }
        
        if (reply == QMessageBox::Save) {
            if (!saveImageWithDialog()) {
                return; // Don't unload if save failed or cancelled
            }
        } else if (reply == QMessageBox::Cancel) {
            return; // User cancelled the unload operation
        }
        
        // Proceed with unload (either after successful save or user chose Discard)
        if (reply == QMessageBox::Save || reply == QMessageBox::Discard) {
            // Clear image data
            hasImage = false;
            currentFilePath.clear();
            hasUnsavedChanges = false;
            
            // Reset UI and history
            resetUiToNoImageState();
        }
    }
    
    /**
     * @brief Apply grayscale conversion to the current image.
     * 
     * Converts the current image to grayscale using average RGB values.
     * This operation supports progress tracking and cancellation.
     * 
     * @note This is a long-running operation that can be cancelled.
     * @see ImageFilters::applyGrayscale() for implementation details
     */
    void applyGrayscale()
    {
        if (!hasImage) return;
        runCancelableFilter([&]() {
            imageFilters->applyGrayscale(currentImage, preFilterImage, cancelRequested);
        });
    }
    
    /**
     * @brief Apply TV/CRT monitor simulation effect to the current image.
     * 
     * Creates a vintage TV/CRT monitor appearance with scan lines, color shifts,
     * and noise effects. This operation supports progress tracking and cancellation.
     * 
     * @note This is a long-running operation that can be cancelled.
     * @see ImageFilters::applyTVFilter() for implementation details
     */
    void applyTVFilter()
    {
        if (!hasImage) return;
        runCancelableFilter([&]() {
            imageFilters->applyTVFilter(currentImage, preFilterImage, cancelRequested);
        });
    }
    
    /**
     * @brief Reset the current image to its original state.
     * 
     * Restores the current image to the state it was in when first loaded,
     * discarding all modifications made since loading.
     * 
     * @note This operation does not affect the undo/redo history.
     * @see originalImage for the stored original image state
     */
    void resetImage()
    {
        if (!hasImage) return;
        
        currentImage = originalImage;
        updateImageDisplay();
        statusBar()->showMessage("Image reset to original");
    }
    
    /**
     * @brief Apply black and white conversion to the current image.
     * 
     * Converts the current image to pure black and white using threshold-based
     * processing. This operation supports progress tracking and cancellation.
     * 
     * @note This is a long-running operation that can be cancelled.
     * @see ImageFilters::applyBlackAndWhite() for implementation details
     */
    void applyBlackAndWhite()
    {
        if (!hasImage) return;
        runCancelableFilter([&]() {
            imageFilters->applyBlackAndWhite(currentImage, preFilterImage, cancelRequested);
        });
    }
    
    /**
     * @brief Apply color inversion to the current image.
     * 
     * Inverts all color values in the current image to create a negative effect.
     * This operation supports progress tracking and cancellation.
     * 
     * @note This is a long-running operation that can be cancelled.
     * @see ImageFilters::applyInvert() for implementation details
     */
    void applyInvert()
    {
        if (!hasImage) return;
        runCancelableFilter([&]() {
            imageFilters->applyInvert(currentImage, preFilterImage, cancelRequested);
        });
    }
    
    /**
     * @brief Merge the current image with another image.
     * 
     * Opens a file dialog to select a second image and merges it with the current
     * image by averaging their pixel values. The resulting image will have the
     * dimensions of the smaller input image.
     * 
     * @details This method:
     * - Opens a file dialog for image selection
     * - Loads the selected image using the Image class
     * - Merges the images by averaging pixel values
     * - Handles errors gracefully with user feedback
     * - Updates the display after successful merge
     * 
     * @note This is an immediate operation without progress tracking.
     * @see ImageFilters::applyMerge() for implementation details
     * @see ImageIO::loadFromFile() for image loading
     */
    void applyMerge()
    {
        if (!hasImage) return;
        
        QString fileName = QFileDialog::getOpenFileName(this,
            "Select Image to Merge", QDir::homePath(), IMAGE_FILTER);
        
        if (!fileName.isEmpty()) {
            try {
                saveStateForUndo();
                
                Image mergeImage;
                mergeImage.loadNewImage(fileName.toStdString());
                
                imageFilters->applyMerge(currentImage, mergeImage);
                updateImageDisplay();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Merge failed: %1").arg(e.what()));
            }
        }
    }
    
    void applyFlip()
    {
        if (!hasImage) return;
        
        QStringList options;
        options << "Horizontal" << "Vertical";
        
        QString choice = getInputFromList("Flip Image", "Choose flip direction:", options);
        
        if (!choice.isEmpty()) {
            saveStateForUndo();
            
            try {
                imageFilters->applyFlip(currentImage, choice);
                updateImageDisplay();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
            }
        }
    }
    
    void applyRotate()
    {
        if (!hasImage) return;
        
        QStringList options;
        options << "90°" << "180°" << "270°";
        
        QString choice = getInputFromList("Rotate Image", "Choose rotation angle:", options);
        
        if (!choice.isEmpty()) {
            saveStateForUndo();
            
            try {
                imageFilters->applyRotate(currentImage, choice);
                updateImageDisplay();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
            }
        }
    }
    
    void applyDarkAndLight()
    {
        if (!hasImage) return;
        
        // Ask user for dark or light using GUI instead of std::cin
        QStringList options; options << "dark" << "light";
        QString choice = getInputFromList("Dark or Light", "Choose:", options);
        if (choice.isEmpty()) return;
        
        runSimpleFilter([&]() {
            imageFilters->applyDarkAndLight(currentImage, choice);
        });
    }
    
    void applyFrame()
    {
        if (!hasImage) return;
        
        QStringList options;
        options << "Simple Frame" << "Decorated Frame";
        
        QString choice = getInputFromList("Add Frame", "Choose frame type:", options);
        
        if (!choice.isEmpty()) {
            runSimpleFilter([&]() {
                imageFilters->applyFrame(currentImage, choice);
            });
        }
    }
    
    void applyEdges()
    {
        if (!hasImage) return;
        runSimpleFilter([&]() {
            imageFilters->applyEdges(currentImage);
        });
    }
    
    void applyResize()
    {
        if (!hasImage) return;
        
        bool ok1, ok2;
        int width = QInputDialog::getInt(this, "Resize Image", "Enter new width:", 
            currentImage.width, 1, 10000, 1, &ok1);
        int height = QInputDialog::getInt(this, "Resize Image", "Enter new height:", 
            currentImage.height, 1, 10000, 1, &ok2);
        
        if (ok1 && ok2) {
            runSimpleFilter([&]() {
                imageFilters->applyResize(currentImage, width, height);
            });
        }
    }
    
    void applyBlur()
    {
        if (!hasImage) return;
        runCancelableFilter([&]() {
            imageFilters->applyBlur(currentImage, preFilterImage, cancelRequested);
        });
    }
    
    /**
     * @brief Apply the Infrared effect with progress and cancellation support.
     */
    void applyInfrared()
    {
        if (!hasImage) return;
        runCancelableFilter([&]() {
            imageFilters->applyInfrared(currentImage, preFilterImage, cancelRequested);
        });
    }
    
    /**
     * @brief Apply the Purple color filter with progress and cancellation.
     */
    void applyPurpleFilter()
    {
        if (!hasImage) return;
        runCancelableFilter([&]() {
            imageFilters->applyPurpleFilter(currentImage, preFilterImage, cancelRequested);
        });
    }
    
    /**
     * @brief Enter interactive crop mode using a rubber-band selection.
     */
    void startCropMode()
    {
        if (!hasImage) return;
        if (!rubberBand) {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, ui.imageLabel);
        }
        cropping = true;
        statusBar()->showMessage("Crop mode: drag to select area, release to crop");
    }
    
    /**
     * @brief Undo the last image modification.
     */
    void undo()
    {
        if (!hasImage) return;
        if (!history.undo(currentImage)) return;
        
        updateImageDisplay();
        updateUndoRedoButtons();
        statusBar()->showMessage("Undo applied");
    }
    
    /**
     * @brief Redo the last undone image modification.
     */
    void redo()
    {
        if (!hasImage) return;
        if (!history.redo(currentImage)) return;
        
        updateImageDisplay();
        updateUndoRedoButtons();
        statusBar()->showMessage("Redo applied");
    }
    
    /**
     * @brief Request cancellation for a long-running filter.
     */
    void cancelFilter()
    {
        cancelRequested = true;
        statusBar()->showMessage("Cancelling filter...");
    }

private:
    Ui::MainWindow ui;
    
    /**
     * @brief Push current image state onto the undo stack and mark unsaved changes.
     */
    void saveStateForUndo()
    {
        if (!hasImage) return;
        // Save current state to history
        history.pushUndo(currentImage);
        // Mark as having unsaved changes
        hasUnsavedChanges = true;
        
        updateUndoRedoButtons();
    }
    
    /**
     * @brief Refresh enabled state of Undo/Redo buttons based on history.
     */
    void updateUndoRedoButtons()
    {
        ui.undoButton->setEnabled(history.canUndo());
        ui.redoButton->setEnabled(history.canRedo());
    }

    /**
     * @brief Refresh the enabled state of all UI buttons based on image availability.
     * 
     * Enables or disables all image processing buttons and controls based on whether
     * an image is currently loaded. This ensures the UI remains in a consistent state
     * and prevents operations on non-existent images.
     * 
     * @param isActive True to enable all buttons, false to disable them
     * 
     * @details This method controls the state of:
     * - File operations (save, unload, reset)
     * - History operations (undo, redo)
     * - All image processing filters
     * - Interactive tools (crop)
     * 
     * @note This method should be called whenever the image state changes
     *       to maintain UI consistency.
     */
    void refreshButtons(const bool isActive) {
        ui.saveButton->setEnabled(isActive);
        ui.unloadButton->setEnabled(isActive);
        ui.resetButton->setEnabled(isActive);
        ui.undoButton->setEnabled(isActive);
        ui.redoButton->setEnabled(isActive);
        ui.grayscaleButton->setEnabled(isActive);
        ui.blackWhiteButton->setEnabled(isActive);
        ui.invertButton->setEnabled(isActive);
        ui.mergeButton->setEnabled(isActive);
        ui.flipButton->setEnabled(isActive);
        ui.rotateButton->setEnabled(isActive);
        ui.cropButton->setEnabled(isActive);
        ui.darkLightButton->setEnabled(isActive);
        ui.frameButton->setEnabled(isActive);
        ui.edgesButton->setEnabled(isActive);
        ui.resizeButton->setEnabled(isActive);
        ui.blurButton->setEnabled(isActive);
        ui.infraredButton->setEnabled(isActive);
        ui.purpleButton->setEnabled(isActive);
        ui.tvFilterButton->setEnabled(isActive);
    }

    /**
     * @brief Compute and enforce a minimum window size to avoid scrollbars for the current image.
     */
    void updateMinimumWindowSize()
    {
        // Keep a stable, small base minimum to allow shrinking after expansion.
        setMinimumSize(600, 400);
    }
    
protected:
    /**
     * @brief Intercept window close to prompt for saving unsaved changes.
     */
    void closeEvent(QCloseEvent *event) override
    {
        if (hasImage && hasUnsavedChanges) {
            QMessageBox::StandardButton reply = QMessageBox::question(this, "Save Changes",
                "The image has unsaved changes. Do you want to save before exiting?",
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            
            if (reply == QMessageBox::Save) {
                if (saveImageWithDialog()) {
                    event->accept();
                } else {
                    event->ignore();
                    return;
                }
            } else if (reply == QMessageBox::Discard) {
                event->accept(); // Allow the application to close without saving
            } else {
                event->ignore(); // User cancelled the exit
                return;
            }
        }
        
        QMainWindow::closeEvent(event);
    }
    
    /**
     * @brief Throttle image re-layout on window resize using a timer.
     */
    void resizeEvent(QResizeEvent *event) override
    {
        QMainWindow::resizeEvent(event);
        // Use timer to avoid too many updates during rapid resizing
        if (hasImage) {
            resizeTimer->start();
        }
    }
    
    /**
     * @brief Accept drag if it contains a supported image file.
     */
    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->mimeData()->hasUrls()) {
            QList<QUrl> urls = event->mimeData()->urls();
            if (!urls.isEmpty()) {
                QString fileName = urls.first().toLocalFile();
                QFileInfo fileInfo(fileName);
                QString suffix = fileInfo.suffix().toLower();
                
                // Check if it's a supported image format
                if (suffix == "png" || suffix == "jpg" || suffix == "jpeg" || 
                    suffix == "bmp" || suffix == "tga") {
                    event->acceptProposedAction();
                    statusBar()->showMessage("Drop image to load: " + fileInfo.fileName());
                    return;
                }
            }
        }
        event->ignore();
    }
    
    /**
     * @brief Allow drag move within the window for image files.
     */
    void dragMoveEvent(QDragMoveEvent *event) override
    {
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }
    
    /**
     * @brief Restore status message when a drag leaves the window.
     */
    void dragLeaveEvent(QDragLeaveEvent *event) override
    {
        Q_UNUSED(event)
        statusBar()->showMessage(hasImage ? "Ready" : "Ready - Drag an image here or click 'Load Image'");
    }
    
    /**
     * @brief Load an image when a supported file is dropped onto the window.
     */
    void dropEvent(QDropEvent *event) override
    {
        if (event->mimeData()->hasUrls()) {
            QList<QUrl> urls = event->mimeData()->urls();
            if (!urls.isEmpty()) {
                QString fileName = urls.first().toLocalFile();
                QFileInfo fileInfo(fileName);
                QString suffix = fileInfo.suffix().toLower();
                
                // Check if it's a supported image format
                if (suffix == "png" || suffix == "jpg" || suffix == "jpeg" || 
                    suffix == "bmp" || suffix == "tga") {
                    
                    event->acceptProposedAction();
                    
                    // Load the dropped image
                    loadImageFromPath(fileName, true);
                    return;
                }
            }
        }
        event->ignore();
        statusBar()->showMessage("Unsupported file format. Please drop a PNG, JPG, JPEG, BMP, or TGA file.");
    }
    
    bool eventFilter(QObject *watched, QEvent *event) override
    {
        if (watched == ui.imageLabel && cropping && hasImage) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *me = static_cast<QMouseEvent*>(event);
                cropOrigin = me->pos();
                if (!rubberBand) rubberBand = new QRubberBand(QRubberBand::Rectangle, ui.imageLabel);
                rubberBand->setGeometry(QRect(cropOrigin, QSize()));
                rubberBand->show();
                return true;
            } else if (event->type() == QEvent::MouseMove) {
                QMouseEvent *me = static_cast<QMouseEvent*>(event);
                if (rubberBand) rubberBand->setGeometry(QRect(cropOrigin, me->pos()).normalized());
                return true;
            } else if (event->type() == QEvent::MouseButtonRelease) {
                QMouseEvent *me = static_cast<QMouseEvent*>(event);
                if (rubberBand) {
                    QRect selection = QRect(cropOrigin, me->pos()).normalized();
                    performCropFromSelection(selection);
                    rubberBand->hide();
                }
                cropping = false;
                statusBar()->showMessage("Cropped");
                return true;
            }
        }
        return QMainWindow::eventFilter(watched, event);
    }
    /**
     * @brief Update the image display with smart resizing and aspect ratio preservation.
     * 
     * Converts the current image to a QPixmap and displays it in the image label with
     * smart resizing that maintains aspect ratio and fits within the available space.
     * Updates the status bar with detailed image information.
     * 
     * @details This method:
     * - Converts the Image object to QPixmap for display
     * - Calculates optimal display size maintaining aspect ratio
     * - Scales the image with smooth transformation
     * - Updates the image label with the scaled pixmap
     * - Resizes the label to match the scaled image
     * - Updates the minimum window size to prevent scrollbars
     * - Shows detailed image information in the status bar
     * 
     * @note This method is called whenever the image changes and should be
     *       called from the main thread for UI updates.
     * @see buildQImage() for Image to QImage conversion
     * @see calculateAspectRatioSize() for size calculation
     */
    void updateImageDisplay()
    {
        if (!hasImage) return;
        
        QPixmap pixmap = QPixmap::fromImage(buildQImage(currentImage));
        
        // Get the available space in the scroll area
        QSize scrollAreaSize = ui.scrollArea->size();
        QSize availableSize(scrollAreaSize.width() - 20, scrollAreaSize.height() - 20); // Account for scrollbars
        
        // Calculate the target size maintaining aspect ratio
        QSize targetSize = calculateAspectRatioSize(QSize(currentImage.width, currentImage.height), availableSize);
         
         // Scale the image with smooth transformation
         QPixmap scaledPixmap = pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
         
         // Set the pixmap and ensure the label size matches the scaled image
         ui.imageLabel->setPixmap(scaledPixmap);
         ui.imageLabel->setText("");
         ui.imageLabel->setScaledContents(false); // Disable automatic scaling
         ui.imageLabel->resize(scaledPixmap.size()); // Resize label to match pixmap
         
         // Calculate minimum window size to prevent scrollbars
         updateMinimumWindowSize();
        
        // Update status bar with image info
        double imageAspectRatio = static_cast<double>(currentImage.width) / currentImage.height;
        statusBar()->showMessage(QString("Image: %1x%2 | Display: %3x%4 | Aspect Ratio: %5")
            .arg(currentImage.width)
            .arg(currentImage.height)
            .arg(scaledPixmap.width())
            .arg(scaledPixmap.height())
            .arg(QString::number(imageAspectRatio, 'f', 2)));
    }
    
    /**
     * @brief Crop the current image using a selection rectangle relative to the label.
     * @param selectionOnLabel The selection bounds in label coordinates.
     */
    void performCropFromSelection(const QRect &selectionOnLabel)
    {
        if (!hasImage) return;
        if (selectionOnLabel.width() <= 1 || selectionOnLabel.height() <= 1) return;
        
        // Determine the scale used to draw the pixmap on the label
        QSize scrollAreaSize = ui.scrollArea->size();
        QSize availableSize(scrollAreaSize.width() - 20, scrollAreaSize.height() - 20);
        
        // Calculate the target size maintaining aspect ratio
        QSize targetSize = calculateAspectRatioSize(QSize(currentImage.width, currentImage.height), availableSize);
        
        // Build the current displayed pixmap to get its actual size
        QPixmap pixmap = QPixmap::fromImage(buildQImage(currentImage));
        QPixmap scaledPixmap = pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        
        // The image is centered inside imageLabel.
        QSize labelSize = ui.imageLabel->size();
        int offsetX = (labelSize.width() - scaledPixmap.width()) / 2;
        int offsetY = (labelSize.height() - scaledPixmap.height()) / 2;
        
        // Intersect selection with the drawn image rect
        QRect drawnRect(offsetX, offsetY, scaledPixmap.width(), scaledPixmap.height());
        QRect selection = selectionOnLabel.intersected(drawnRect);
        if (selection.isEmpty()) return;
        
        // Map from label coords to image pixel coords
        double scaleX = static_cast<double>(currentImage.width) / scaledPixmap.width();
        double scaleY = static_cast<double>(currentImage.height) / scaledPixmap.height();
        
        int x0 = std::max(0, static_cast<int>((selection.left() - offsetX) * scaleX));
        int y0 = std::max(0, static_cast<int>((selection.top() - offsetY) * scaleY));
        int x1 = std::min((int)currentImage.width, static_cast<int>((selection.right() - offsetX + 1) * scaleX));
        int y1 = std::min((int)currentImage.height, static_cast<int>((selection.bottom() - offsetY + 1) * scaleY));
        
        int newW = std::max(1, x1 - x0);
        int newH = std::max(1, y1 - y0);
        
        if (newW <= 1 || newH <= 1) return;
        
        saveStateForUndo();
        Image result(newW, newH);
        for (int y = 0; y < newH; y++) {
            for (int x = 0; x < newW; x++) {
                for (int c = 0; c < 3; c++) {
                    result.setPixel(x, y, c, currentImage(x0 + x, y0 + y, c));
                }
            }
        }
        currentImage = result;
        updateImageDisplay();
    }
    
    Image originalImage;
    Image currentImage;
    bool hasImage;
    QString currentFilePath;
    
    // Cancel mechanism
    std::atomic<bool> cancelRequested{false};
    Image preFilterImage; // Store image state before filter for cancellation
    
    // Undo/Redo system
    HistoryManager history{20};
    
    // Save state tracking
    bool hasUnsavedChanges = false;
    
    // Resize handling
    QTimer *resizeTimer;
    
    // Crop handling
    bool cropping = false;
    QRubberBand *rubberBand = nullptr;
    QPoint cropOrigin;
    
    // Image filters
    ImageFilters* imageFilters;

    // Helpers
    bool saveImageWithDialog()
    {
        QString fileName = QFileDialog::getSaveFileName(this,
            "Save Image", QDir::homePath(), SAVE_FILTER);
        if (fileName.isEmpty()) return false;
        try {
            ImageIO::saveToFile(currentImage, fileName);
            hasUnsavedChanges = false; // Mark as saved
            statusBar()->showMessage(QString("Saved: %1").arg(QFileInfo(fileName).fileName()));
            return true;
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Failed to save image: %1").arg(e.what()));
            return false;
        }
    }

    void resetUiToNoImageState()
    {
        // Clear undo/redo history
        history.clear();
        updateUndoRedoButtons();
        // Reset image label
        ui.imageLabel->clear();
        ui.imageLabel->setText("No image loaded\nClick 'Load Image' or drag & drop an image here");
        // Reset minimum window size and disable buttons
        updateMinimumWindowSize();
        refreshButtons(false);
        // Update status bar
        statusBar()->showMessage("Image unloaded - Ready to load a new image");
    }

    void finalizeSuccessfulLoad(const QString &filePath, bool viaDrop)
    {
        currentFilePath = filePath;
        hasUnsavedChanges = false;
        updateImageDisplay();
        updateMinimumWindowSize();
        refreshButtons(true);
        history.clear();
        updateUndoRedoButtons();
        const QString baseName = QFileInfo(filePath).fileName();
        statusBar()->showMessage(viaDrop ? QString("Loaded via drag & drop: %1").arg(baseName)
                                         : QString("Loaded: %1").arg(baseName));
    }

    void loadImageFromPath(const QString &filePath, bool viaDrop)
    {
        try {
            originalImage = ImageIO::loadFromFile(filePath);
            currentImage = originalImage;
            hasImage = true;
            finalizeSuccessfulLoad(filePath, viaDrop);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Failed to load image: %1").arg(e.what()));
            statusBar()->showMessage("Failed to load image");
        }
    }

    QString getInputFromList(const QString &title, const QString &label, const QStringList &options)
    {
        bool ok;
        return QInputDialog::getItem(this, title, label, options, 0, false, &ok);
    }

    QSize calculateAspectRatioSize(const QSize &imageSize, const QSize &availableSize)
    {
        double imageAspectRatio = static_cast<double>(imageSize.width()) / imageSize.height();
        double availableAspectRatio = static_cast<double>(availableSize.width()) / availableSize.height();
        
        QSize targetSize;
        if (imageAspectRatio > availableAspectRatio) {
            // Image is wider than available space - fit to width
            targetSize.setWidth(availableSize.width());
            targetSize.setHeight(static_cast<int>(availableSize.width() / imageAspectRatio));
        } else {
            // Image is taller than available space - fit to height
            targetSize.setHeight(availableSize.height());
            targetSize.setWidth(static_cast<int>(availableSize.height() * imageAspectRatio));
        }
        
        // Ensure we don't exceed the original image size (don't upscale)
        if (targetSize.width() > imageSize.width() || targetSize.height() > imageSize.height()) {
            targetSize = imageSize;
        }
        
        return targetSize;
    }
    void runCancelableFilter(const std::function<void()> &filterCall)
    {
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        ui.cancelButton->setVisible(true);
        try {
            filterCall();
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        ui.cancelButton->setVisible(false);
    }

    void runSimpleFilter(const std::function<void()> &filterCall)
    {
        saveStateForUndo();
        try {
            filterCall();
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
    }

    /**
     * @brief Convert an Image object to a QImage for Qt display.
     * 
     * Converts the internal Image data structure to a QImage that can be
     * displayed in Qt widgets. This method handles the conversion from
     * the custom Image format to Qt's standard image format.
     * 
     * @param img Reference to the Image object to convert
     * @return QImage object ready for Qt display
     * 
     * @details This method:
     * - Creates a QImage with RGB888 format
     * - Iterates through all pixels in the image
     * - Converts RGB values from the Image format to Qt format
     * - Returns a QImage ready for display or further processing
     * 
     * @note This method performs a complete copy of the image data and
     *       should be used efficiently for large images.
     * @see QImage for Qt image format details
     * @see Image class for the source image format
     */
    QImage buildQImage(const Image &img)
    {
        QImage qimg(img.width, img.height, QImage::Format_RGB888);
        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                int r = img(x, y, 0);
                int g = img(x, y, 1);
                int b = img(x, y, 2);
                qimg.setPixel(x, y, qRgb(r, g, b));
            }
        }
        return qimg;
    }
};

/**
 * @brief Main entry point for the Image Studio application.
 * 
 * Initializes the Qt application, creates the main window, and starts the event loop.
 * This function sets up the complete application environment and handles the
 * application lifecycle from startup to shutdown.
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line argument strings
 * @return Application exit code (0 for success, non-zero for error)
 * 
 * @details The main function:
 * - Creates and configures the Qt application instance
 * - Sets the application window icon
 * - Creates the main ImageStudio window
 * - Shows the window and starts the event loop
 * - Handles application shutdown gracefully
 * 
 * @note This function follows Qt's standard application structure and should
 *       be called only once per application instance.
 * @see QApplication for Qt application management
 * @see ImageStudio for the main application window
 * 
 * @example
 * @code
 * int main(int argc, char *argv[]) {
 *     QApplication app(argc, argv);
 *     ImageStudio window;
 *     window.show();
 *     return app.exec();
 * }
 * @endcode
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("assets/icon.jpg"));
    
    ImageStudio window;
    window.show();
    
    return app.exec();
}

#include "image_studio.moc"