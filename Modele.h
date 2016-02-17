#ifndef Modele_H
#define Modele_H

#include"Bonus.h"
#include"Humain.h"
#include<SFML/Window.hpp>
#include<iostream>
#include<vector>

const int MAX_BONUS = 4;
const int TPS_GENERATION_BONUS = 6;

class Modele
{
public:
	explicit Modele(bool controleurVideo){
		this->h = Humain();
		this->ia = IA();
		this->b = (controleurVideo) ? Balle(9, 300, 220, 500) : Balle(9, 300, 220, 700);
		this->tempsEcoule = sf::Time::Zero;
		this->mutex = true;
		this->nbRetour = 0;
		this->rebond = sf::Time::Zero;
	};
	explicit Modele(const Modele& m){
		this->h = m.h;
		this->ia = m.ia;
		this->b = m.b;
		this->tempsEcoule = m.tempsEcoule;
		this->mutex = m.mutex;
		this->nbRetour = m.nbRetour;
		this->rebond = m.rebond;
	};
	explicit Modele(Modele&& autre) : h{ std::move(autre.h) }, ia{ std::move(autre.ia) }, b{ std::move(autre.b) }, lbo(std::move(autre.lbo)), tempsEcoule{ std::move(autre.tempsEcoule) },
		mutex{ autre.mutex }, nbRetour{ autre.nbRetour }, timer{ std::move(autre.timer) }, rebond{ std::move(autre.rebond) }{};
	inline void genererBonus(sf::Time temps){
		this->tempsEcoule += temps;
		if (int(this->tempsEcoule.asSeconds()) % TPS_GENERATION_BONUS == 0 && this->lbo.size() < MAX_BONUS && mutex){
			this->mutex = false;
			srand(time(nullptr));
			int aleatx = rand() % 600 + 1;
			int aleaty = rand() % 450 + 1;
			int effet = rand() % 6;
			Bonus b(aleatx, aleaty, effet);
			lbo.push_back(b);
		}
		else if (int(this->tempsEcoule.asSeconds()) % (TPS_GENERATION_BONUS + 1) == 0){
			this->mutex = true;
		}
	};
	inline void bougerRaquette(const int &sens, const float &temps){
		if (sens != 0){
			int coll = 0;
			coll = h.collisionAvecMur();
			if (coll != sens){
				h.setDirection(sens);
				this->h.bougerRaquette(float(h.getRaquette().getVelocite()) * temps * float(sens));
			}
		}
	};
	inline void bougerIA(const float &temps){
		this->ia.bougerRaquette(temps, this->b.getY());
	};
	inline void bougerBalle(const float &temps){
		int point = 0;
		if ((point = this->b.collisionAvecBalle(this->h)) != 0 || (point = this->b.collisionAvecBalle(this->ia)) != 0){
			this->rebond = timer.restart();
			if (this->rebond.asSeconds() > 0.10){
				(point > 0) ? this->b.rebondVertical() : this->b.rebondHorizontal();
				nbRetour++;
			}
			// /!\ A refaire plus proprement
			//si la balle et la raquette vont dans le meme sens, la balle change, A FAIRE ?
			//if (nbRetour % 2 == 0){
			//la balle va un peu plus du coté vers lequel le joueur appuie
			if (h.getDirection() > 0) {
				this->b.modifierVecY(0.80);
			}
			else {
				this->b.modifierVecY(1.20);
			}
			if (ia.getDirection() > 0) {
				this->b.modifierVecY(0.80);
			}
			else {
				this->b.modifierVecY(1.20);
			}
		}
		else if (b.collisionMurHorizontal()) this->b.rebondHorizontal();
		else if ((point = b.collisionMurVertical()) != 0){
			monterStatistiques(point);
			b.balleAuCentre();
			//on reprend le compte de 0
			this->nbRetour = 0;
		}
		else{
			for (std::vector<Bonus>::iterator it = lbo.begin(); it != lbo.end(); ++it){
				if (it->collisionAvecBonus(b) != 0){
					//l'ia joue la premiere, si le nombre de coups est pair, alors le joueur a touché la balle en dernier
					if (this->nbRetour != 0){
						(this->nbRetour % 2 == 0) ? it->appliquerEffet(h, b) : it->appliquerEffet(ia, b);
						lbo.erase(it);
					}
					break;
				}
			}
		}
		this->b.setX(float(b.getVelocite()) * float(temps) * b.getVecX());
		this->b.setY(float(b.getVelocite()) * float(temps) * b.getVecY());
	};
	/*
	* Si -1 augmente score ia, si 1 augmente score Humain
	*/
	inline void monterStatistiques(int valeur){
		augmenterScore(valeur);
		augmenterPoints(valeur);
		afficherScore();
	}
	inline void augmenterScore(int valeur){
		(valeur > 0) ? h.setScore(100) : ia.setScore(100);
	}
	inline void augmenterPoints(int valeur){
		(valeur > 0) ? h.setNbPoint(1) : ia.setNbPoint(1);
	}
	inline void afficherScore(){
		std::cout << "Humain : " << this->h.getNbPoint() << " - ";
		std::cout << "IA : " << this->ia.getNbPoint() << std::endl;
	}
	void debloquerHautFait(){

	}
	inline Humain getH(){
		return this->h;
	};
	inline IA getIA(){
		return this->ia;
	};
	inline Balle getB(){
		return this->b;
	}
	inline std::vector<Bonus> getBonus(){
		return this->lbo;
	}
private:

	Humain h;
	IA ia;
	Balle b;
	std::vector<Bonus> lbo;
	sf::Time tempsEcoule;
	bool mutex;
	//compte le nombre de renvoie qu'il y a eu sur la partie
	int nbRetour;
	sf::Clock timer;
	sf::Time rebond;
};
#endif // !Modele_H
