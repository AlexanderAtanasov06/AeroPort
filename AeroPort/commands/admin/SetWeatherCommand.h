#pragma once
#include "CommandVisitor.h"

class SetWeatherCommand : public CommandVisitor {
public:
    explicit SetWeatherCommand(const std::string& commandLine);

    void visit(AirportAuthority& a) override;

private:
    std::string commandLine;
};