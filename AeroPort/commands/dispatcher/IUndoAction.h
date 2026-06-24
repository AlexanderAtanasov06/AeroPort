#pragma once

class IUndoAction {
public:
    virtual ~IUndoAction() = default;
    virtual void undo() = 0;
};
