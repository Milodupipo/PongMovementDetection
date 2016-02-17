#ifndef Bonus_H
#define Bonus_H

#include<iostream>
#include"Balle.h"
#include<map>
#include<string>
#include<functional>

class Bonus
{
public:
	Bonus(){};
	Bonus(int x, int y, int effet) : x(x), y(y), effet(effet)
	{
		this->mapEffet.insert(std::make_pair(0, std::mem_fun(&Bonus::agrandirRaquette)));
		this->mapEffet.insert(std::make_pair(1, std::mem_fun(&Bonus::rapetissirRaquette)));
		this->mapEffet.insert(std::make_pair(2, std::mem_fun(&Bonus::accelererRaquette)));
		this->mapEffet.insert(std::make_pair(3, std::mem_fun(&Bonus::ralentirRaquette)));
		this->mapEffet.insert(std::make_pair(4, std::mem_fun(&Bonus::accelererBalle)));
		this->mapEffet.insert(std::make_pair(5, std::mem_fun(&Bonus::agrandirBalle)));
		this->mapEffet.insert(std::make_pair(6, std::mem_fun(&Bonus::rapetissirBalle)));
		switch(effet){
		case 0:
		case 2:
		case 5:
			this->r = 173;
			this->g = 207;
			this->bl = 79;
			break;
		case 1:
		case 3:
		case 4:
		case 6:
			this->r = 185;
			this->g = 18;
			this->bl = 27;
			break;
		}
	};
	Bonus(int x, int y, int effet, int r, int g, int bl) : x(x), y(y), effet(effet), r(r), g(g), bl(bl)
	{
		this->mapEffet.insert(std::make_pair(0, std::mem_fun(&Bonus::agrandirRaquette)));
		this->mapEffet.insert(std::make_pair(1, std::mem_fun(&Bonus::rapetissirRaquette)));
		this->mapEffet.insert(std::make_pair(2, std::mem_fun(&Bonus::accelererRaquette)));
		this->mapEffet.insert(std::make_pair(3, std::mem_fun(&Bonus::ralentirRaquette)));
		this->mapEffet.insert(std::make_pair(4, std::mem_fun(&Bonus::accelererBalle)));
		this->mapEffet.insert(std::make_pair(5, std::mem_fun(&Bonus::agrandirBalle)));
		this->mapEffet.insert(std::make_pair(6, std::mem_fun(&Bonus::rapetissirBalle)));
	};
	Bonus(const Bonus &b){
		*this = b;
	};
	explicit Bonus(Bonus&& autre) : x(autre.x), y(autre.y), effet(autre.effet), r(autre.r), g(autre.g), bl(autre.bl), j(std::move(autre.j)), b(std::move(autre.b)), mapEffet(std::move(autre.mapEffet)) {};
	const Bonus& operator=(const Bonus &bo){
		this->x = bo.x;
		this->y = bo.y;
		this->effet = bo.effet;
		this->r = bo.r;
		this->g = bo.g;
		this->bl = bo.bl;
		this->mapEffet = bo.mapEffet;
		this->j = j;
		return *this;
	};
	~Bonus(){};
	//applique le bon effet en fonction du int passé en param lors de la construction
	inline void appliquerEffet(Joueur &j, Balle &b){
		this->j = j;
		this->b = b;
		// /!\ mapEffet ne se remplit pas, l'iterateur ne pointe sur rien !
		std::map<int, std::mem_fun_t<void, Bonus> >::iterator it = this->mapEffet.find(this->effet);
		//appel de la bonne méthode
		if (it != mapEffet.end()){
			it->second(this);
			j = this->j;
			b = this->b;
		}
	};
	inline const bool collisionAvecBonus(Balle b){
		float Radius1 = 40;
		float Radius2 = b.getDiametre();
		float xd = this->x - b.getX();
		float yd = this->y - b.getY();
		return sqrt(xd * xd + yd * yd) <= Radius1 + Radius2;
		return false;
	}
	inline const double getY(){
		return this->y;
	};
	inline const int getX(){
		return this->x;
	};
	inline const int getEffet(){
		return this->effet;
	};
	inline const int getR() const{
		return this->r;
	}
	inline const int getG() const{
		return this->g;
	}
	inline const int getB() const{
		return this->bl;
	}
private:
	//quelques effets implémentés pour les bonus

	inline void agrandirRaquette(){
		this->j.modifierTailleRaquette(1.2);
	}
	inline void rapetissirRaquette(){
		this->j.modifierTailleRaquette(0.80);
	}
	inline void accelererRaquette(){
		this->j.modifierVelociteRaquette(1.10);
	}
	inline void ralentirRaquette(){
		this->j.modifierVelociteRaquette(0.90);
	}
	inline void accelererBalle(){
		this->b.modifierVelocite(1.10);
	}
	inline void agrandirBalle(){
		this->b.modifierTaille(1.25);
	}
	inline void rapetissirBalle(){
		this->b.modifierTaille(0.75);
	}

	int x;
	int y;
	int effet;
	int r, g, bl;
	Joueur j;
	Balle b;
	std::map<int, std::mem_fun_t<void, Bonus> > mapEffet;
};
#endif // !Bonus_H