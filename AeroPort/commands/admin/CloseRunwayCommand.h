#pragma once
#include "Engine.h"
#include "CommandVisitor.h"

class CloseRunwayCommand : public CommandVisitor {
	std::string runwayID;
public:
	CloseRunwayCommand(const std::string& id);

	void visit(AirportAuthority& a) override;
};