#include "EuropeanDigitalPutOption.h"

double EuropeanDigitalPutOption::payoff(double final_price) const {
    return final_price <= _strike ? 1.0 : 0.0;
}

OptionType EuropeanDigitalPutOption::GetOptionType() const {
    return type;
}