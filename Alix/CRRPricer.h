#pragma once
#include "Option.h"
#include "BinaryTree.h"
class CRRPricer
{
public:
	CRRPricer(Option*, int, double, double, double, double);
    void compute();
    double operator()();
    double get(int n, int i);
private :
	Option* option;
	int depth;
	double asset_price;
	double up;
	double down;
	double interest_rate;
	BinaryTree<Option*> tree;
    bool closed_form;
};
