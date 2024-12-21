#pragma once
#include "Option.h"
#include "optionType.h"

// Declaration of the class AmericanOption
class AmericanOption : public Option
{
	// Declaration of the private variables strike and type
private: 
	double _strike;

public: 
	// Declaration of the constructor with the parameters strike and expiry
	AmericanOption(double, double);

	// Declaration of the overrriden function isAmericanOption
	bool isAmericanOption() const override;

	// Defines AmericanCallOption and AmericanPutOption as friend classes to access the strike
	friend class AmericanCallOption;
	friend class AmericanPutOption;
};

