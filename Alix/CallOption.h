#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption
{
public:
	CallOption(double, double);
	optionType GetOptionType() const override;
};