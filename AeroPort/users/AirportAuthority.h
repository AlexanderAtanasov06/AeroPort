#pragma once
#include "User.h"

class AirportAuthority : public User {
private:
	AirportAuthority();
public:
	static std::shared_ptr<AirportAuthority> getInstance();

	AirportAuthority(const AirportAuthority&) = delete;
	AirportAuthority& operator=(const AirportAuthority&) = delete;

	void help() const override;
	void viewProfile() const override;

	void accept(CommandVisitor& visitor) override;
	void accept(UserVisitor& visitor) override;

};