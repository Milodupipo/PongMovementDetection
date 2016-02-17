#ifndef Raquette_H
#define Raquette_H

const int VELOCITE_RAQ_MIN = 150;
const int VELOCITE_RAQ_MAX = 600;
const int LGR_MIN = 30;


class Raquette
{
public:
	Raquette(){};
	Raquette(const bool ia, const int taille, const int vitesse) : longueur(taille), velocite(vitesse)
	{
		this->y = 150;
		(ia) ? this->x = 565 : this->x = 20;
	};
	Raquette(const Raquette& raq){
		*this = raq;
	};
	explicit Raquette(Raquette&& autre) : longueur{ autre.longueur }, velocite{ autre.velocite }, y{ autre.y }, x{ autre.x }, direction{ autre.direction } {};
	const Raquette& operator=(const Raquette &r){
		this->longueur = r.longueur;
		this->velocite = r.velocite;
		this->y = r.y;
		this->x = r.x;
		this->direction = r.direction;
		return *this;
	};
	~Raquette(){};
	inline void setLongueur(int valeur){
		this->longueur = valeur;
	};
	inline void modifierLongueur(double valeur){
		int res;
		if ((res = this->longueur * valeur) > LGR_MIN)
			this->longueur = res;
	};
	inline void modifierVelocite(const double valeur){
		int res;
		if ((res = this->velocite * valeur) > VELOCITE_RAQ_MIN && this->velocite * valeur < VELOCITE_RAQ_MAX)
			this->velocite = res;
	};
	inline void setY(const double valeur){
		this->y += valeur;
	};
	inline const double getY() const{
		return this->y;
	};
	inline const int getX() const{
		return this->x;
	};
	inline const int getLongueur() const{
		return this->longueur;
	};
	inline const int getVelocite() const{
		return this->velocite;
	};
	inline const int getDirection() const{
		return this->direction;
	}
	inline void setDirection(const int valeur){
		this->direction = valeur;
	}
private:
	int longueur;
	// piyels/secondes
	int velocite;
	double y;
	double x;
	int direction;
};
#endif // !Raquette_H
