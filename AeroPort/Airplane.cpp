#include "Airplane.h"

size_t Airplane::nextID = 1;

Airplane::Airplane(const std::string& model) : ID(nextID), model(model) {
	nextID++;
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
