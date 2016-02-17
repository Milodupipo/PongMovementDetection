#ifndef Curseur_H
#define Curseur_H

#include<iostream>
#include<SFML/Graphics.hpp>

class Curseur : public sf::Drawable
{
public:
	Curseur()
	{
		this->y = 0;
		this->carre = sf::CircleShape(20, 4);
		this->carre.setPosition(-30, y);
		this->carre.setFillColor(sf::Color(150, 50, 250));
	};
	Curseur(const Curseur &c){
		*this = c;
	};
	explicit Curseur(Curseur&& autre) : y{ autre.y }, carre{ std::move(autre.carre) } {};
	inline const Curseur& operator=(const Curseur&& c){
		if (this != &c){
			this->carre = c.carre;
			this->carre.setPosition(0, y);
			this->y = c.y;
		}
		return *this;
	};
	inline const Curseur& operator=(const Curseur& c){
		this->carre = c.carre;
		this->carre.setPosition(-30, y);
		this->y = c.y;
		return *this;
	};
	~Curseur(){};
	inline const int getY() const{
		return y;
	};
	inline void setY(const int valeur){
		this->y = valeur;
	}
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(this->carre, states);
	};
	sf::CircleShape carre;
	int y;
};
#endif // !Curseur_H
