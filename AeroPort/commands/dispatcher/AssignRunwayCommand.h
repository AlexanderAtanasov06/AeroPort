#pragma once
#include "CommandVisitor.h"
#include "IUndoAction.h"
#include "Flight.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include "Engine.h"

class AssignRunwayUndoAction : public IUndoAction {
private:
    std::string flightID;
    std::string runwayID;
    Flight::Status prevStatus;
public:
    AssignRunwayUndoAction(const std::string& fID, const std::string& rID, Flight::Status status);
    void undo() override;
};

class AssignRunwayCommand : public CommandVisitor {
private:
    std::string flightID;
    std::string runwayID;
public:
    AssignRunwayCommand(const std::string& flightID, const std::string& runwayID);

    void visit(Dispatcher& d) override;
};