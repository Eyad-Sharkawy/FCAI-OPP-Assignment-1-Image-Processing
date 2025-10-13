QT += core widgets

CONFIG += c++20

TARGET = ImageStudio
TEMPLATE = app

SOURCES += src/gui/image_studio.cpp

HEADERS += src/core/Image_Class.h

FORMS += src/gui/mainwindow.ui

# Include paths for headers and third-party libraries
INCLUDEPATH += src/core \
               third_party/stb

QMAKE_CXXFLAGS += -std=c++20

# Disable warnings for STB library
QMAKE_CXXFLAGS += -Wno-missing-field-initializers

# Windows: embed executable icon if .ico exists
win32:exists(assets/icon.ico) {
    RC_ICONS = assets/icon.ico
}
