#pragma once
#include <memory>
#include <sstream>
#include <vector>
#include <print>
#include "CommandVisitor.h"
#include "AddFundsCommand.h"
#include "BuildRunwayCommand.h"
#include "BuildHangarCommand.h"
#include "CloseRunwayCommand.h"
#include "RegisterAirlineCommand.h"
#include "BuyAircraftCommand.h"
#include "CloneAircraftCommand.h"
#include "SendToHangarCommand.h"
#include "RetrieveFromHangarCommand.h"
#include "BookTicketCommand.h"
#include "ListFlightsCommand.h"
#include "ScheduleFlightCommand.h"
#include "CancelFlightCommand.h"
#include "UpgradeTicketCommand.h"
#include "AddBaggageCommand.h"
#include "CancelTicketCommand.h"
#include "AssignRunwayCommand.h"
#include "UndoCommand.h"
#include "FreeRunwayCommand.h"
#include "SetWeatherCommand.h"
#include "AirportReportCommand.h"
#include "DelayFlightCommand.h"
#include "AuditAirlineCommand.h"
#include "ListAirspaceCommand.h"
#include "MyTicketsCommand.h"
#include "ListRunwaysCommand.h"
#include "ListFleetCommand.h"
#include "FlightRevenueCommand.h"

class CommandFactory {
public:
	CommandFactory() = delete;
	static std::unique_ptr<CommandVisitor> create(const std::string& line);
};