#pragma once
#include "Engine.h"
#include "CommandVisitor.h"
#include "Hangar.h"

class BuildHangarCommand : public CommandVisitor{
	std::string commandLine;
public:
	BuildHangarCommand(const std::string& commandLine);

	void visit(Passenger& p) override;
	void visit(Dispatcher& d) override;
	void visit(AirportAuthority& a) override;
};