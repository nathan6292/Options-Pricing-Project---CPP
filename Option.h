#pragma once
#include <vector>

class Option
{
private: 
	double _expiry;

public:
	double getExpiry() const;
	virtual double payoff(double) const = 0;
	double payoffPath(std::vector<double>) const; 
	Option(double);
	virtual bool isAsianOption() const; 
	virtual bool isAmericanOption() const;
};

