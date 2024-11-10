#pragma once
#include"BinaryTree.h"
#include"Option.h"


class CRRPricer
{
private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    BinaryTree<double> _tree;
public:
    CRRPricer(Option*, int, double, double, double, double);
    void compute();
    //double get(int, int) pas utile car deja get node dans binary tree
    double operator()(bool method = false);
};


