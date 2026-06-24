#pragma once
#include "CommandVisitor.h"
#include "IUndoAction.h"
#include "Flight.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include "Engine.h"

class DelayFlightUndoAction : public IUndoAction {
private:
    std::string flightID;
    Flight::Status prevStatus;
public:
    DelayFlightUndoAction(const std::string& fID, Flight::Status status);
    void undo() override;
};

class DelayFlightCommand : public CommandVisitor {
private:
    std::string flightID;
public:
    DelayFlightCommand(const std::string& flightID);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};