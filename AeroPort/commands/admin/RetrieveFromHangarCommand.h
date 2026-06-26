#pragma once
#include "Engine.h"
#include "CommandVisitor.h"

class RetrieveFromHangarCommand : public CommandVisitor {
    size_t aircraftID;
public:
    RetrieveFromHangarCommand(size_t aircraftID);

    void visit(AirportAuthority& a) override;
};
