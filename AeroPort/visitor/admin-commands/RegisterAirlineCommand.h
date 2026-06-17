#pragma once
#include "Engine.h"
#include "CommandVisitor.h"

class RegisterAirlineCommand : public CommandVisitor {
    std::string name;
    double balance;
public:
    RegisterAirlineCommand(const std::string& name, double balance);

    void visit(Passenger& p) override;
    void visit(Dispatcher& d) override;
    void visit(AirportAuthority& a) override;
};