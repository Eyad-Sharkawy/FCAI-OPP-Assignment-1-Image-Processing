/**
 * @file Image_Class.cpp
 * @brief Implementation of the Image class with STB library integration.
 * 
 * This file contains the implementation of the Image class, which serves as the
 * fundamental data structure for all image processing operations. The implementation
 * leverages the STB (Sean T. Barrett) library for robust image I/O operations.
 * 
 * @details The implementation includes:
 * - STB library integration for image loading and saving
 * - Memory management with RAII principles
 * - Safe pixel access with bounds checking
 * - Copy semantics with proper resource management
 * - Exception safety and comprehensive error handling
 * - Support for multiple image formats (PNG, JPEG, BMP, TGA)
 * 
 * @note This file includes the STB library implementation only once to avoid
 *       multiple definition errors. The STB library provides the underlying
 *       functionality for image I/O operations.
 * 
 * @author Original Authors:
 * - Shehab Diab
 * - Youssef Mohamed
 * - Nada Ahmed
 * - Dr. Mohamed El-Ramely (Supervisor)
 * 
 * @author Current Team:
 * - Ahmed Mohamed ElSayed Tolba (ID: 20242023)
 * - Eyad Mohamed Saad Ali (ID: 20242062) 
 * - Tarek Sami Mohamed Mohamed (ID: 20242190)
 * 
 * @institution Faculty of Computers and Artificial Intelligence, Cairo University
 * @version 2.0.0 (Enhanced with comprehensive documentation and Qt integration)
 * @date October 13, 2025
 * @copyright FCAI Cairo University
 */

// Include STB implementation only once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image/Image_Class.h"

// All the Image class method implementations will be here
// This file will include the STB implementation only once

