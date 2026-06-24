#include "Airplane.h"

size_t Airplane::nextID = 1;

Airplane::Airplane(const std::string& model) : ID(nextID), model(model) {
	nextID++;
}

void Airplane::repair() {
	health = 100;
}

void Airplane::increaseHealth(double health) {
	if (health <=0 ) {
		throw std::invalid_argument("[Error] Health must be a positive number!");
	}
	this->health += health;
	if (this->health >= 100) {
		this->health = 100;
	}
}

bool Airplane::isHealthy() const
{
	if (health > 20)
	{
		return true;
	}
	return false;
}

size_t Airplane::getID() const {
	return ID;
}

std::string Airplane::getModel() const {
	return model;
}

size_t Airplane::getHealth() const {
	return health;
}
