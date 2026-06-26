#pragma once
#include "CommandVisitor.h"
#include "IUndoAction.h"
#include "Flight.h"
#include "Runway.h"
#include "Passenger.h"
#include "Dispatcher.h"
#include "AirportAuthority.h"
#include "Engine.h"

class FreeRunwayUndoAction : public IUndoAction {
private:
    std::string flightID;
    std::string runwayID;
    std::string airlineName;
    Flight::Status prevFlightStatus;
    double airlineRevenueAdded;
    double airportRevenueAdded;
    int healthDeducted;
public:
    FreeRunwayUndoAction(const std::string& fID, const std::string& rID, const std::string& aName,
        Flight::Status fStatus, double airlineRevenue, double airportRevenue, int health);
    void undo() override;
};

class FreeRunwayCommand : public CommandVisitor {
private:
    std::string runwayID;
public:
    FreeRunwayCommand(const std::string& runwayID);

    void visit(Dispatcher& d) override;
};