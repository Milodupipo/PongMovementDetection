#ifndef Joueur_H
#define Joueur_H

#include"Raquette.h"

class Joueur
{
public:
	Joueur(){};
	explicit Joueur(const Joueur &j)
	{
		*this = j;
	};
	explicit Joueur(Joueur&& autre) : score(autre.score), nbPoint(autre.nbPoint), nbRetour(autre.nbRetour), direction(autre.direction), r(std::move(autre.r)) {};
	const Joueur& operator=(const Joueur &j){
		this->r = j.r;
		this->score = j.score;
		this->nbPoint = j.nbPoint;
		this->nbRetour = j.nbRetour;
		return *this;
	};
	~Joueur(){};
	inline const Raquette getRaquette() const{
		return this->r;
	};
	inline const Raquette& getRaquetteRef() const{
		return this->r;
	};
	inline const int collisionAvecMur(){
		if (r.getY() <= 0){
			return -1;
		}
		else if (r.getY() + r.getLongueur() >= 450){
			return 1;
		}
		return 0;
	};
	inline void bougerRaquette(const int &valeur){
		this->r.setY(valeur);
	};
	inline void modifierTailleRaquette(const int valeur){
		this->r.setLongueur(valeur);
	}
	inline void modifierTailleRaquette(const double valeur){
		this->r.modifierLongueur(valeur);
	}
	inline void modifierVelociteRaquette(const double valeur){
		this->r.modifierVelocite(valeur);
	}
	inline void setScore(const int valeur){
		this->score += valeur;
	};
	inline void setNbPoint(const int valeur){
		this->nbPoint += valeur;
	};
	inline const int getScore() const{
		return this->score;
	};
	inline const int getNbPoint() const{
		return this->nbPoint;
	};
	inline void setDirection(const int valeur){
		this->direction = valeur;
	}
	inline const int getDirection(){
		return this->direction;
	}
protected:
	Raquette r;
	int score;
	int nbPoint;
	int nbRetour;
	int direction;
};
#endif // !Joueur_H
