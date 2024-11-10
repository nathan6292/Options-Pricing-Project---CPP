#pragma once
#include<iostream>
#include"EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption
{
public:
	EuropeanDigitalCallOption(double, double);
	optionType GetOptionType()const override;
};
