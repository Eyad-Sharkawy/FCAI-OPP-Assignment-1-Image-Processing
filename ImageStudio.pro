# Image Studio v2.0.0 - Qt Project File (qmake)
# 
# This qmake project file defines the build configuration for Image Studio
# using Qt's qmake build system. It configures the project to use C++20,
# Qt 6, and includes all necessary source files and dependencies.
#
# Note: This is the legacy build system. CMake is the recommended build system.
#
# Author: Image Studio Development Team
# Institution: Faculty of Computers and Artificial Intelligence, Cairo University
# Version: 2.0.0
# Date: October 13, 2025

QT += core widgets

CONFIG += c++20

TARGET = ImageStudio
TEMPLATE = app

SOURCES += src/gui/image_studio.cpp \
           src/core/ImageFilters.cpp \
           src/core/Image_Class.cpp

HEADERS += src/core/Image_Class.h \
           src/core/ImageFilters.h

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
