#pragma once
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

	// Destructeur virtuel pour une bonne gestion des objets dérivés
	virtual ~option() {}

};

