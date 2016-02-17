#ifndef Humain_H
#define Humain_H

#include"Joueur.h"
#include<iostream>

class Humain : public Joueur
{
public:
	Humain()
	{
		std::cout << "Humain par defaut" << std::endl;

		this->r = Raquette(false, 60, 300);
		this->score = 0;
		this->nbPoint = 0;
		this->nbRetour = 0;
	};
	Humain(const Humain& h)
	{
		*this = h;
	};
	explicit Humain(Humain&& autre) : Joueur(autre){};
	const Humain& operator=(const Humain &h){
		this->r = h.r;
		this->score = h.score;
		this->nbPoint = h.nbPoint;
		this->nbRetour = h.nbRetour;
		return *this;
	};
	~Humain(){};

private:
};
#endif // !Humain_H
