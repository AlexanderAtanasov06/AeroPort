#pragma once
#include <print>
#include <stdexcept>
#include <algorithm>

class Passenger;
class Dispatcher;
class AirportAuthority;

class CommandVisitor {
public:
    virtual ~CommandVisitor() = default;
    virtual void visit(Passenger& p);
    virtual void visit(Dispatcher& d);
    virtual void visit(AirportAuthority& a);
};