#pragma once
class Option
{
private: 
	double _expiry;
public:
	double getExpiry() const;
	virtual double payoff(double) const = 0;
	Option(double);
};