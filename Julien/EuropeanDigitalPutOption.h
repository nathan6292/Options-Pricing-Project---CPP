#pragma once
#include<iostream>
#include"EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption
{
public:
	EuropeanDigitalPutOption(double, double);
	optionType GetOptionType()const override;
};
