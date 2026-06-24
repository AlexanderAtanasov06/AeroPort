#pragma once
#include <string>

class IWeatherObserver {
public:
    virtual void onWeatherChange(const std::string& weather) = 0;
    virtual ~IWeatherObserver() = default;
};