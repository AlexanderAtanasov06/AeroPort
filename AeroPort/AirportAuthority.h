#pragma once
#include "User.h"

class AirportAuthority : public User {
private:
	AirportAuthority();
public:
	static AirportAuthority& getInstance();
	//void handleCommand()
	void help() const override;
};