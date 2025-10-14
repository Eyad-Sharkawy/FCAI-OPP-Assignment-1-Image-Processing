# Image Studio v3.0.1 - CMake Build Configuration
# 
# This CMake configuration file defines the build system for Image Studio,
# a Qt-based image processing application. It configures the project to use
# C++20, Qt 6, and includes all necessary source files and dependencies.
#
# Author: Image Studio Development Team
# Institution: Faculty of Computers and Artificial Intelligence, Cairo University
# Version: 3.0.1
# Date: October 13, 2025

cmake_minimum_required(VERSION 3.20)
project(ImageStudio VERSION 3.0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Enable Qt's MOC, UIC, and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(src/core)
include_directories(src/core/image)
include_directories(src/core/filters)
include_directories(src/core/history)
include_directories(src/core/io)
include_directories(third_party/stb)

# Source files
set(SOURCES
    src/gui/image_studio.cpp
    src/core/filters/ImageFilters.cpp
    src/core/image/Image_Class.cpp
)

# Header files
set(HEADERS
    src/core/image/Image_Class.h
    src/core/filters/ImageFilters.h
    src/core/history/HistoryManager.h
    src/core/io/ImageIO.h
)

# UI files
set(UI_FILES
    src/gui/mainwindow.ui
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_FILES})

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} 
    Qt6::Core 
    Qt6::Widgets
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Windows specific settings
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wno-missing-field-initializers
)
