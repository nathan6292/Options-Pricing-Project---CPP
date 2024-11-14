#include "Option.h"

Option::Option(double expiry) : _expiry(expiry) {}

double Option::getExpiry() const {
	return _expiry;
}

double Option::payoffPath(std::vector<double> time) const {
	return payoff(time[time.size() - 1]);
}

bool Option::isAsianOption() const{
	return false; 
}

bool Option::isAmericanOption() const {
	return false; 
}


