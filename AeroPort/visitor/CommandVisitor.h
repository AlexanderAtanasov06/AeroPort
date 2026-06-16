#pragma once
#include <print>
#include <stdexcept>
#include "Runway.h"

class Passenger;
class Dispatcher;
class AirportAuthority;

class CommandVisitor {
public:
    virtual ~CommandVisitor() = default;
    virtual void visit(Passenger& p) = 0;
    virtual void visit(Dispatcher& d) = 0;
    virtual void visit(AirportAuthority& a) = 0;
};