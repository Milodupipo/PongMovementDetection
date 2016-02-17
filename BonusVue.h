#ifndef BonusVue_H
#define BonusVue_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include <iterator>
#include"Bonus.h"

const int DIAMETRE_BONUS = 25;

class BonusVue : public sf::Drawable
{
public:
	BonusVue(){};
	BonusVue(int x, int y, int effet) : x(x), y(y), effet(effet){
		srand(time(nullptr));
		this->cercle = sf::CircleShape(DIAMETRE_BONUS);
		this->cercle.setPosition(x, y);

		this->cercle.setFillColor(sf::Color(this->r, this->g, this->b));
	};
	explicit BonusVue(const BonusVue &b){
		*this = b;
	};
	explicit BonusVue(BonusVue&& autre) : x(autre.x), y(autre.y), effet(autre.effet), r(autre.r), g(autre.g), b(autre.b), cercle(std::move(autre.cercle)) {};
	const BonusVue& operator=(const BonusVue &bov){
		this->x = bov.x;
		this->y = bov.y;
		this->r = bov.r;
		this->g = bov.g;
		this->b = bov.b;
		this->effet = bov.effet;
		this->cercle = bov.cercle;
		return *this;
	};
	const BonusVue& operator=(const Bonus &bo){
		Bonus tmp = bo;
		this->x = tmp.getX();
		this->y = tmp.getY();
		this->r = bo.getR();
		this->g = bo.getG();
		this->b = bo.getB();
		this->effet = tmp.getEffet();
		this->cercle = sf::CircleShape(DIAMETRE_BONUS);
		this->cercle.setPosition(this->x, this->y);
		this->cercle.setFillColor(sf::Color(this->r, this->g, this->b));
		return *this;
	};
	~BonusVue(){};
	inline double getY(){
		return this->y;
	};
	inline int getX(){
		return this->x;
	};
	inline sf::CircleShape getCercle(){
		return cercle;
	}
	inline const int getR() const{
		return r;
	}
	inline const int getG() const{
		return g;
	}
	inline const int getB() const{
		return b;
	}
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(this->cercle, states);
	};

	int x;
	int y;
	int effet;
	sf::CircleShape cercle;
	int r, g, b;
};
#endif // !BonusVue_H