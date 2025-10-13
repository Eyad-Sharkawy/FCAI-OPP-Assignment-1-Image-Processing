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
#include <QHBoxLayout>
#include <QCloseEvent>
#include <cmath>
#include <algorithm>
#include <stack>
#include <random>
#include <chrono>
#include <atomic>
#include "../core/image/Image_Class.h"
#include "../core/filters/ImageFilters.h"
#include "ui_mainwindow.h"
#include "../core/history/HistoryManager.h"
#include "../core/io/ImageIO.h"

/**
 * @class SimpleImageApp
 * @brief Main Qt window for Image Studio.
 *
 * Owns the UI, wires signals/slots, manages current/original images,
 * delegates image processing to ImageFilters, and coordinates history,
 * progress, cancellation, drag-and-drop, and cropping interactions.
 */
class SimpleImageApp : public QMainWindow
{
    Q_OBJECT

public:
SimpleImageApp(QWidget *parent = nullptr) : QMainWindow(parent), hasImage(false)
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
        connect(ui.loadButton, &QPushButton::clicked, this, &SimpleImageApp::loadImage);
        connect(ui.saveButton, &QPushButton::clicked, this, &SimpleImageApp::saveImage);
        connect(ui.unloadButton, &QPushButton::clicked, this, &SimpleImageApp::unloadImage);
        connect(ui.resetButton, &QPushButton::clicked, this, &SimpleImageApp::resetImage);
        connect(ui.undoButton, &QPushButton::clicked, this, &SimpleImageApp::undo);
        connect(ui.redoButton, &QPushButton::clicked, this, &SimpleImageApp::redo);
        connect(ui.grayscaleButton, &QPushButton::clicked, this, &SimpleImageApp::applyGrayscale);
        connect(ui.blackWhiteButton, &QPushButton::clicked, this, &SimpleImageApp::applyBlackAndWhite);
        connect(ui.invertButton, &QPushButton::clicked, this, &SimpleImageApp::applyInvert);
        connect(ui.mergeButton, &QPushButton::clicked, this, &SimpleImageApp::applyMerge);
        connect(ui.flipButton, &QPushButton::clicked, this, &SimpleImageApp::applyFlip);
        connect(ui.rotateButton, &QPushButton::clicked, this, &SimpleImageApp::applyRotate);
        connect(ui.darkLightButton, &QPushButton::clicked, this, &SimpleImageApp::applyDarkAndLight);
        connect(ui.frameButton, &QPushButton::clicked, this, &SimpleImageApp::applyFrame);
        connect(ui.cropButton, &QPushButton::clicked, this, &SimpleImageApp::startCropMode);
        connect(ui.edgesButton, &QPushButton::clicked, this, &SimpleImageApp::applyEdges);
        connect(ui.resizeButton, &QPushButton::clicked, this, &SimpleImageApp::applyResize);
        connect(ui.blurButton, &QPushButton::clicked, this, &SimpleImageApp::applyBlur);
        connect(ui.infraredButton, &QPushButton::clicked, this, &SimpleImageApp::applyInfrared);
        connect(ui.purpleButton, &QPushButton::clicked, this, &SimpleImageApp::applyPurpleFilter);
        connect(ui.tvFilterButton, &QPushButton::clicked, this, &SimpleImageApp::applyTVFilter);
        connect(ui.cancelButton, &QPushButton::clicked, this, &SimpleImageApp::cancelFilter);
        
        // Connect menu actions
        connect(ui.actionLoadImage, &QAction::triggered, this, &SimpleImageApp::loadImage);
        connect(ui.actionSaveImage, &QAction::triggered, this, &SimpleImageApp::saveImage);
        connect(ui.actionUnloadImage, &QAction::triggered, this, &SimpleImageApp::unloadImage);
        connect(ui.actionResetImage, &QAction::triggered, this, &SimpleImageApp::resetImage);
        connect(ui.actionUndo, &QAction::triggered, this, &SimpleImageApp::undo);
        connect(ui.actionRedo, &QAction::triggered, this, &SimpleImageApp::redo);
        connect(ui.actionExit, &QAction::triggered, this, &QWidget::close);
        connect(ui.actionGrayscale, &QAction::triggered, this, &SimpleImageApp::applyGrayscale);
        connect(ui.actionBlackWhite, &QAction::triggered, this, &SimpleImageApp::applyBlackAndWhite);
        connect(ui.actionInvert, &QAction::triggered, this, &SimpleImageApp::applyInvert);
        connect(ui.actionMerge, &QAction::triggered, this, &SimpleImageApp::applyMerge);
        connect(ui.actionFlip, &QAction::triggered, this, &SimpleImageApp::applyFlip);
        connect(ui.actionRotate, &QAction::triggered, this, &SimpleImageApp::applyRotate);
        connect(ui.actionCrop, &QAction::triggered, this, &SimpleImageApp::startCropMode);
        connect(ui.actionDarkLight, &QAction::triggered, this, &SimpleImageApp::applyDarkAndLight);
        connect(ui.actionFrame, &QAction::triggered, this, &SimpleImageApp::applyFrame);
        connect(ui.actionEdgeDetection, &QAction::triggered, this, &SimpleImageApp::applyEdges);
        connect(ui.actionResize, &QAction::triggered, this, &SimpleImageApp::applyResize);
        connect(ui.actionBlur, &QAction::triggered, this, &SimpleImageApp::applyBlur);
        connect(ui.actionInfrared, &QAction::triggered, this, &SimpleImageApp::applyInfrared);
        connect(ui.actionPurpleFilter, &QAction::triggered, this, &SimpleImageApp::applyPurpleFilter);
        connect(ui.actionTVFilter, &QAction::triggered, this, &SimpleImageApp::applyTVFilter);
        
        // Create status bar
        statusBar()->showMessage("Ready - Drag an image here or click 'Load Image'");
        
        // Initialize resize timer for smooth resizing
        resizeTimer = new QTimer(this);
        resizeTimer->setSingleShot(true);
        resizeTimer->setInterval(100); // 100ms delay
        connect(resizeTimer, &QTimer::timeout, this, &SimpleImageApp::updateImageDisplay);
        
        // Enable drag and drop
        setAcceptDrops(true);
        ui.imageLabel->setAcceptDrops(true);
        ui.scrollArea->setAcceptDrops(true);
        // Install event filter on imageLabel to capture mouse events for crop
        ui.imageLabel->installEventFilter(this);
        
        // Initialize image filters
        imageFilters = new ImageFilters(ui.progressBar, statusBar());
        
        // Initially disable filter buttons
        ui.saveButton->setEnabled(false);
        ui.unloadButton->setEnabled(false);
        ui.resetButton->setEnabled(false);
        ui.undoButton->setEnabled(false);
        ui.redoButton->setEnabled(false);
        ui.grayscaleButton->setEnabled(false);
        ui.blackWhiteButton->setEnabled(false);
        ui.invertButton->setEnabled(false);
        ui.mergeButton->setEnabled(false);
        ui.flipButton->setEnabled(false);
        ui.rotateButton->setEnabled(false);
        ui.cropButton->setEnabled(false);
        ui.darkLightButton->setEnabled(false);
        ui.frameButton->setEnabled(false);
        ui.edgesButton->setEnabled(false);
        ui.resizeButton->setEnabled(false);
        ui.blurButton->setEnabled(false);
        ui.infraredButton->setEnabled(false);
        ui.purpleButton->setEnabled(false);
        ui.tvFilterButton->setEnabled(false);
    }
    
    // Destructor to clean up
    ~SimpleImageApp() {
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
            "Load Image", QDir::homePath(),
            "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*)");
        
        if (!fileName.isEmpty()) {
            try {
                originalImage = ImageIO::loadFromFile(fileName);
                currentImage = originalImage;
                hasImage = true;
                currentFilePath = fileName;
                hasUnsavedChanges = false; // New image is considered "saved"
                
                updateImageDisplay();
                updateMinimumWindowSize();
                ui.saveButton->setEnabled(true);
                ui.unloadButton->setEnabled(true);
                ui.resetButton->setEnabled(true);
                ui.grayscaleButton->setEnabled(true);
                ui.blackWhiteButton->setEnabled(true);
                ui.invertButton->setEnabled(true);
                ui.mergeButton->setEnabled(true);
                ui.flipButton->setEnabled(true);
                ui.rotateButton->setEnabled(true);
                ui.cropButton->setEnabled(true);
                ui.darkLightButton->setEnabled(true);
                ui.frameButton->setEnabled(true);
                ui.edgesButton->setEnabled(true);
                ui.resizeButton->setEnabled(true);
                ui.blurButton->setEnabled(true);
                ui.infraredButton->setEnabled(true);
                ui.purpleButton->setEnabled(true);
                ui.tvFilterButton->setEnabled(true);
                
                // Clear undo/redo history when loading new image
                history.clear();
                updateUndoRedoButtons();
                
                statusBar()->showMessage(QString("Loaded: %1").arg(QFileInfo(fileName).fileName()));
                
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", 
                    QString("Failed to load image: %1").arg(e.what()));
            }
        }
    }
    
    void saveImage()
    {
        if (!hasImage) {
            QMessageBox::warning(this, "Warning", "No image to save!");
            return;
        }
        
        QString fileName = QFileDialog::getSaveFileName(this,
            "Save Image", QDir::homePath(),
            "PNG Files (*.png);;JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)");
        
        if (!fileName.isEmpty()) {
            try {
                ImageIO::saveToFile(currentImage, fileName);
                        hasUnsavedChanges = false; // Mark as saved
                statusBar()->showMessage(QString("Saved: %1").arg(QFileInfo(fileName).fileName()));
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", 
                    QString("Failed to save image: %1").arg(e.what()));
            }
                }
    }
    
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
            // Try to save the image first
            QString fileName = QFileDialog::getSaveFileName(this,
                "Save Image", QDir::homePath(),
                "PNG Files (*.png);;JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)");
            
            if (!fileName.isEmpty()) {
                try {
                    ImageIO::saveToFile(currentImage, fileName);
                    hasUnsavedChanges = false; // Mark as saved
                    statusBar()->showMessage(QString("Saved: %1").arg(QFileInfo(fileName).fileName()));
                } catch (const std::exception& e) {
                    QMessageBox::critical(this, "Error", 
                        QString("Failed to save image: %1").arg(e.what()));
                    return; // Don't unload if save failed
                }
            } else {
                return; // User cancelled save dialog, don't unload
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
            
            // Clear undo/redo history
            history.clear();
            
            // Reset image label
            ui.imageLabel->clear();
            ui.imageLabel->setText("No image loaded\nClick 'Load Image' or drag & drop an image here");
            
            // Reset minimum window size
            updateMinimumWindowSize();
            
            // Disable all filter buttons
            ui.saveButton->setEnabled(false);
            ui.unloadButton->setEnabled(false);
            ui.resetButton->setEnabled(false);
            ui.undoButton->setEnabled(false);
            ui.redoButton->setEnabled(false);
            ui.grayscaleButton->setEnabled(false);
            ui.blackWhiteButton->setEnabled(false);
            ui.invertButton->setEnabled(false);
            ui.mergeButton->setEnabled(false);
            ui.flipButton->setEnabled(false);
            ui.rotateButton->setEnabled(false);
            ui.cropButton->setEnabled(false);
            ui.darkLightButton->setEnabled(false);
            ui.frameButton->setEnabled(false);
            ui.edgesButton->setEnabled(false);
            ui.resizeButton->setEnabled(false);
            ui.blurButton->setEnabled(false);
            ui.infraredButton->setEnabled(false);
            ui.purpleButton->setEnabled(false);
            ui.tvFilterButton->setEnabled(false);
            
            // Update status bar
            statusBar()->showMessage("Image unloaded - Ready to load a new image");
        }
    }
    
    void applyGrayscale()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.cancelButton->setVisible(true);
        
        try {
            imageFilters->applyGrayscale(currentImage, preFilterImage, cancelRequested);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.cancelButton->setVisible(false);
    }
    
    void applyTVFilter()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.cancelButton->setVisible(true);
        
        try {
            imageFilters->applyTVFilter(currentImage, preFilterImage, cancelRequested);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.cancelButton->setVisible(false);
    }
    
    void resetImage()
    {
        if (!hasImage) return;
        
        currentImage = originalImage;
        updateImageDisplay();
        statusBar()->showMessage("Image reset to original");
    }
    
    void applyBlackAndWhite()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.cancelButton->setVisible(true);
        
        try {
            imageFilters->applyBlackAndWhite(currentImage, preFilterImage, cancelRequested);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.cancelButton->setVisible(false);
    }
    
    void applyInvert()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.cancelButton->setVisible(true);
        
        try {
            imageFilters->applyInvert(currentImage, preFilterImage, cancelRequested);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.cancelButton->setVisible(false);
    }
    
    void applyMerge()
    {
        if (!hasImage) return;
        
        QString fileName = QFileDialog::getOpenFileName(this,
            "Select Image to Merge", QDir::homePath(),
            "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*)");
        
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
        
        bool ok;
        QString choice = QInputDialog::getItem(this, "Flip Image", 
            "Choose flip direction:", options, 0, false, &ok);
        
        if (ok) {
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
        
        bool ok;
        QString choice = QInputDialog::getItem(this, "Rotate Image", 
            "Choose rotation angle:", options, 0, false, &ok);
        
        if (ok) {
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
        bool ok = false;
        QString choice = QInputDialog::getItem(this, "Dark or Light", "Choose:", options, 0, false, &ok);
        if (!ok) return;
        
        saveStateForUndo();
        
        try {
            imageFilters->applyDarkAndLight(currentImage, choice);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
    }
    
    void applyFrame()
    {
        if (!hasImage) return;
        
        QStringList options;
        options << "Simple Frame" << "Decorated Frame";
        
        bool ok;
        QString choice = QInputDialog::getItem(this, "Add Frame", 
            "Choose frame type:", options, 0, false, &ok);
        
        if (ok) {
            saveStateForUndo();
            
            try {
                imageFilters->applyFrame(currentImage, choice);
                updateImageDisplay();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
            }
        }
    }
    
    void applyEdges()
    {
        if (!hasImage) return;
        
        saveStateForUndo();
        
        try {
            imageFilters->applyEdges(currentImage);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
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
            saveStateForUndo();
            
            try {
                imageFilters->applyResize(currentImage, width, height);
                updateImageDisplay();
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
            }
        }
    }
    
    void applyBlur()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.cancelButton->setVisible(true);
        
        try {
            imageFilters->applyBlur(currentImage, preFilterImage, cancelRequested);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.cancelButton->setVisible(false);
    }
    
    /**
     * @brief Apply the Infrared effect with progress and cancellation support.
     */
    void applyInfrared()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.cancelButton->setVisible(true);
        
        try {
            imageFilters->applyInfrared(currentImage, preFilterImage, cancelRequested);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.cancelButton->setVisible(false);
    }
    
    /**
     * @brief Apply the Purple color filter with progress and cancellation.
     */
    void applyPurpleFilter()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.cancelButton->setVisible(true);
        
        try {
            imageFilters->applyPurpleFilter(currentImage, preFilterImage, cancelRequested);
            updateImageDisplay();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.cancelButton->setVisible(false);
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
     * @brief Compute and enforce a minimum window size to avoid scrollbars for the current image.
     */
    void updateMinimumWindowSize()
    {
        if (!hasImage) {
            setMinimumSize(600, 400);
            return;
        }
        
        // Calculate the minimum size needed to display the image without scrollbars
        // Account for window decorations, menu bar, status bar, and button area
        
        // Get the current window frame size
        QSize currentSize = size();
        QSize contentSize = ui.centralwidget->size();
        
        // Calculate the frame margins (window decorations)
        int frameWidth = currentSize.width() - contentSize.width();
        int frameHeight = currentSize.height() - contentSize.height();
        
        // Calculate the button area height
        int buttonAreaHeight = ui.buttonLayout->sizeHint().height();
        
        // Calculate the minimum scroll area size needed for the image
        QSize scrollAreaSize = ui.scrollArea->size();
        QSize availableSize(scrollAreaSize.width() - 20, scrollAreaSize.height() - 20);
        
        // Calculate the image's natural display size
        double imageAspectRatio = (double)currentImage.width / currentImage.height;
        QSize minImageSize;
        
        // Determine minimum size to fit the image without scrollbars
        if (imageAspectRatio > 1.0) {
            // Wide image - fit to width
            minImageSize.setWidth(availableSize.width());
            minImageSize.setHeight((int)(availableSize.width() / imageAspectRatio));
        } else {
            // Tall image - fit to height
            minImageSize.setHeight(availableSize.height());
            minImageSize.setWidth((int)(availableSize.height() * imageAspectRatio));
        }
        
        // Don't upscale beyond original image size
        if (minImageSize.width() > currentImage.width || minImageSize.height() > currentImage.height) {
            minImageSize = QSize(currentImage.width, currentImage.height);
        }
        
        // Calculate minimum window size
        int minWidth = minImageSize.width() + frameWidth + 20; // +20 for scroll area margins
        int minHeight = minImageSize.height() + frameHeight + buttonAreaHeight + 20; // +20 for margins
        
        // Ensure minimum reasonable size
        minWidth = std::max(minWidth, 600);
        minHeight = std::max(minHeight, 400);
        
        // Set the new minimum size
        setMinimumSize(minWidth, minHeight);
        
        // If current window is smaller than minimum, resize it
        if (width() < minWidth || height() < minHeight) {
            resize(std::max(width(), minWidth), std::max(height(), minHeight));
        }
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
                // Try to save the image
                QString fileName = QFileDialog::getSaveFileName(this,
                    "Save Image", QDir::homePath(),
                    "PNG Files (*.png);;JPEG Files (*.jpg);;BMP Files (*.bmp);;All Files (*)");
                
                if (!fileName.isEmpty()) {
                    try {
                        currentImage.saveImage(fileName.toStdString());
                        event->accept(); // Allow the application to close
                    } catch (const std::exception& e) {
                        QMessageBox::critical(this, "Error", 
                            QString("Failed to save image: %1").arg(e.what()));
                        event->ignore(); // Prevent closing if save failed
                        return;
                    }
                } else {
                    event->ignore(); // User cancelled save dialog
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
                    try {
                        originalImage = ImageIO::loadFromFile(fileName);
                        currentImage = originalImage;
                        hasImage = true;
                        currentFilePath = fileName;
                        hasUnsavedChanges = false; // New image is considered "saved"
                        
                        updateImageDisplay();
                        updateMinimumWindowSize();
                        ui.saveButton->setEnabled(true);
                        ui.unloadButton->setEnabled(true);
                        ui.resetButton->setEnabled(true);
                        ui.grayscaleButton->setEnabled(true);
                        ui.blackWhiteButton->setEnabled(true);
                        ui.invertButton->setEnabled(true);
                        ui.mergeButton->setEnabled(true);
                        ui.flipButton->setEnabled(true);
                        ui.rotateButton->setEnabled(true);
                        ui.cropButton->setEnabled(true);
                        ui.darkLightButton->setEnabled(true);
                        ui.frameButton->setEnabled(true);
                        ui.edgesButton->setEnabled(true);
                        ui.resizeButton->setEnabled(true);
                        ui.blurButton->setEnabled(true);
                        ui.infraredButton->setEnabled(true);
                        ui.purpleButton->setEnabled(true);
                        ui.tvFilterButton->setEnabled(true);
                        
                        // Clear undo/redo history when loading new image
                        history.clear();
                        updateUndoRedoButtons();
                        
                        statusBar()->showMessage(QString("Loaded via drag & drop: %1").arg(fileInfo.fileName()));
                        
                    } catch (const std::exception& e) {
                        QMessageBox::critical(this, "Error", 
                            QString("Failed to load dropped image: %1").arg(e.what()));
                        statusBar()->showMessage("Failed to load image");
                    }
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
    void updateImageDisplay()
    {
        if (!hasImage) return;
        
        QImage qimg(currentImage.width, currentImage.height, QImage::Format_RGB888);
        
        for (int y = 0; y < currentImage.height; y++) {
            for (int x = 0; x < currentImage.width; x++) {
                int r = currentImage(x, y, 0);
                int g = currentImage(x, y, 1);
                int b = currentImage(x, y, 2);
                qimg.setPixel(x, y, qRgb(r, g, b));
            }
        }
        
        QPixmap pixmap = QPixmap::fromImage(qimg);
        
        // Get the available space in the scroll area
         QSize scrollAreaSize = ui.scrollArea->size();
        QSize availableSize(scrollAreaSize.width() - 20, scrollAreaSize.height() - 20); // Account for scrollbars
        
         // Calculate the aspect ratio of the image
         double imageAspectRatio = static_cast<double>(currentImage.width) / currentImage.height;
         double availableAspectRatio = static_cast<double>(availableSize.width()) / availableSize.height();
         
         QSize targetSize;
         
         // Determine the best fit size while maintaining aspect ratio
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
         if (targetSize.width() > currentImage.width || targetSize.height() > currentImage.height) {
             targetSize = QSize(currentImage.width, currentImage.height);
         }
         
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
        
        // Calculate the aspect ratio of the image
        double imageAspectRatio = (double)currentImage.width / currentImage.height;
        double availableAspectRatio = (double)availableSize.width() / availableSize.height();
        
        QSize targetSize;
        
        // Determine the best fit size while maintaining aspect ratio
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
        if (targetSize.width() > currentImage.width || targetSize.height() > currentImage.height) {
            targetSize = QSize(currentImage.width, currentImage.height);
        }
        
        // Build the current displayed pixmap to get its actual size
        QImage qimg(currentImage.width, currentImage.height, QImage::Format_RGB888);
        for (int y = 0; y < currentImage.height; y++) {
            for (int x = 0; x < currentImage.width; x++) {
                int r = currentImage(x, y, 0);
                int g = currentImage(x, y, 1);
                int b = currentImage(x, y, 2);
                qimg.setPixel(x, y, qRgb(r, g, b));
            }
        }
        QPixmap pixmap = QPixmap::fromImage(qimg);
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
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("assets/icon.jpg"));
    
    SimpleImageApp window;
    window.show();
    
    return app.exec();
}

#include "image_studio.moc"