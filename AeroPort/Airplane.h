#pragma once
#include <iostream>
class Airplane {
protected:
	static size_t nextID;
	size_t ID;
	std::string model;
	size_t health = 100;
public:
	Airplane(const std::string& model);
	virtual ~Airplane() = default;

	virtual std::string info() const = 0;
	virtual size_t getRequiredRunwayLength() const = 0;
	virtual bool requiresVIP() const = 0;
	virtual bool requiresHeavyDuty() const = 0;
	virtual void decreaseHealthAfterFlight() = 0;

	virtual std::unique_ptr<Airplane> clone() const = 0;

	size_t getID() const;
	std::string getModel() const;
	size_t getHealth() const;
};
