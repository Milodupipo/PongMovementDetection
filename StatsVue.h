#ifndef StatsVue_H
#define StatsVue_H

#include<iostream>
#include<SFML/Graphics.hpp>

class StatsVue : public sf::Drawable
{
public:
	StatsVue()
	{
		// set the string to display
		
		this->texte.setString("Welcome to Pong");
		
		if (!font.loadFromFile("HighVoltage.otf"))
		{
			std::cout << "[StatsVue][constructeur]La font n'a pas correctement ete chargee" << std::endl;
		}
		this->texte.setFont(font);
		// set the character size
		this->texte.setCharacterSize(24); // in pixels, not points!
		// set the color
		this->texte.setColor(sf::Color::White);
		this->texte.setPosition(10, 10);
	};
	StatsVue(const StatsVue &stat){
		*this = stat;
	};
	
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
		target.draw(this->texte, states);
	};

	sf::Text texte;
	sf::Font font;
};
#endif // !StatsVue_H