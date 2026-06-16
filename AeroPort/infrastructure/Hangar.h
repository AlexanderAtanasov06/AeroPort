#pragma once
#include "Airplane.h"
#include <vector>

class Hangar {
	std::string hangarID;
	size_t capacity;
	double repairFee;
	std::vector<std::shared_ptr<Airplane>> planes;
public:
	Hangar(const std::string& id, size_t capacity, double fee);

	void addAircraft(std::shared_ptr<Airplane> plane);

	size_t getCapacity() const;
	double getRepairFee() const;
	const std::string& getHangarID() const;	
	size_t getCurrentCount() const;
	bool isFull() const;

	std::shared_ptr<Airplane> findAirplane(size_t id);
	const std::vector<std::shared_ptr<Airplane>> getPlanes() const;

};