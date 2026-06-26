#pragma once
#include "Engine.h"
#include "CommandVisitor.h"
#include "AirplaneFactory.h"

class BuyAircraftCommand : public CommandVisitor {
    std::string airlineName;
    std::string type;
    std::string model;
    double capacityOrTonnage;
    static constexpr double AIRCRAFT_PRICE = 10000.0;
public:
    BuyAircraftCommand(const std::string& airlineName, const std::string& type,
        const std::string& model, double capacityOrTonnage);

    void visit(AirportAuthority& a) override;
};