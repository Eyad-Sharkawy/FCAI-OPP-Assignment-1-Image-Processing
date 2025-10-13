#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <stack>
#include <cstddef>
#include "../image/Image_Class.h"

class HistoryManager {
public:
    explicit HistoryManager(std::size_t maxUndoSteps = 20)
        : maxUndoSteps(maxUndoSteps) {}

    void clear()
    {
        while (!undoStack.empty()) undoStack.pop();
        while (!redoStack.empty()) redoStack.pop();
    }

    void pushUndo(const Image& state)
    {
        undoStack.push(state);
        enforceLimit();
        clearRedo();
    }

    bool canUndo() const { return !undoStack.empty(); }
    bool canRedo() const { return !redoStack.empty(); }

    bool undo(Image& current)
    {
        if (undoStack.empty()) return false;
        redoStack.push(current);
        current = undoStack.top();
        undoStack.pop();
        return true;
    }

    bool redo(Image& current)
    {
        if (redoStack.empty()) return false;
        undoStack.push(current);
        current = redoStack.top();
        redoStack.pop();
        return true;
    }

    void clearRedo()
    {
        while (!redoStack.empty()) redoStack.pop();
    }

private:
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

    std::size_t maxUndoSteps;
    std::stack<Image> undoStack;
    std::stack<Image> redoStack;
};

#endif // HISTORYMANAGER_H


