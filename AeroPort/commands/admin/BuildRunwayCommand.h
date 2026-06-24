#pragma once
#include "CommandVisitor.h"
#include <string>
#include <sstream>
#include "Engine.h"

class BuildRunwayCommand : public CommandVisitor{
	std::string commandLine;
public:
	BuildRunwayCommand(const std::string& commandLine);

	void visit(Passenger& p) override;
	void visit(Dispatcher& d) override;
	void visit(AirportAuthority& a) override;
};