#include "VIPStrategy.h"

double VIPStrategy::calculatePrice(double basePrice) const {
    return basePrice * 2;
}

double VIPStrategy::getRefundAmount(double paidPrice) const {
    return paidPrice;
}

bool VIPStrategy::isRefundable() const {
    return true;
}

double VIPStrategy::getFreeBaggage() const {
    return 20;
}

std::string VIPStrategy::getName() const
{
    return "VIP";
}
