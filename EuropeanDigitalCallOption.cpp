#include "EuropeanDigitalCallOption.h"

double EuropeanDigitalCallOption::payoff(double final_price) const {
    return final_price >= _strike ? 1.0 : 0.0;
}

OptionType EuropeanDigitalCallOption::GetOptionType() const {
    return type;
}

