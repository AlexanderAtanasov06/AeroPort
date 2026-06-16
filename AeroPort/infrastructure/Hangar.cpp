#include "Hangar.h"

Hangar::Hangar(const std::string& id, size_t capacity, double fee) 
	: hangarID(id), capacity(capacity), repairFee(fee) {
}

void Hangar::addAircraft(std::shared_ptr<Airplane> plane) {
	if (isFull()) {
		throw std::logic_error("[Error] Hangar full!");
	}
	planes.push_back(plane);
}

size_t Hangar::getCapacity() const {
	return capacity;
}

double Hangar::getRepairFee() const {
	return repairFee;
}

const std::string& Hangar::getHangarID() const {
	return hangarID;
}

size_t Hangar::getCurrentCount() const {
	return planes.size();
}

bool Hangar::isFull() const {
	return planes.size() >= capacity;
}

std::shared_ptr<Airplane> Hangar::findAirplane(size_t id) {
	auto it = std::find_if(planes.begin(), planes.end(), [&id](const auto& plane) {
		return plane->getID() == id;
		});
	if (it != planes.end()) {
		return *it;
	}
	return nullptr;
}

const std::vector<std::shared_ptr<Airplane>> Hangar::getPlanes() const {
	return planes;
}


