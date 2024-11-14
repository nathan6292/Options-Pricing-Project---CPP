#pragma once
#include <vector>

class option
{
private :
	double _expiry;
public:
	option(double expiry): _expiry(expiry) {}

	// Getter pour l'expiration
	double getExpiry() const {
		return _expiry;
	}

	// Méthode purement virtuelle pour représenter la fonction de paiement
	virtual double payoff(double underlyingPrice) const = 0; // le =0 permet de dire que c'est une virtuelle pure

	// New virtual method for path-dependent payoff, default to last element
	virtual double payoffPath(const std::vector<double>& pathPrices) const {
		return payoff(pathPrices.back());
	}

	virtual bool isAsianOption() const {
		return false;
	}

	virtual bool isAmericanOption() const
	{
		return false;
	}
	// Destructeur virtuel pour une bonne gestion des objets dérivés
	virtual ~option() {}

};

