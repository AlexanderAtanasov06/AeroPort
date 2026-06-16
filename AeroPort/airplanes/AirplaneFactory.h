#pragma once
#include "PassengerPlane.h"
#include "CargoPlane.h"
#include "PrivateJet.h"
#include <memory>
#include <string>

class AirplaneFactory {
public:
    AirplaneFactory() = delete;

    static std::unique_ptr<Airplane> create(const std::string& type,
        const std::string& model,
        size_t capacityOrTonnage);
};