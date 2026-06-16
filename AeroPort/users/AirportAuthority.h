#pragma once
#include "User.h"

class AirportAuthority : public User {
private:
	AirportAuthority();
public:
	static AirportAuthority& getInstance();
	//void handleCommand()
	void help() const override;
	void viewProfile() const override;

	void accept(CommandVisitor& visitor) override;

};