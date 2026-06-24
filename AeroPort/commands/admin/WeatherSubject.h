#pragma once
#include "IWeatherObserver.h"
#include <memory>

class WeatherSubject {
public:
    virtual void addObserver(std::shared_ptr<IWeatherObserver> observer) = 0;
    virtual void notifyObservers(const std::string& weather) = 0;
    virtual ~WeatherSubject() = default;
};