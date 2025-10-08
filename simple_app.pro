QT += core widgets

CONFIG += c++20

TARGET = ImageStudio
TEMPLATE = app

SOURCES += src/simple_qt_app.cpp

HEADERS += include/Image_Class.h

INCLUDEPATH += include

QMAKE_CXXFLAGS += -std=c++20

# Disable warnings for STB library
QMAKE_CXXFLAGS += -Wno-missing-field-initializers

# Windows: embed executable icon if .ico exists
win32:exists(assets/icon.ico) {
    RC_ICONS = assets/icon.ico
}
