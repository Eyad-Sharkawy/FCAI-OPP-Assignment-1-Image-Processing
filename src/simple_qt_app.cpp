//==================================================================================
//                                       Header
//==================================================================================
//section: S33
//group:B
//lab7
//TA:Laila Mostafa
//==================================================================================
//Team members:
// Ahmed Mohamed ElSayed Tolba  // ID: 20242023
// Eyad Mohamed Saad Ali        // ID: 20242062
// Tarek Sami Mohamed Mohamed   // ID: 20242190
//===================================================================================
//Work breakdown:
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
#include <cmath>
#include <algorithm>
#include <stack>
#include "Image_Class.h"

class SimpleImageApp : public QMainWindow
{
    Q_OBJECT

public:
SimpleImageApp(QWidget *parent = nullptr) : QMainWindow(parent), hasImage(false)
    {
        setWindowTitle("Image Studio");
        setWindowIcon(QIcon("assets/icon.jpg"));
        setMinimumSize(600, 400);
        
        // Create central widget
        QWidget *centralWidget = new QWidget();
        setCentralWidget(centralWidget);
        
        // Create layout
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);
        
        // Create image label
        imageLabel = new QLabel();
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setMinimumSize(400, 300);
        imageLabel->setStyleSheet(
            "QLabel {"
            "  border: 2px solid #9e9e9e;"
            "  background-color: #f4f4f4;"
            "  color: #2b2b2b;"
            "  font-size: 14px;"
            "}"
        );
        imageLabel->setText("No image loaded\nClick 'Load Image' or drag & drop an image here");
        
        // Create scroll area
        scrollArea = new QScrollArea();
        scrollArea->setWidget(imageLabel);
        scrollArea->setWidgetResizable(true);
        layout->addWidget(scrollArea);
        
        // Create buttons in a grid layout
        QGridLayout *buttonLayout = new QGridLayout();
        
        // File operations
        loadButton = new QPushButton("Load Image");
        saveButton = new QPushButton("Save Image");
        resetButton = new QPushButton("Reset");
        undoButton = new QPushButton("Undo");
        redoButton = new QPushButton("Redo");
        
        // Basic filters
        grayscaleButton = new QPushButton("Grayscale");
        blackWhiteButton = new QPushButton("Black & White");
        invertButton = new QPushButton("Invert");
        mergeButton = new QPushButton("Merge");
        
        // Transform filters
        flipButton = new QPushButton("Flip");
        rotateButton = new QPushButton("Rotate");
        cropButton = new QPushButton("Crop");
        darkLightButton = new QPushButton("Dark & Light");
        frameButton = new QPushButton("Frame");
        
        // Advanced filters
        edgesButton = new QPushButton("Edge Detection");
        resizeButton = new QPushButton("Resize");
        blurButton = new QPushButton("Blur");
        infraredButton = new QPushButton("Infrared");
        purpleButton = new QPushButton("Purple Filter");
        tvFilterButton = new QPushButton("TV/CRT Filter");
        
        // Add buttons to grid
        int row = 0, col = 0;
        buttonLayout->addWidget(loadButton, row, col++);
        buttonLayout->addWidget(saveButton, row, col++);
        buttonLayout->addWidget(resetButton, row, col++);
        buttonLayout->addWidget(undoButton, row, col++);
        buttonLayout->addWidget(redoButton, row, col++);
        
        row++; col = 0;
        buttonLayout->addWidget(grayscaleButton, row, col++);
        buttonLayout->addWidget(blackWhiteButton, row, col++);
        buttonLayout->addWidget(invertButton, row, col++);
        buttonLayout->addWidget(mergeButton, row, col++);
        
        row++; col = 0;
        buttonLayout->addWidget(flipButton, row, col++);
        buttonLayout->addWidget(rotateButton, row, col++);
        buttonLayout->addWidget(darkLightButton, row, col++);
        buttonLayout->addWidget(frameButton, row, col++);
        buttonLayout->addWidget(cropButton, row, col++);
        
        row++; col = 0;
        buttonLayout->addWidget(edgesButton, row, col++);
        buttonLayout->addWidget(resizeButton, row, col++);
        buttonLayout->addWidget(blurButton, row, col++);
        buttonLayout->addWidget(infraredButton, row, col++);
        
        row++; col = 0;
        buttonLayout->addWidget(purpleButton, row, col++);
        buttonLayout->addWidget(tvFilterButton, row, col++);
        
        layout->addLayout(buttonLayout);
        
        // Connect signals
        connect(loadButton, &QPushButton::clicked, this, &SimpleImageApp::loadImage);
        connect(saveButton, &QPushButton::clicked, this, &SimpleImageApp::saveImage);
        connect(resetButton, &QPushButton::clicked, this, &SimpleImageApp::resetImage);
        connect(undoButton, &QPushButton::clicked, this, &SimpleImageApp::undo);
        connect(redoButton, &QPushButton::clicked, this, &SimpleImageApp::redo);
        connect(grayscaleButton, &QPushButton::clicked, this, &SimpleImageApp::applyGrayscale);
        connect(blackWhiteButton, &QPushButton::clicked, this, &SimpleImageApp::applyBlackAndWhite);
        connect(invertButton, &QPushButton::clicked, this, &SimpleImageApp::applyInvert);
        connect(mergeButton, &QPushButton::clicked, this, &SimpleImageApp::applyMerge);
        connect(flipButton, &QPushButton::clicked, this, &SimpleImageApp::applyFlip);
        connect(rotateButton, &QPushButton::clicked, this, &SimpleImageApp::applyRotate);
        connect(darkLightButton, &QPushButton::clicked, this, &SimpleImageApp::applyDarkAndLight);
        connect(frameButton, &QPushButton::clicked, this, &SimpleImageApp::applyFrame);
        connect(cropButton, &QPushButton::clicked, this, &SimpleImageApp::startCropMode);
        connect(edgesButton, &QPushButton::clicked, this, &SimpleImageApp::applyEdges);
        connect(resizeButton, &QPushButton::clicked, this, &SimpleImageApp::applyResize);
        connect(blurButton, &QPushButton::clicked, this, &SimpleImageApp::applyBlur);
        connect(infraredButton, &QPushButton::clicked, this, &SimpleImageApp::applyInfrared);
        connect(purpleButton, &QPushButton::clicked, this, &SimpleImageApp::applyPurpleFilter);
        connect(tvFilterButton, &QPushButton::clicked, this, &SimpleImageApp::applyTVFilter);
        
        // Create menu bar
        QMenuBar *menuBar = this->menuBar();
        QMenu *fileMenu = menuBar->addMenu("File");
        fileMenu->addAction("Load Image", this, &SimpleImageApp::loadImage);
        fileMenu->addAction("Save Image", this, &SimpleImageApp::saveImage);
        fileMenu->addAction("Reset Image", this, &SimpleImageApp::resetImage);
        fileMenu->addSeparator();
        fileMenu->addAction("Undo", this, &SimpleImageApp::undo, QKeySequence::Undo);
        fileMenu->addAction("Redo", this, &SimpleImageApp::redo, QKeySequence::Redo);
        fileMenu->addSeparator();
        fileMenu->addAction("Exit", this, &QWidget::close);
        
        QMenu *filterMenu = menuBar->addMenu("Filters");
        filterMenu->addAction("Grayscale", this, &SimpleImageApp::applyGrayscale);
        filterMenu->addAction("Black & White", this, &SimpleImageApp::applyBlackAndWhite);
        filterMenu->addAction("Invert", this, &SimpleImageApp::applyInvert);
        filterMenu->addAction("Merge", this, &SimpleImageApp::applyMerge);
        filterMenu->addSeparator();
        filterMenu->addAction("Flip", this, &SimpleImageApp::applyFlip);
        filterMenu->addAction("Rotate", this, &SimpleImageApp::applyRotate);
        filterMenu->addAction("Crop", this, &SimpleImageApp::startCropMode);
        filterMenu->addAction("Dark & Light", this, &SimpleImageApp::applyDarkAndLight);
        filterMenu->addAction("Frame", this, &SimpleImageApp::applyFrame);
        filterMenu->addSeparator();
        filterMenu->addAction("Edge Detection", this, &SimpleImageApp::applyEdges);
        filterMenu->addAction("Resize", this, &SimpleImageApp::applyResize);
        filterMenu->addAction("Blur", this, &SimpleImageApp::applyBlur);
        filterMenu->addAction("Infrared", this, &SimpleImageApp::applyInfrared);
        filterMenu->addAction("Purple Filter", this, &SimpleImageApp::applyPurpleFilter);
        filterMenu->addAction("TV/CRT Filter", this, &SimpleImageApp::applyTVFilter);
        
        // Create status bar
        statusBar()->showMessage("Ready - Drag an image here or click 'Load Image'");
        
        // Initialize resize timer for smooth resizing
        resizeTimer = new QTimer(this);
        resizeTimer->setSingleShot(true);
        resizeTimer->setInterval(100); // 100ms delay
        connect(resizeTimer, &QTimer::timeout, this, &SimpleImageApp::updateImageDisplay);
        
        // Enable drag and drop
        setAcceptDrops(true);
        imageLabel->setAcceptDrops(true);
        scrollArea->setAcceptDrops(true);
        // Install event filter on imageLabel to capture mouse events for crop
        imageLabel->installEventFilter(this);
        
        // Initially disable filter buttons
        saveButton->setEnabled(false);
        resetButton->setEnabled(false);
        undoButton->setEnabled(false);
        redoButton->setEnabled(false);
        grayscaleButton->setEnabled(false);
        blackWhiteButton->setEnabled(false);
        invertButton->setEnabled(false);
        mergeButton->setEnabled(false);
        flipButton->setEnabled(false);
        rotateButton->setEnabled(false);
        darkLightButton->setEnabled(false);
        frameButton->setEnabled(false);
        edgesButton->setEnabled(false);
        resizeButton->setEnabled(false);
        blurButton->setEnabled(false);
        infraredButton->setEnabled(false);
        purpleButton->setEnabled(false);
        tvFilterButton->setEnabled(false);
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
                
                updateImageDisplay();
                saveButton->setEnabled(true);
                resetButton->setEnabled(true);
                grayscaleButton->setEnabled(true);
                blackWhiteButton->setEnabled(true);
                invertButton->setEnabled(true);
                mergeButton->setEnabled(true);
                flipButton->setEnabled(true);
                rotateButton->setEnabled(true);
                darkLightButton->setEnabled(true);
                frameButton->setEnabled(true);
                edgesButton->setEnabled(true);
                resizeButton->setEnabled(true);
                blurButton->setEnabled(true);
                infraredButton->setEnabled(true);
                purpleButton->setEnabled(true);
                tvFilterButton->setEnabled(true);
                
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
                statusBar()->showMessage(QString("Saved: %1").arg(QFileInfo(fileName).fileName()));
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", 
                    QString("Failed to save image: %1").arg(e.what()));
            }
        }
    }
    
    void applyGrayscale()
    {
        if (!hasImage) return;
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Grayscale filter...");
        QApplication::processEvents();
        
        try {
            // Simple grayscale conversion
            for (int y = 0; y < currentImage.height; y++) {
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);
                    int gray = (r + g + b) / 3;
                    currentImage.setPixel(x, y, 0, gray);
                    currentImage.setPixel(x, y, 1, gray);
                    currentImage.setPixel(x, y, 2, gray);
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Grayscale filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
    }
    
    void applyTVFilter()
    {
        if (!hasImage) return;
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying TV/CRT filter...");
        QApplication::processEvents();
        
        try {
            // Simple TV filter effect
            for (int y = 0; y < currentImage.height; y++) {
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);
                    
                    // Add scanlines
                    if (y % 3 == 0) {
                        r = (int)(r * 0.7f);
                        g = (int)(g * 0.7f);
                        b = (int)(b * 0.7f);
                    }
                    
                    // Add some color shift
                    r = std::min(255, (int)(r * 1.1f));
                    b = std::min(255, (int)(b * 1.2f));
                    
                    currentImage.setPixel(x, y, 0, r);
                    currentImage.setPixel(x, y, 1, g);
                    currentImage.setPixel(x, y, 2, b);
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("TV/CRT filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
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
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Black & White filter...");
        QApplication::processEvents();
        
        try {
            // Pure black and white conversion
            for (int y = 0; y < currentImage.height; y++) {
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
            }
            updateImageDisplay();
            statusBar()->showMessage("Black & White filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
    }
    
    void applyInvert()
    {
        if (!hasImage) return;
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Invert filter...");
        QApplication::processEvents();
        
        try {
            for (int y = 0; y < currentImage.height; y++) {
                for (int x = 0; x < currentImage.width; x++) {
                    currentImage.setPixel(x, y, 0, 255 - currentImage(x, y, 0));
                    currentImage.setPixel(x, y, 1, 255 - currentImage(x, y, 1));
                    currentImage.setPixel(x, y, 2, 255 - currentImage(x, y, 2));
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Invert filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
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
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Dark & Light filter...");
        QApplication::processEvents();
        
        try {
            for (int y = 0; y < currentImage.height; y++) {
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);
                    
                    // Increase contrast
                    r = std::min(255, std::max(0, (r - 128) * 2 + 128));
                    g = std::min(255, std::max(0, (g - 128) * 2 + 128));
                    b = std::min(255, std::max(0, (b - 128) * 2 + 128));
                    
                    currentImage.setPixel(x, y, 0, r);
                    currentImage.setPixel(x, y, 1, g);
                    currentImage.setPixel(x, y, 2, b);
                }
            }
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
                int borderWidth = (choice == "Simple Frame") ? 10 : 20;
                Image result(currentImage.width + 2 * borderWidth, currentImage.height + 2 * borderWidth);
                
                if (choice == "Simple Frame") {
                    // Fill with white border
                    for (int y = 0; y < result.height; y++) {
                        for (int x = 0; x < result.width; x++) {
                            result.setPixel(x, y, 0, 255);
                            result.setPixel(x, y, 1, 255);
                            result.setPixel(x, y, 2, 255);
                        }
                    }
                } else {
                    // Fill with gradient border
                    for (int y = 0; y < result.height; y++) {
                        for (int x = 0; x < result.width; x++) {
                            int intensity = 255 - (std::min(x, std::min(y, std::min(result.width - x, result.height - y))) * 255 / borderWidth);
                            result.setPixel(x, y, 0, intensity);
                            result.setPixel(x, y, 1, intensity);
                            result.setPixel(x, y, 2, intensity);
                        }
                    }
                }
                
                // Copy original image
                for (int y = 0; y < currentImage.height; y++) {
                    for (int x = 0; x < currentImage.width; x++) {
                        result.setPixel(x + borderWidth, y + borderWidth, 0, currentImage(x, y, 0));
                        result.setPixel(x + borderWidth, y + borderWidth, 1, currentImage(x, y, 1));
                        result.setPixel(x + borderWidth, y + borderWidth, 2, currentImage(x, y, 2));
                    }
                }
                
                currentImage = result;
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
            Image result = currentImage;
            
            // Simple edge detection using Sobel operator
            for (int y = 1; y < currentImage.height - 1; y++) {
                for (int x = 1; x < currentImage.width - 1; x++) {
                    // Sobel X
                    int gx = -currentImage(x-1, y-1, 0) + currentImage(x+1, y-1, 0) +
                             -2*currentImage(x-1, y, 0) + 2*currentImage(x+1, y, 0) +
                             -currentImage(x-1, y+1, 0) + currentImage(x+1, y+1, 0);
                    
                    // Sobel Y
                    int gy = -currentImage(x-1, y-1, 0) - 2*currentImage(x, y-1, 0) - currentImage(x+1, y-1, 0) +
                             currentImage(x-1, y+1, 0) + 2*currentImage(x, y+1, 0) + currentImage(x+1, y+1, 0);
                    
                    int magnitude = std::min(255, (int)std::sqrt(gx*gx + gy*gy));
                    
                    result.setPixel(x, y, 0, magnitude);
                    result.setPixel(x, y, 1, magnitude);
                    result.setPixel(x, y, 2, magnitude);
                }
            }
            
            currentImage = result;
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
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Blur filter...");
        QApplication::processEvents();
        
        try {
            Image result = currentImage;
            
            // Simple box blur
            for (int y = 1; y < currentImage.height - 1; y++) {
                for (int x = 1; x < currentImage.width - 1; x++) {
                    int r = 0, g = 0, b = 0;
                    
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dx = -1; dx <= 1; dx++) {
                            r += currentImage(x + dx, y + dy, 0);
                            g += currentImage(x + dx, y + dy, 1);
                            b += currentImage(x + dx, y + dy, 2);
                        }
                    }
                    
                    result.setPixel(x, y, 0, r / 9);
                    result.setPixel(x, y, 1, g / 9);
                    result.setPixel(x, y, 2, b / 9);
                }
            }
            
            currentImage = result;
            updateImageDisplay();
            statusBar()->showMessage("Blur filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
    }
    
    void applyInfrared()
    {
        if (!hasImage) return;
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Infrared filter...");
        QApplication::processEvents();
        
        try {
            for (int y = 0; y < currentImage.height; y++) {
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);

                    float brightness = (r + g + b) / 3.0f;
                    float inverted = 255 - brightness;

                    int R = 255;
                    unsigned int G = int(inverted);
                    unsigned int B = int(inverted);

                    currentImage.setPixel(x, y, 0, R);
                    currentImage.setPixel(x, y, 1, G);
                    currentImage.setPixel(x, y, 2, B);
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Infrared filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
    }
    
    void applyPurpleFilter()
    {
        if (!hasImage) return;
        
        saveStateForUndo();
        
        statusBar()->showMessage("Applying Purple filter...");
        QApplication::processEvents();
        
        try {
            for (int y = 0; y < currentImage.height; y++) {
                for (int x = 0; x < currentImage.width; x++) {
                    int r = currentImage(x, y, 0);
                    int g = currentImage(x, y, 1);
                    int b = currentImage(x, y, 2);

                    r = std::min(255, (int)(r * 1.3));
                    g = std::max(0, (int)(g * 0.5));
                    b = std::min(255, (int)(b * 1.3));

                    currentImage.setPixel(x, y, 0, r);
                    currentImage.setPixel(x, y, 1, g);
                    currentImage.setPixel(x, y, 2, b);
                }
            }
            updateImageDisplay();
            statusBar()->showMessage("Purple filter applied");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", QString("Filter failed: %1").arg(e.what()));
        }
    }
    
    void startCropMode()
    {
        if (!hasImage) return;
        if (!rubberBand) {
            rubberBand = new QRubberBand(QRubberBand::Rectangle, imageLabel);
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

private:
    void saveStateForUndo()
    {
        if (!hasImage) return;
        
        // Save current state to undo stack
        undoStack.push(currentImage);
        
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
        undoButton->setEnabled(!undoStack.empty());
        redoButton->setEnabled(!redoStack.empty());
    }
    
protected:
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
                        
                        updateImageDisplay();
                        saveButton->setEnabled(true);
                        resetButton->setEnabled(true);
                        grayscaleButton->setEnabled(true);
                        blackWhiteButton->setEnabled(true);
                        invertButton->setEnabled(true);
                        mergeButton->setEnabled(true);
                        flipButton->setEnabled(true);
                        rotateButton->setEnabled(true);
                        darkLightButton->setEnabled(true);
                        frameButton->setEnabled(true);
                        edgesButton->setEnabled(true);
                        resizeButton->setEnabled(true);
                        blurButton->setEnabled(true);
                        infraredButton->setEnabled(true);
                        purpleButton->setEnabled(true);
                        tvFilterButton->setEnabled(true);
                        
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
        if (watched == imageLabel && cropping && hasImage) {
            if (event->type() == QEvent::MouseButtonPress) {
                QMouseEvent *me = static_cast<QMouseEvent*>(event);
                cropOrigin = me->pos();
                if (!rubberBand) rubberBand = new QRubberBand(QRubberBand::Rectangle, imageLabel);
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
        QSize scrollAreaSize = scrollArea->size();
        QSize availableSize(scrollAreaSize.width() - 20, scrollAreaSize.height() - 20); // Account for scrollbars
        
        // Scale the image to fit the available space while maintaining aspect ratio
        QPixmap scaledPixmap = pixmap.scaled(availableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        
        imageLabel->setPixmap(scaledPixmap);
        imageLabel->setText("");
        
        // Update status bar with image info
        statusBar()->showMessage(QString("Image: %1x%2 | Display: %3x%4")
            .arg(currentImage.width)
            .arg(currentImage.height)
            .arg(scaledPixmap.width())
            .arg(scaledPixmap.height()));
    }
    
    void performCropFromSelection(const QRect &selectionOnLabel)
    {
        if (!hasImage) return;
        if (selectionOnLabel.width() <= 1 || selectionOnLabel.height() <= 1) return;
        
        // Determine the scale used to draw the pixmap on the label
        // We rendered a scaled pixmap that fits availableSize with KeepAspectRatio.
        QSize scrollAreaSize = scrollArea->size();
        QSize availableSize(scrollAreaSize.width() - 20, scrollAreaSize.height() - 20);
        
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
        QPixmap scaledPixmap = pixmap.scaled(availableSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        
        // The image is centered inside imageLabel.
        QSize labelSize = imageLabel->size();
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
    
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QPushButton *cropButton;
    QPushButton *loadButton;
    QPushButton *saveButton;
    QPushButton *resetButton;
    QPushButton *undoButton;
    QPushButton *redoButton;
    QPushButton *grayscaleButton;
    QPushButton *blackWhiteButton;
    QPushButton *invertButton;
    QPushButton *mergeButton;
    QPushButton *flipButton;
    QPushButton *rotateButton;
    QPushButton *darkLightButton;
    QPushButton *frameButton;
    QPushButton *edgesButton;
    QPushButton *resizeButton;
    QPushButton *blurButton;
    QPushButton *infraredButton;
    QPushButton *purpleButton;
    QPushButton *tvFilterButton;
    
    Image originalImage;
    Image currentImage;
    bool hasImage;
    QString currentFilePath;
    
    // Undo/Redo system
    std::stack<Image> undoStack;
    std::stack<Image> redoStack;
    static const int MAX_UNDO_STEPS = 20; // Limit memory usage
    
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

#include "simple_qt_app.moc"
