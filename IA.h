#ifndef IA_H
#define IA_H

#include"Joueur.h"
#include<iostream>

class IA : public Joueur
{
public:
	IA()
	{
		std::cout << "IA par defaut" << std::endl;
		this->r = Raquette(true, 60, 300);
		this->score = 0;
		this->nbPoint = 0;
		this->nbRetour = 0;
	};
	explicit IA(IA&& autre) : Joueur(autre){};
	~IA(){};
	inline void bougerRaquette(float temps, int by){
		int velocite = this->r.getVelocite();
		int sens = (by < this->r.getY() + this->r.getLongueur() / 2) ? -1 : 1;
		if (r.getY() + (r.getLongueur() / 2) - 20 + 10 < by) sens = 1;
		else if (r.getY() + (r.getLongueur() / 2) - 20 - 10 > by) sens = -1;
		else sens = 0;
		if (sens != 0){
			int coll = 0;
			coll = collisionAvecMur();
			if (coll != sens){
				this->direction = sens;
				this->r.setY(float(velocite) * temps * float(sens));
			}
		}
	}

private:
};
#endif // !IA_H
