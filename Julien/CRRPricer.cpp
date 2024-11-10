#include"CRRPricer.h"
#include<stdexcept>
using namespace std;

CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)
{
	_option = option;
	_depth = depth;
	_asset_price = asset_price;
	_up = up;
	_down = down;
	_interest_rate = interest_rate;

	//if (_down >= 1 + _interest_rate || _up <= 1 + _interest_rate)
	//{
	//	throw invalid_argument("Présence d'arbitrage");
	//}

	_tree.setDepth(_depth);
}

void CRRPricer::compute()
{
	double q = (_interest_rate - _down) / (_up - _down); //risk-neutral proba

	for (int i = 0; i < _depth; i++)
	{
		double price_last_node = _asset_price * pow(1 + _up, i) * pow(1 + _down, _depth - i); //refaire sans pow 1ère formule cours
		_tree.setNode(_depth, i, _option->payoff(price_last_node));
	}

	for (int n = _depth - 1; n >= 0; --n) {
		for (int i = 0; i <= n; ++i) 
		{
			double node_value = (q * _tree.getNode(n + 1, i + 1) + (1 - q) * _tree.getNode(n + 1, i)) / (1 + _interest_rate); //2ème formule cours
			_tree.setNode(n, i, node_value);
		}
	}
}

double CRRPricer::operator()(bool method) 
{
	if (!method)
	{
		compute();
		return _tree.getNode(0, 0);
	}
	else
	{
		double q = (_interest_rate - _down) / (_up - _down);
		double option_price = 0;

		for (int i = 0; i <= _depth; ++i) {
			double proba_binomial = exp(lgamma(_depth + 1) - lgamma(i + 1) - lgamma(_depth - i + 1))
				* pow(q, i) * pow(1 - q, _depth - i);
			double final_price = _asset_price * pow(1 + _up, i) * pow(1 + _down, _depth - i); //même formule qu'utilisé precdemment
			option_price += proba_binomial * _option->payoff(final_price);
		}

		return option_price / pow(1 + _interest_rate, _depth);
	}
}
	//revoir distinction de cas
