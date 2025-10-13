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
#include "../core/Image_Class.h"
#include "ui_mainwindow.h"

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

private slots:
    void loadImage()
    {
        QString fileName = QFileDialog::getOpenFileName(this,
            "Load Image", QDir::homePath(),
            "Image Files (*.png *.jpg *.jpeg *.bmp *.tga);;All Files (*)");
        
        if (!fileName.isEmpty()) {
            try {
                originalImage.loadNewImage(fileName.toStdString());
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
                
                // Clear undo/redo stacks when loading new image
                while (!undoStack.empty()) undoStack.pop();
                while (!redoStack.empty()) redoStack.pop();
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
                currentImage.saveImage(fileName.toStdString());
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
                    currentImage.saveImage(fileName.toStdString());
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
            
            // Clear undo/redo stacks
            while (!undoStack.empty()) undoStack.pop();
            while (!redoStack.empty()) redoStack.pop();
            
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
        ui.progressBar->setVisible(true);
        ui.progressBar->setRange(0, currentImage.height);
        ui.progressBar->setValue(0);
        ui.cancelButton->setVisible(true);
        
        statusBar()->showMessage("Applying Grayscale filter... (Click Cancel to stop)");
        QApplication::processEvents();
        
        try {
            // Simple grayscale conversion with cancellation support
            for (int y = 0; y < currentImage.height; y++) {
                // Check for cancellation
                if (cancelRequested) {
                    currentImage = preFilterImage;
                    updateImageDisplay();
                    statusBar()->showMessage("Grayscale filter cancelled");
                    ui.progressBar->setVisible(false);
                    ui.cancelButton->setVisible(false);
                    return;
                }
                
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);
                    int gray = (r + g + b) / 3;
                    currentImage.setPixel(x, y, 0, gray);
                    currentImage.setPixel(x, y, 1, gray);
                    currentImage.setPixel(x, y, 2, gray);
                }
                
                // Update progress
                ui.progressBar->setValue(y + 1);
                if (y % 50 == 0) { // Update display every 50 rows
                    QApplication::processEvents();
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Grayscale filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.progressBar->setVisible(false);
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
        ui.progressBar->setVisible(true);
        ui.progressBar->setRange(0, currentImage.height);
        ui.progressBar->setValue(0);
        ui.cancelButton->setVisible(true);
        
        statusBar()->showMessage("Applying TV/CRT filter... (Click Cancel to stop)");
        QApplication::processEvents();
        
        try {
            // Initialize random number generator with time-based seed
            auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
            std::mt19937 rng(seed);
            std::uniform_int_distribution<int> noise_dist(-10, 10);

            for (int y = 0; y < currentImage.height; y++) {
                // Check for cancellation
                if (cancelRequested) {
                    currentImage = preFilterImage;
                    updateImageDisplay();
                    statusBar()->showMessage("TV/CRT filter cancelled");
                    ui.progressBar->setVisible(false);
                    ui.cancelButton->setVisible(false);
                    return;
                }
                
                for (int x = 0; x < currentImage.width; x++) {
                    // Get original pixel values
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);
                    
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
                    
                    // 4. Add slight noise/grain for authentic TV feel
                    int noise = noise_dist(rng); // -10 to +10
                    r = std::min(255, std::max(0, r + noise));
                    g = std::min(255, std::max(0, g + noise));
                    b = std::min(255, std::max(0, b + noise));
                    
                    // Set the final pixel
                    currentImage.setPixel(x, y, 0, r);
                    currentImage.setPixel(x, y, 1, g);
                    currentImage.setPixel(x, y, 2, b);
                }
                
                // Update progress
                ui.progressBar->setValue(y + 1);
                if (y % 20 == 0) { // Update display every 20 rows
                    QApplication::processEvents();
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("TV/CRT filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.progressBar->setVisible(false);
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
        ui.progressBar->setVisible(true);
        ui.progressBar->setRange(0, currentImage.height);
        ui.progressBar->setValue(0);
        ui.cancelButton->setVisible(true);
        
        statusBar()->showMessage("Applying Black & White filter... (Click Cancel to stop)");
        QApplication::processEvents();
        
        try {
            // Pure black and white conversion with cancellation support
            for (int y = 0; y < currentImage.height; y++) {
                // Check for cancellation
                if (cancelRequested) {
                    currentImage = preFilterImage;
                    updateImageDisplay();
                    statusBar()->showMessage("Black & White filter cancelled");
                    ui.progressBar->setVisible(false);
                    ui.cancelButton->setVisible(false);
                    return;
                }
                
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);
                    int gray = (r + g + b) / 3;
                    int bw = (gray > 127) ? 255 : 0;
                    currentImage.setPixel(x, y, 0, bw);
                    currentImage.setPixel(x, y, 1, bw);
                    currentImage.setPixel(x, y, 2, bw);
                }
                
                // Update progress
                ui.progressBar->setValue(y + 1);
                if (y % 50 == 0) { // Update display every 50 rows
                    QApplication::processEvents();
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Black & White filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.progressBar->setVisible(false);
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
        ui.progressBar->setVisible(true);
        ui.progressBar->setRange(0, currentImage.height);
        ui.progressBar->setValue(0);
        ui.cancelButton->setVisible(true);
        
        statusBar()->showMessage("Applying Invert filter... (Click Cancel to stop)");
        QApplication::processEvents();
        
        try {
            for (int y = 0; y < currentImage.height; y++) {
                // Check for cancellation
                if (cancelRequested) {
                    currentImage = preFilterImage;
                    updateImageDisplay();
                    statusBar()->showMessage("Invert filter cancelled");
                    ui.progressBar->setVisible(false);
                    ui.cancelButton->setVisible(false);
                    return;
                }
                
                for (int x = 0; x < currentImage.width; x++) {
                    currentImage.setPixel(x, y, 0, 255 - currentImage(x, y, 0));
                    currentImage.setPixel(x, y, 1, 255 - currentImage(x, y, 1));
                    currentImage.setPixel(x, y, 2, 255 - currentImage(x, y, 2));
                }
                
                // Update progress
                ui.progressBar->setValue(y + 1);
                if (y % 50 == 0) { // Update display every 50 rows
                    QApplication::processEvents();
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Invert filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.progressBar->setVisible(false);
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
                
                statusBar()->showMessage("Applying Merge filter...");
                QApplication::processEvents();
                
                int width = std::min(currentImage.width, mergeImage.width);
                int height = std::min(currentImage.height, mergeImage.height);
                
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        int r = (currentImage(x, y, 0) + mergeImage(x, y, 0)) / 2;
                        int g = (currentImage(x, y, 1) + mergeImage(x, y, 1)) / 2;
                        int b = (currentImage(x, y, 2) + mergeImage(x, y, 2)) / 2;
                        currentImage.setPixel(x, y, 0, r);
                        currentImage.setPixel(x, y, 1, g);
                        currentImage.setPixel(x, y, 2, b);
                    }
                }
                updateImageDisplay();
                statusBar()->showMessage("Merge filter applied");
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
            
            statusBar()->showMessage("Applying Flip filter...");
            QApplication::processEvents();
            
            try {
                if (choice == "Horizontal") {
                    // Horizontal flip
                    for (int y = 0; y < currentImage.height; y++) {
                        for (int x = 0; x < currentImage.width / 2; x++) {
                            int x2 = currentImage.width - 1 - x;
                            for (int c = 0; c < 3; c++) {
                                int temp = currentImage(x, y, c);
                                currentImage.setPixel(x, y, c, currentImage(x2, y, c));
                                currentImage.setPixel(x2, y, c, temp);
                            }
                        }
                    }
                } else {
                    // Vertical flip
                    for (int y = 0; y < currentImage.height / 2; y++) {
                        for (int x = 0; x < currentImage.width; x++) {
                            int y2 = currentImage.height - 1 - y;
                            for (int c = 0; c < 3; c++) {
                                int temp = currentImage(x, y, c);
                                currentImage.setPixel(x, y, c, currentImage(x, y2, c));
                                currentImage.setPixel(x, y2, c, temp);
                            }
                        }
                    }
                }
                updateImageDisplay();
                statusBar()->showMessage("Flip filter applied");
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
            
            statusBar()->showMessage("Applying Rotate filter...");
            QApplication::processEvents();
            
            try {
                Image tempImage = currentImage;
                
                if (choice == "90°") {
                    currentImage = Image(tempImage.height, tempImage.width);
                    for (int y = 0; y < tempImage.height; y++) {
                        for (int x = 0; x < tempImage.width; x++) {
                            int newX = tempImage.height - 1 - y;
                            int newY = x;
                            for (int c = 0; c < 3; c++) {
                                currentImage.setPixel(newX, newY, c, tempImage(x, y, c));
                            }
                        }
                    }
                } else if (choice == "180°") {
                    for (int y = 0; y < currentImage.height / 2; y++) {
                        for (int x = 0; x < currentImage.width; x++) {
                            int y2 = currentImage.height - 1 - y;
                            int x2 = currentImage.width - 1 - x;
                            for (int c = 0; c < 3; c++) {
                                int temp = currentImage(x, y, c);
                                currentImage.setPixel(x, y, c, currentImage(x2, y2, c));
                                currentImage.setPixel(x2, y2, c, temp);
                            }
                        }
                    }
                } else { // 270°
                    currentImage = Image(tempImage.height, tempImage.width);
                    for (int y = 0; y < tempImage.height; y++) {
                        for (int x = 0; x < tempImage.width; x++) {
                            int newX = y;
                            int newY = tempImage.width - 1 - x;
                            for (int c = 0; c < 3; c++) {
                                currentImage.setPixel(newX, newY, c, tempImage(x, y, c));
                            }
                        }
                    }
                }
                updateImageDisplay();
                statusBar()->showMessage("Rotate filter applied");
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
        
        statusBar()->showMessage("Applying Dark & Light filter...");
        QApplication::processEvents();
        
        try {
            Image result(currentImage.width, currentImage.height);
            for (int i = 0; i < currentImage.width; ++i) {
                for (int j = 0; j < currentImage.height; ++j) {
                    for (int k = 0; k < currentImage.channels; ++k) {
                        int p = currentImage(i, j, k);
                        if (choice == "dark") {
                            p = p / 3;
                        } else { // light
                            p = p * 2;
                            if (p > 255) p = 255;
                        }
                        result.setPixel(i, j, k, (unsigned char)p);
                    }
                }
            }
            currentImage = result;
            updateImageDisplay();
            statusBar()->showMessage("Dark & Light filter applied");
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
            
            statusBar()->showMessage("Applying Frame filter...");
            QApplication::processEvents();
            
            try {
                if (choice == "Simple Frame") {
                    // Simple frame with blue outer and inner white border
                    int frameSize = 10;
                    int innerFrame = 5;
                    Image result(currentImage.width + 2 * frameSize, currentImage.height + 2 * frameSize);
                    
                    // Fill with blue frame
                    for (int y = 0; y < result.height; y++) {
                        for (int x = 0; x < result.width; x++) {
                            result.setPixel(x, y, 0, 0);
                            result.setPixel(x, y, 1, 0);
                            result.setPixel(x, y, 2, 255);
                        }
                    }
                    
                    // Copy original image
                    for (int y = 0; y < currentImage.height; y++) {
                        for (int x = 0; x < currentImage.width; x++) {
                            for (int c = 0; c < 3; c++) {
                                result.setPixel(x + frameSize, y + frameSize, c, currentImage(x, y, c));
                            }
                        }
                    }
                    
                    // Add inner white border
                    int gap = 5;
                    for (int y = frameSize + gap; y < frameSize + currentImage.height - gap; y++) {
                        for (int x = frameSize + gap; x < frameSize + currentImage.width - gap; x++) {
                            bool isWhiteBorder =
                                (x < frameSize + gap + innerFrame ||
                                 x >= frameSize + currentImage.width - gap - innerFrame ||
                                 y < frameSize + gap + innerFrame ||
                                 y >= frameSize + currentImage.height - gap - innerFrame);
                            if (isWhiteBorder) {
                            result.setPixel(x, y, 0, 255);
                            result.setPixel(x, y, 1, 255);
                            result.setPixel(x, y, 2, 255);
                        }
                    }
                    }
                    currentImage = result;
                } else {
                    // Decorated frame with brown/beige design and accent patterns
                    int frameWidth = 25;
                    int outerColor[3] = {100, 70, 50};
                    int innerColor[3] = {235, 225, 210};
                    int accentColor[3] = {180, 140, 80};
                    
                    int originalWidth = currentImage.width;
                    int originalHeight = currentImage.height;
                    int newWidth = originalWidth + 2 * frameWidth;
                    int newHeight = originalHeight + 2 * frameWidth;
                    
                    Image result(newWidth, newHeight);
                    
                    // Copy original image
                    for (int y = 0; y < originalHeight; y++) {
                        for (int x = 0; x < originalWidth; x++) {
                            for (int c = 0; c < 3; c++) {
                                result.setPixel(x + frameWidth, y + frameWidth, c, currentImage(x, y, c));
                            }
                        }
                    }
                    
                    // Create decorated frame
                    for (int y = 0; y < newHeight; y++) {
                        for (int x = 0; x < newWidth; x++) {
                            if (x < frameWidth || x >= newWidth - frameWidth ||
                                y < frameWidth || y >= newHeight - frameWidth) {
                                
                                int distFromEdge = std::min({x, y, newWidth - 1 - x, newHeight - 1 - y});
                                
                                if (distFromEdge < 3) {
                                    for (int c = 0; c < 3; c++) {
                                        result.setPixel(x, y, c, outerColor[c]);
                                    }
                                }
                                else if (distFromEdge == 12 || distFromEdge == 15 || distFromEdge == 9) {
                                    for (int c = 0; c < 3; c++) {
                                        result.setPixel(x, y, c, accentColor[c]);
                                    }
                                }
                                else if (distFromEdge < frameWidth - 4) {
                                    for (int c = 0; c < 3; c++) {
                                        result.setPixel(x, y, c, innerColor[c]);
                                    }
                                    
                                    int cornerDist = std::min(std::min(x, newWidth - 1 - x),
                                                             std::min(y, newHeight - 1 - y));
                                    
                                    if (cornerDist < frameWidth) {
                                        if ((x + y) % 12 == 0) {
                                            for (int c = 0; c < 3; c++) {
                                                result.setPixel(x, y, c, accentColor[c]);
                                            }
                                        }
                                    }
                                }
                                else if (distFromEdge >= frameWidth - 4 && distFromEdge < frameWidth - 1) {
                                    for (int c = 0; c < 3; c++) {
                                        result.setPixel(x, y, c, accentColor[c]);
                                    }
                                }
                                else {
                                    for (int c = 0; c < 3; c++) {
                                        result.setPixel(x, y, c, outerColor[c]);
                                    }
                                }
                            }
                        }
                    }
                currentImage = result;
                }
                updateImageDisplay();
                statusBar()->showMessage("Frame filter applied");
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
            }
        }
    }
    
    void applyEdges()
    {
        if (!hasImage) return;
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Edge Detection filter...");
        QApplication::processEvents();
        
        try {
            // Convert to grayscale first
            Image gray(currentImage.width, currentImage.height);
            for (int y = 0; y < currentImage.height; y++) {
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);
                    // Use weighted average for better grayscale conversion
                    int grayVal = (int)(0.299 * r + 0.587 * g + 0.114 * b);
                    gray.setPixel(x, y, 0, grayVal);
                    gray.setPixel(x, y, 1, grayVal);
                    gray.setPixel(x, y, 2, grayVal);
                }
            }

            // Apply Gaussian blur to reduce noise
            Image blurred(currentImage.width, currentImage.height);
            int kernel[5][5] = {
                {1, 4, 6, 4, 1},
                {4, 16, 24, 16, 4},
                {6, 24, 36, 24, 6},
                {4, 16, 24, 16, 4},
                {1, 4, 6, 4, 1}
            };
            int kernelSum = 256; // Sum of all kernel values

            for (int y = 2; y < currentImage.height - 2; y++) {
                for (int x = 2; x < currentImage.width - 2; x++) {
                    int sum = 0;
                    for (int ky = -2; ky <= 2; ky++) {
                        for (int kx = -2; kx <= 2; kx++) {
                            sum += gray(x + kx, y + ky, 0) * kernel[ky + 2][kx + 2];
                        }
                    }
                    int blurredVal = sum / kernelSum;
                    blurred.setPixel(x, y, 0, blurredVal);
                    blurred.setPixel(x, y, 1, blurredVal);
                    blurred.setPixel(x, y, 2, blurredVal);
                }
            }

            // Apply Sobel edge detection
            Image edge(currentImage.width, currentImage.height);
            
            // Sobel kernels
            int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            for (int y = 1; y < currentImage.height - 1; y++) {
                for (int x = 1; x < currentImage.width - 1; x++) {
                    int gx = 0, gy = 0;
                    
                    // Apply Sobel kernels
                    for (int ky = -1; ky <= 1; ky++) {
                        for (int kx = -1; kx <= 1; kx++) {
                            int pixelVal = blurred(x + kx, y + ky, 0);
                            gx += pixelVal * sobelX[ky + 1][kx + 1];
                            gy += pixelVal * sobelY[ky + 1][kx + 1];
                        }
                    }
                    
                    // Calculate gradient magnitude
                    int magnitude = (int)std::sqrt(gx * gx + gy * gy);
                    
                    // Clamp to 0-255 range
                    magnitude = std::min(255, std::max(0, magnitude));
                    
                    // Apply threshold to enhance edges (white edges on black background)
                    int edgeVal = (magnitude > 50) ? 0 : 255;
                    
                    edge.setPixel(x, y, 0, edgeVal);
                    edge.setPixel(x, y, 1, edgeVal);
                    edge.setPixel(x, y, 2, edgeVal);
                }
            }
            
            currentImage = edge;
            updateImageDisplay();
            statusBar()->showMessage("Edge Detection filter applied");
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
            
            statusBar()->showMessage("Applying Resize filter...");
            QApplication::processEvents();
            
            try {
                Image result(width, height);
                
                double xRatio = (double)currentImage.width / width;
                double yRatio = (double)currentImage.height / height;
                
                for (int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        int srcX = (int)(x * xRatio);
                        int srcY = (int)(y * yRatio);
                        
                        srcX = std::min(srcX, (int)currentImage.width - 1);
                        srcY = std::min(srcY, (int)currentImage.height - 1);
                        
                        result.setPixel(x, y, 0, currentImage(srcX, srcY, 0));
                        result.setPixel(x, y, 1, currentImage(srcX, srcY, 1));
                        result.setPixel(x, y, 2, currentImage(srcX, srcY, 2));
                    }
                }
                
                currentImage = result;
                updateImageDisplay();
                statusBar()->showMessage(QString("Resize filter applied (%1x%2)").arg(width).arg(height));
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
        ui.progressBar->setVisible(true);
        ui.progressBar->setRange(0, currentImage.height);
        ui.progressBar->setValue(0);
        ui.cancelButton->setVisible(true);
        
        statusBar()->showMessage("Applying Blur filter... (Click Cancel to stop)");
        QApplication::processEvents();
        
        try {
            // Radius-15 average blur with cancellation support
            int blurSize = 15;
            Image result(currentImage.width, currentImage.height);
            
            for (int y = 0; y < currentImage.height; y++) {
                // Check for cancellation
                if (cancelRequested) {
                    currentImage = preFilterImage;
                    updateImageDisplay();
                    statusBar()->showMessage("Blur filter cancelled");
                    ui.progressBar->setVisible(false);
                    ui.cancelButton->setVisible(false);
                    return;
                }
                
                for (int x = 0; x < currentImage.width; x++) {
                    int R = 0, G = 0, B = 0;
                    int count = 0;
                    for (int i = -blurSize; i <= blurSize; i++) {
                        for (int j = -blurSize; j <= blurSize; j++) {
                            int nx = x + j;
                            int ny = y + i;
                            if (nx >= 0 && nx < currentImage.width && ny >= 0 && ny < currentImage.height) {
                                R += currentImage(nx, ny, 0);
                                G += currentImage(nx, ny, 1);
                                B += currentImage(nx, ny, 2);
                                count++;
                            }
                        }
                    }
                    result.setPixel(x, y, 0, R / count);
                    result.setPixel(x, y, 1, G / count);
                    result.setPixel(x, y, 2, B / count);
                }
                
                // Update progress
                ui.progressBar->setValue(y + 1);
                if (y % 10 == 0) { // Update display every 10 rows to avoid too much overhead
                    QApplication::processEvents();
                }
            }
            
            currentImage = result;
            updateImageDisplay();
            statusBar()->showMessage("Blur filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.progressBar->setVisible(false);
        ui.cancelButton->setVisible(false);
    }
    
    void applyInfrared()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.progressBar->setVisible(true);
        ui.progressBar->setRange(0, currentImage.width);
        ui.progressBar->setValue(0);
        ui.cancelButton->setVisible(true);
        
        statusBar()->showMessage("Applying Infrared filter... (Click Cancel to stop)");
        QApplication::processEvents();
        
        try {
            for (int x = 0; x < currentImage.width; ++x) {
                // Check for cancellation
                if (cancelRequested) {
                    currentImage = preFilterImage;
                    updateImageDisplay();
                    statusBar()->showMessage("Infrared filter cancelled");
                    ui.progressBar->setVisible(false);
                    ui.cancelButton->setVisible(false);
                    return;
                }
                
                for (int y = 0; y < currentImage.height; ++y) {
                    int red   = currentImage(x, y, 0);
                    int green = currentImage(x, y, 1);
                    int blue  = currentImage(x, y, 2);

                    float brightness = (red + green + blue) / 3.0f;
                    float inverted = 255 - brightness;

                    int R = 255;
                    unsigned int G = int(inverted);
                    unsigned int B = int(inverted);

                    currentImage(x, y, 0) = R;
                    currentImage(x, y, 1) = G;
                    currentImage(x, y, 2) = B;
                }
                
                // Update progress
                ui.progressBar->setValue(x + 1);
                if (x % 50 == 0) { // Update display every 50 columns
                    QApplication::processEvents();
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Infrared filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.progressBar->setVisible(false);
        ui.cancelButton->setVisible(false);
    }
    
    void applyPurpleFilter()
    {
        if (!hasImage) return;
        
        // Setup for cancellation
        cancelRequested = false;
        preFilterImage = currentImage;
        saveStateForUndo();
        
        // Show progress UI
        ui.progressBar->setVisible(true);
        ui.progressBar->setRange(0, currentImage.height);
        ui.progressBar->setValue(0);
        ui.cancelButton->setVisible(true);
        
        statusBar()->showMessage("Applying Purple filter... (Click Cancel to stop)");
        QApplication::processEvents();
        
        try {
            for (int y = 0; y < currentImage.height; y++) {
                // Check for cancellation
                if (cancelRequested) {
                    currentImage = preFilterImage;
                    updateImageDisplay();
                    statusBar()->showMessage("Purple filter cancelled");
                    ui.progressBar->setVisible(false);
                    ui.cancelButton->setVisible(false);
                    return;
                }
                
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);

                    r = std::min(255, (int)(r * 1.3));
                    g = std::max(0,   (int)(g * 0.5));
                    b = std::min(255, (int)(b * 1.3));

                    currentImage.setPixel(x, y, 0, r);
                    currentImage.setPixel(x, y, 1, g);
                    currentImage.setPixel(x, y, 2, b);
                }
                
                // Update progress
                ui.progressBar->setValue(y + 1);
                if (y % 50 == 0) { // Update display every 50 rows
                    QApplication::processEvents();
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Purple filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
        
        // Hide progress UI
        ui.progressBar->setVisible(false);
        ui.cancelButton->setVisible(false);
    }
    
    void startCropMode()
    {
        if (!hasImage) return;
        if (!rubberBand) {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, ui.imageLabel);
        }
        cropping = true;
        statusBar()->showMessage("Crop mode: drag to select area, release to crop");
    }
    
    void undo()
    {
        if (!hasImage || undoStack.empty()) return;
        
        // Save current state to redo stack
        redoStack.push(currentImage);
        
        // Restore previous state
        currentImage = undoStack.top();
        undoStack.pop();
        
        updateImageDisplay();
        updateUndoRedoButtons();
        statusBar()->showMessage("Undo applied");
    }
    
    void redo()
    {
        if (!hasImage || redoStack.empty()) return;
        
        // Save current state to undo stack
        undoStack.push(currentImage);
        
        // Restore next state
        currentImage = redoStack.top();
        redoStack.pop();
        
        updateImageDisplay();
        updateUndoRedoButtons();
        statusBar()->showMessage("Redo applied");
    }
    
    void cancelFilter()
    {
        cancelRequested = true;
        statusBar()->showMessage("Cancelling filter...");
    }

private:
    Ui::MainWindow ui;
    
    void saveStateForUndo()
    {
        if (!hasImage) return;
        
        // Save current state to undo stack
        undoStack.push(currentImage);
        
        // Mark as having unsaved changes
        hasUnsavedChanges = true;
        
        // Limit undo stack size to prevent excessive memory usage
        if (undoStack.size() > MAX_UNDO_STEPS) {
            // Remove oldest state (this is a simple approach)
            std::stack<Image> tempStack;
            for (int i = 0; i < MAX_UNDO_STEPS - 1; i++) {
                tempStack.push(undoStack.top());
                undoStack.pop();
            }
            undoStack = tempStack;
        }
        
        // Clear redo stack when new action is performed
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        
        updateUndoRedoButtons();
    }
    
    void updateUndoRedoButtons()
    {
        ui.undoButton->setEnabled(!undoStack.empty());
        ui.redoButton->setEnabled(!redoStack.empty());
    }
    
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
    
    void resizeEvent(QResizeEvent *event) override
    {
        QMainWindow::resizeEvent(event);
        // Use timer to avoid too many updates during rapid resizing
        if (hasImage) {
            resizeTimer->start();
        }
    }
    
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
    
    void dragMoveEvent(QDragMoveEvent *event) override
    {
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }
    
    void dragLeaveEvent(QDragLeaveEvent *event) override
    {
        Q_UNUSED(event)
        statusBar()->showMessage(hasImage ? "Ready" : "Ready - Drag an image here or click 'Load Image'");
    }
    
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
                        originalImage.loadNewImage(fileName.toStdString());
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
                        
                        // Clear undo/redo stacks when loading new image
                        while (!undoStack.empty()) undoStack.pop();
                        while (!redoStack.empty()) redoStack.pop();
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
         double imageAspectRatio = (double)currentImage.width / currentImage.height;
         double availableAspectRatio = (double)availableSize.width() / availableSize.height();
         
         QSize targetSize;
         
         // Determine the best fit size while maintaining aspect ratio
         if (imageAspectRatio > availableAspectRatio) {
             // Image is wider than available space - fit to width
             targetSize.setWidth(availableSize.width());
             targetSize.setHeight((int)(availableSize.width() / imageAspectRatio));
         } else {
             // Image is taller than available space - fit to height
             targetSize.setHeight(availableSize.height());
             targetSize.setWidth((int)(availableSize.height() * imageAspectRatio));
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
            targetSize.setHeight((int)(availableSize.width() / imageAspectRatio));
        } else {
            // Image is taller than available space - fit to height
            targetSize.setHeight(availableSize.height());
            targetSize.setWidth((int)(availableSize.height() * imageAspectRatio));
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
        double scaleX = (double)currentImage.width / scaledPixmap.width();
        double scaleY = (double)currentImage.height / scaledPixmap.height();
        
        int x0 = std::max(0, (int)((selection.left() - offsetX) * scaleX));
        int y0 = std::max(0, (int)((selection.top() - offsetY) * scaleY));
        int x1 = std::min((int)currentImage.width, (int)((selection.right() - offsetX + 1) * scaleX));
        int y1 = std::min((int)currentImage.height, (int)((selection.bottom() - offsetY + 1) * scaleY));
        
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
    std::stack<Image> undoStack;
    std::stack<Image> redoStack;
    static const int MAX_UNDO_STEPS = 20; // Limit memory usage
    
    // Save state tracking
    bool hasUnsavedChanges = false;
    
    // Resize handling
    QTimer *resizeTimer;
    
    // Crop handling
    bool cropping = false;
    QRubberBand *rubberBand = nullptr;
    QPoint cropOrigin;
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
