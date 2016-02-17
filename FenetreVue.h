#ifndef FenetreVue_H
#define FenetreVue_H

#include<iostream>
#include<algorithm>
#include<vector>
#include"RaquetteVue.h"
#include"BalleVue.h"
#include"StatsVue.h"
#include"BonusVue.h"
#include"Humain.h"
#include"Curseur.h"
#include"IA.h"

void copier(const std::vector<Bonus> &param, std::vector<BonusVue> &result)
{
	std::vector<Bonus> tmpParam = param;
	BonusVue bv;
	result.clear();
	for (std::vector<Bonus>::iterator it = tmpParam.begin(); it != tmpParam.end(); ++it){
		bv = *it;
		result.push_back(bv);
	}
}

class FenetreVue
{
public:
	FenetreVue(int dx, int dy, bool controleurVideo) : x(dx), y(dy)
	{
		this->controleVideo = controleurVideo;
		this->r1 = RaquetteVue(false, 60);
		this->r2 = RaquetteVue(true, 60);
		this->b = BalleVue(9, 300, 225);
		this->s = StatsVue();
		this->c = Curseur();
		this->lbo.push_back(BonusVue(-500, -500, 0));
	};
	explicit FenetreVue(const FenetreVue &vue){
		*this = vue;
	};
	// /!\ manque le constructeur par déplacement
	const FenetreVue& operator=(const FenetreVue &vue){
		this->x = vue.x;
		this->y = vue.y;
		this->r1 = vue.r1;
		this->r2 = vue.r2;
		this->b = vue.b;
		this->c = vue.c;
		this->fenetre = vue.fenetre;
		return *this;
	};
	const FenetreVue& operator=(FenetreVue&& vue){
		if (this != &vue)
		{
			delete fenetre;
			this->fenetre = vue.fenetre;
			vue.fenetre = nullptr;
			this->x = vue.x;
			this->y = vue.y;
			this->r1 = vue.r1;
			this->r2 = vue.r2;
			this->b = vue.b;
			this->c = vue.c;
		}
		return *this;
	};
	~FenetreVue(){
		delete fenetre;
	};
	inline sf::RenderWindow* creerFenetre(){
		//créer la fenetre
		sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(x, y), "FenetreVue");
		fenetre = window;
		return window;
	};
	/*
	* Humain, ia, balle x, bally y, liste bonus
	*/
	inline const void actualiser(const Humain &j, const IA &ia, const Balle &b, const std::vector<Bonus> &bo, const Curseur &c){
		copier(bo, lbo);
		this->r1.setTaille(j.getRaquette().getLongueur());
		this->r2.setTaille(ia.getRaquette().getLongueur());
		this->r1.setY(j.getRaquette().getY());
		this->r2.setY(ia.getRaquette().getY());
		this->b = b;
		this->c = c;
	};
	inline void dessiner(){
		for (std::vector<BonusVue>::iterator it = lbo.begin(); it != lbo.end(); ++it){
			fenetre->draw(*it);
		}
		if (this->controleVideo) fenetre->draw(c);
		fenetre->draw(r1);
		fenetre->draw(r2);
		fenetre->draw(b);
	}
private:
	int x;
	int y;
	RaquetteVue r1;
	RaquetteVue r2;
	BalleVue b;
	StatsVue s;
	Curseur c;
	sf::RenderWindow* fenetre;
	std::vector<BonusVue> lbo;
	bool controleVideo;
};
#endif // !FenetreVue_H
