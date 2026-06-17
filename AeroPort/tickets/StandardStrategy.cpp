#include "StandardStrategy.h"

double StandardStrategy::calculatePrice(double basePrice) const {
    return basePrice;
}

double StandardStrategy::getRefundAmount(double paidPrice) const {
    return paidPrice;
}

bool StandardStrategy::isRefundable() const {
    return true;
}

double StandardStrategy::getFreeBaggage() const {
    return 0;
}
