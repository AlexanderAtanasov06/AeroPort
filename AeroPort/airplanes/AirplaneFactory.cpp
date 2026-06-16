#include "AirplaneFactory.h"

std::unique_ptr<Airplane> AirplaneFactory::create(const std::string& type,
    const std::string& model,
    size_t capacityOrTonnage) {
    if (type == "PassengerPlane") {
        return std::make_unique<PassengerPlane>(model, capacityOrTonnage);
    }
    if (type == "CargoPlane") {
        return std::make_unique<CargoPlane>(model, capacityOrTonnage);
    }
    if (type == "PrivateJet") {
        return std::make_unique<PrivateJet>(model);
    }
    return nullptr;
}