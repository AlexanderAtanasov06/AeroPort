#pragma once
#include "CommandVisitor.h"

class SetWeatherCommand : public CommandVisitor {
public:
    explicit SetWeatherCommand(const std::string& commandLine);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;

private:
    std::string commandLine;
};