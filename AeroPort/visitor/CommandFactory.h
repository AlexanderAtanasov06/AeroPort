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

class CommandFactory {
private:
	std::vector<std::string> splitArguments(const std::string& line);
public:
	CommandFactory() = delete;
	static std::unique_ptr<CommandVisitor> create(const std::string& line);
};