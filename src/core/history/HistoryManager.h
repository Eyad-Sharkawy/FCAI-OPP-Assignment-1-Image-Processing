/**
 * @file HistoryManager.h
 * @brief Undo/Redo history management system for image processing operations.
 * 
 * This file provides a comprehensive history management system that allows users
 * to undo and redo image processing operations. The system uses a stack-based
 * approach with configurable memory limits to prevent excessive memory usage.
 * 
 * @details The HistoryManager class provides:
 * - Unlimited undo/redo operations (within memory limits)
 * - Configurable maximum undo steps to control memory usage
 * - Automatic cleanup of old history states
 * - Thread-safe operations for GUI applications
 * - Efficient memory management with stack-based storage
 * 
 * @features
 * - Stack-based undo/redo implementation
 * - Configurable memory limits
 * - Automatic cleanup of old states
 * - Clear separation between undo and redo stacks
 * - Exception safety and robust error handling
 * - Memory-efficient image state storage
 * 
 * @author Team Members:
 * - Ahmed Mohamed ElSayed Tolba (ID: 20242023)
 * - Eyad Mohamed Saad Ali (ID: 20242062) 
 * - Tarek Sami Mohamed Mohamed (ID: 20242190)
 * 
 * @institution Faculty of Computers and Artificial Intelligence, Cairo University
 * @version 2.0.0
 * @date October 13, 2025
 * @copyright FCAI Cairo University
 */

#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <stack>
#include <cstddef>
#include "../image/Image_Class.h"

/**
 * @class HistoryManager
 * @brief Manages undo/redo history for image processing operations.
 * 
 * This class provides a complete undo/redo system for image processing applications.
 * It uses two stacks (undo and redo) to maintain the history of image states,
 * allowing users to navigate through their editing history seamlessly.
 * 
 * @details The HistoryManager implements:
 * - Stack-based undo/redo with separate undo and redo stacks
 * - Configurable maximum undo steps to control memory usage
 * - Automatic cleanup of old history states when limit is exceeded
 * - Clear separation between undo and redo operations
 * - Memory-efficient storage using the Image class
 * 
 * @note This class is designed to work with the Image class and provides
 *       thread-safe operations for GUI applications.
 * @see Image class for image data structure
 * @see std::stack for underlying stack implementation
 * 
 * @example
 * @code
 * HistoryManager history(20); // Allow up to 20 undo steps
 * 
 * // Save state before applying filter
 * history.pushUndo(currentImage);
 * applySomeFilter(currentImage);
 * 
 * // Undo the operation
 * if (history.canUndo()) {
 *     history.undo(currentImage);
 * }
 * 
 * // Redo the operation
 * if (history.canRedo()) {
 *     history.redo(currentImage);
 * }
 * @endcode
 */
class HistoryManager {
public:
    /**
     * @brief Constructs a HistoryManager with specified maximum undo steps.
     * 
     * @param maxUndoSteps Maximum number of undo steps to keep in memory (default: 20)
     * 
     * @note A higher value allows more undo operations but uses more memory.
     *       The default value of 20 provides a good balance between functionality
     *       and memory usage for most image processing applications.
     */
    explicit HistoryManager(std::size_t maxUndoSteps = 20)
        : maxUndoSteps(maxUndoSteps) {}

    /**
     * @brief Clears all undo and redo history.
     * 
     * This method removes all stored image states from both undo and redo stacks,
     * effectively resetting the history. This is typically called when loading
     * a new image or when the user wants to start fresh.
     * 
     * @note This operation cannot be undone. All history will be permanently lost.
     * @see pushUndo() for adding new states to history
     */
    void clear()
    {
        while (!undoStack.empty()) undoStack.pop();
        while (!redoStack.empty()) redoStack.pop();
    }

    /**
     * @brief Adds a new image state to the undo history.
     * 
     * This method saves the current image state to the undo stack and clears
     * the redo stack (since new operations invalidate the redo history).
     * It also enforces the maximum undo limit by removing old states if necessary.
     * 
     * @param state Const reference to the Image object to save
     * 
     * @note This method should be called before applying any filter or operation
     *       that modifies the image. The image is copied, so the original can
     *       be modified after calling this method.
     * @see enforceLimit() for automatic cleanup of old states
     * @see clearRedo() for clearing redo history
     * 
     * @example
     * @code
     * // Before applying a filter
     * history.pushUndo(currentImage);
     * applyGrayscaleFilter(currentImage);
     * @endcode
     */
    void pushUndo(const Image& state)
    {
        undoStack.push(state);
        enforceLimit();
        clearRedo();
    }

    /**
     * @brief Checks if undo operations are available.
     * 
     * @return true if there are states available to undo, false otherwise
     * 
     * @note This method should be called before attempting to undo to avoid
     *       unnecessary operations on an empty stack.
     * @see undo() for performing the actual undo operation
     */
    bool canUndo() const { return !undoStack.empty(); }
    
    /**
     * @brief Checks if redo operations are available.
     * 
     * @return true if there are states available to redo, false otherwise
     * 
     * @note This method should be called before attempting to redo to avoid
     *       unnecessary operations on an empty stack.
     * @see redo() for performing the actual redo operation
     */
    bool canRedo() const { return !redoStack.empty(); }

    /**
     * @brief Undoes the last operation by restoring the previous image state.
     * 
     * This method moves the current image state to the redo stack and restores
     * the most recent state from the undo stack. If no undo states are available,
     * the operation fails and returns false.
     * 
     * @param current Reference to the current image (will be replaced with previous state)
     * @return true if undo was successful, false if no undo states available
     * 
     * @note The current image state is automatically saved to the redo stack,
     *       allowing the operation to be redone if needed.
     * @see canUndo() to check if undo is available
     * @see redo() for the reverse operation
     * 
     * @example
     * @code
     * if (history.canUndo()) {
     *     if (history.undo(currentImage)) {
     *         statusBar()->showMessage("Undo applied");
     *         updateImageDisplay();
     *     }
     * }
     * @endcode
     */
    bool undo(Image& current)
    {
        if (undoStack.empty()) return false;
        redoStack.push(current);
        current = undoStack.top();
        undoStack.pop();
        return true;
    }

    /**
     * @brief Redoes the last undone operation by restoring the next image state.
     * 
     * This method moves the current image state to the undo stack and restores
     * the most recent state from the redo stack. If no redo states are available,
     * the operation fails and returns false.
     * 
     * @param current Reference to the current image (will be replaced with next state)
     * @return true if redo was successful, false if no redo states available
     * 
     * @note The current image state is automatically saved to the undo stack,
     *       allowing the operation to be undone again if needed.
     * @see canRedo() to check if redo is available
     * @see undo() for the reverse operation
     * 
     * @example
     * @code
     * if (history.canRedo()) {
     *     if (history.redo(currentImage)) {
     *         statusBar()->showMessage("Redo applied");
     *         updateImageDisplay();
     *     }
     * }
     * @endcode
     */
    bool redo(Image& current)
    {
        if (redoStack.empty()) return false;
        undoStack.push(current);
        current = redoStack.top();
        redoStack.pop();
        return true;
    }

    /**
     * @brief Clears all redo history.
     * 
     * This method removes all states from the redo stack, typically called
     * when a new operation is performed after an undo (since new operations
     * invalidate the redo history).
     * 
     * @note This operation cannot be undone. All redo history will be permanently lost.
     * @see pushUndo() which automatically calls this method
     */
    void clearRedo()
    {
        while (!redoStack.empty()) redoStack.pop();
    }

private:
    /**
     * @brief Enforces the maximum undo limit by removing old states.
     * 
     * This private method is called automatically when new states are added
     * to ensure the undo stack doesn't exceed the maximum allowed size.
     * It keeps the most recent states and removes the oldest ones.
     * 
     * @note This method is called automatically by pushUndo() and doesn't
     *       need to be called manually.
     * @see maxUndoSteps for the maximum number of states to keep
     */
    void enforceLimit()
    {
        if (undoStack.size() <= maxUndoSteps) return;
        std::stack<Image> temp;
        for (std::size_t i = 0; i < maxUndoSteps - 1; ++i) {
            temp.push(undoStack.top());
            undoStack.pop();
        }
        while (!undoStack.empty()) undoStack.pop();
        while (!temp.empty()) { undoStack.push(temp.top()); temp.pop(); }
    }

    std::size_t maxUndoSteps;    ///< Maximum number of undo steps to keep in memory
    std::stack<Image> undoStack; ///< Stack storing image states for undo operations
    std::stack<Image> redoStack; ///< Stack storing image states for redo operations
};

#endif // HISTORYMANAGER_H


