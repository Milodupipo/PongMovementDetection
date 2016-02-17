#ifndef Balle_H
#define Balle_H

#include<stdlib.h>     /* srand, rand */
#include<time.h>       /* time */
#include<math.h>
#include"Humain.h"
#include"IA.h"
#include <fstream>

const int VELOCITE_BALLE_MIN = 300;
const int VELOCITE_BALLE_MAX = 1000;
const int TAILLE_MIN = 4;
const int TAILLE_MAX = 26;

using namespace std;

class Balle
{
public:
	Balle(){};
	Balle(int diametre, int x, int y, int vitesse) : diametre(diametre), x(x), y(y), velocite(vitesse)
	{
		srand(time(nullptr));
		double aleat = rand() % 60 + 20;
		this->vecx = aleat / 100;
		this->vecy = 1 - this->vecx;
	};
	Balle(const Balle &raq){
		*this = raq;
	};
	explicit Balle(Balle&& autre) : x{ autre.x }, y{ autre.y }, diametre{ autre.diametre }, vecx{ autre.vecx }, vecy{ autre.vecy }, velocite{ autre.velocite } {};
	~Balle(){};
	inline void rebondVertical(){
		this->vecx *= -1;
	}
	inline void rebondHorizontal(){
		this->vecy *= -1;
	}
	/* /!\ deux méthodes de collisions à factoriser lorsqu'elles auront un type mere commun
	* 0 pas de collision, 1 rebond vertical, -1 rebond horizontal
	*/
	inline int collisionAvecBalle(const Humain &j){
		if (j.getRaquette().getY() <= this->y + this->diametre * 2 && ((j.getRaquette().getY() + j.getRaquette().getLongueur()) >= this->y)){
			if (j.getRaquette().getX() + 20 > this->x && j.getRaquette().getX() < this->x){
				return 1;
			}
		}
		return 0;
	};
	inline int collisionAvecBalle(const IA &ia){
		if (ia.getRaquette().getY() <= this->y + this->diametre && ((ia.getRaquette().getY() + ia.getRaquette().getLongueur()) >= this->y)){
			if (this->x + this->diametre * 2 >= ia.getRaquette().getX() && ia.getRaquette().getX() > this->x){
				return 1;
			}
		}
		return 0;
	};
	inline int collisionMurVertical(){
		if (this->x <= 0){
			return -1;
		}
		else if (this->x >= 600 - this->diametre * 2){
			return 1;
		}
		return 0;
	}
	inline bool collisionMurHorizontal(){
		if (this->y > 0 && this->y < 450 - this->diametre){
			return false;
		}
		return true;
	};
	inline void setTaille(const int diametre){
		this->diametre = diametre;
	};
	inline void setY(const double valeur){
		this->y += valeur;
	};
	inline void setX(const double valeur){
		this->x += valeur;
	};
	inline const double getX() const{
		return this->x;
	};
	inline const double getY() const{
		return this->y;
	};
	inline const int getDiametre() const{
		return this->diametre;
	};
	inline const double getVecX() const{
		return this->vecx;
	};
	inline const double getVecY() const{
		return this->vecy;
	};
	inline void setVecX(const double valeur){
		this->vecy = valeur;
	};
	inline void setVecY(const double valeur){
		this->vecy = valeur;
	};

	inline void modifierVecY(const double valeur){
		double resy = this->vecy * valeur;
		double resx = 0;
		if (resy > -0.80 && resy < 0.80) {
			double resx = (this->vecx > 0) ? (1 - fabs(resy)) : (1 - fabs(resy)) * -1;
			if (resx > -0.80 && resx < 0.80){
				this->vecy = resy;
				this->vecx = resx;
			}			
		}
	};
	inline int getVelocite(){
		return this->velocite;
	};
	inline void balleAuCentre(){
		srand(time(nullptr));
		this->x = 300;
		this->y = 225;
		double aleat = rand() % 60 + 20;
		this->vecx = aleat / 100;
		this->vecy = 1 - this->vecx;
	};
	inline void modifierVelocite(const double valeur){
		int res;
		if ((res = this->velocite * valeur) > VELOCITE_BALLE_MIN && this->velocite * valeur < VELOCITE_BALLE_MAX)
			this->velocite = res;
	};
	inline void modifierTaille(const double valeur){
		int res = double(this->diametre) * valeur;
		if ((res = double(this->diametre) * valeur) > TAILLE_MIN && double(this->diametre) * valeur < TAILLE_MAX)
			this->diametre = res;
	};
private:
	int diametre;
	double x;
	double y;
	double vecx;
	double vecy;
	int velocite;
};
#endif // !Balle_H
