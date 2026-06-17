#pragma once

class Passenger;
class AirportAuthority;
class Dispatcher;

class UserVisitor {
public:
	virtual void visit(Passenger& p) = 0;
	virtual void visit(AirportAuthority& a) = 0;
	virtual	void visit(Dispatcher& a) = 0;
};