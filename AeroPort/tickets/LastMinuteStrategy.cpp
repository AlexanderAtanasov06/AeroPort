#include "LastMinuteStrategy.h"

double LastMinuteStrategy::calculatePrice(double basePrice) const {
    return basePrice * 0.5;
}

double LastMinuteStrategy::getRefundAmount(double paidPrice) const {
    return 0;
}

bool LastMinuteStrategy::isRefundable() const {
    return false;
}

double LastMinuteStrategy::getFreeBaggage() const {
    return 0;
}

std::string LastMinuteStrategy::getName() const
{
    return "LastMinute";
}
