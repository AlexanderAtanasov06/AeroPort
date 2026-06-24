#pragma once
#include "Engine.h"
#include "CommandVisitor.h"

class SendToHangarCommand : public CommandVisitor {
    size_t aircraftID;
    std::string hangarID;
public:
    SendToHangarCommand(size_t aircraftID, const std::string& hangarID);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};
