#ifndef RaquetteVue_H

#include<iostream>
#include<SFML/Graphics.hpp>

class RaquetteVue : public sf::Drawable
{
public:
	RaquetteVue(){};
	RaquetteVue(bool ia, int taille) : longueur(taille)
	{
		this->y = 150;
		(ia) ? this->x = 565 : this->x = 15;
		rectangle = sf::RectangleShape(sf::Vector2f( 20, taille));
		rectangle.setPosition(x, 300);
		rectangle.setFillColor(sf::Color(255, 255, 255));
	};
	explicit RaquetteVue(const RaquetteVue &raq){
		*this = raq;
	};
	const RaquetteVue& operator=(const RaquetteVue &raq){
		this->longueur = raq.longueur;
		this->y = raq.y;
		this->x = raq.x;
		this->rectangle = raq.rectangle;
		return *this;
	};
	inline void setTaille(const int valeur){
		this->longueur = valeur;
		this->rectangle.setSize(sf::Vector2f( 20, longueur));
	};
	inline void setY(const int valeur){
		this->y = valeur;
		this->rectangle.setPosition(x, y);
	};
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(rectangle, states);
	};

	int longueur;
	int y;
	int x;
	sf::RectangleShape rectangle;
};
#endif // !RaquetteVue_H
