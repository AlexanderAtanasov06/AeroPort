#pragma once
#include "CommandVisitor.h"

class UndoCommand : public CommandVisitor {
public:
    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};
