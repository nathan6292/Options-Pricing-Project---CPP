#pragma once
#include "Option.h"
#include "BinaryTree.h"
#include "BlackScholesPricer.h"
#include "AmericanOption.h"
class CRRPricer
{
public:
	CRRPricer(Option*, int, double, double, double, double);
	CRRPricer(Option*, int, double, double, double);
	void compute();
	double get(int, int);
	double operator()(bool closed_form = false);
	bool getExercise(int, int);
private:
	Option* option;
	int depth;
	double asset_price;
	double up;
	double down;
	double interest_rate;
	BinaryTree<double> tree;
	BinaryTree<bool> tree_bool;
};