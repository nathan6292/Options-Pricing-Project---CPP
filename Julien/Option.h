#pragma once
#include<iostream>
using namespace std;

class Option
{
public:
	double getExpiry() const;
	virtual double payoff(double) const=0; //attention hyper important de mettre = 0 (virtual pure) sinon obligation de definir payoff dans option.cpp
	Option(double);

private:
	double _expiry;
};
