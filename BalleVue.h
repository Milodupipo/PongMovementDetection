#ifndef BalleVue_H
#define BalleVue_H

#include<iostream>
#include<SFML/Graphics.hpp>
#include"Balle.h"

class BalleVue : public sf::Drawable
{
public:
	BalleVue(){};
	BalleVue(int diametre, int x, int y) : diametre(diametre), x(x), y(y)
	{
		this->cercle = sf::CircleShape(diametre);
		this->cercle.setFillColor(sf::Color(255, 255, 255));
		this->cercle.setPosition(300, 225);
	};
	explicit BalleVue(const BalleVue &balle){
		*this = balle;
	};
	explicit BalleVue(BalleVue&& autre) : x{ autre.x }, y{ autre.y }, diametre{ autre.diametre }, cercle{ std::move(autre.cercle) } {};
	~BalleVue(){};
	const BalleVue& operator=(const BalleVue &bav){
		this->diametre = bav.diametre;
		this->y = bav.y;
		this->x = bav.x;
		this->diametre = bav.diametre;
		this->cercle = bav.cercle;
		return *this;
	};
	const BalleVue& operator=(const Balle &ba){
		this->diametre = ba.getDiametre();
		this->y = ba.getY();
		this->x = ba.getX();
		this->cercle.setPosition(x, y);
		this->cercle.setRadius(this->diametre);
		return *this;
	};
	inline void setContour(){
		this->cercle.setOutlineThickness(4);
		this->cercle.setOutlineColor(sf::Color(250, 150, 100));
	}
	inline void setTaille(const int diametre){
		this->diametre = diametre;
		this->cercle = sf::CircleShape(diametre);
	};
	inline void setY(const int valeur){
		this->y = valeur;
		this->cercle.setPosition(x, y);
	};
	inline void setX(const int valeur){
		this->x = valeur;
		this->cercle.setPosition(x, y);
	};
	inline int getX(){
		return this->x;
	};
	inline int getY(){
		return this->y;
	};
	inline int getDiametre(){
		return this->diametre;
	};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(this->cercle, states);
	};

	int diametre;
	int x;
	int y;
	sf::CircleShape cercle;
};
#endif // !BalleVue_H