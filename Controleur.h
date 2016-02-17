#ifndef Controleur_H
#define Controleur_H

#include<SFML/Window.hpp>
#include"Detection.h"
#include"Raquette.h"
#include"Curseur.h"
#include <thread> 

class Controleur
{
public:
	Controleur(bool controleurVideo)
	{
		std::cout << "Controleur par defaut" << std::endl;
		this->controleurVideo = controleurVideo;
		this->sens = 0;
		this->d = new Detection;
	};
	explicit Controleur(const Controleur &c){
		std::cout << "Controleur par copie" << std::endl;
		*this = c;
	};
	explicit Controleur(Controleur&& autre) : sens{ autre.sens }, d{ std::move(autre.d) }, c{ autre.c }, controleurVideo{ autre.controleurVideo } {};
	const Controleur& operator=(const Controleur &ctrl){
		std::cout << "Controleur affectation par copie" << std::endl;
		this->d = ctrl.d;
		this->sens = ctrl.sens;
		this->c = ctrl.c;
		this->controleurVideo = ctrl.controleurVideo;
		return *this;
	};
	const Controleur& operator=(Controleur&& ctrl){
		std::cout << "Controleur affectation par deplacement" << std::endl;
		if (this != &ctrl)
		{
			delete d;
			this->d = ctrl.d;
			ctrl.d = nullptr;
			this->sens = ctrl.sens;
			this->c = ctrl.c;
			this->controleurVideo = ctrl.controleurVideo;
		}
		return *this;
	};
	~Controleur(){};
	inline void ecouterControleutilisateur(sf::RenderWindow *fenetre, const Raquette &r){
		(this->controleurVideo) ? lireFluxVideo(fenetre, r) : ecouterClavier(fenetre);
	}
	inline int getSens(){
		return sens;
	};
	inline const Curseur getCurseur() const{
		return this->c;
	};
private:
	//bouge la raquette dans le sens de la masse du point capté sur la caméra
	inline void lireFluxVideo(sf::RenderWindow *fenetre, const Raquette &r){
		sf::Event event;
		while (fenetre->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				fenetre->close();
				break;
			}
		}
		int y = d->analyseImage();
		c.setY(y);
		//le but ici est de laisser une marge de 20px dans lesquels la barre arretera de bouger
		//la position sera considérée comme bonne
		if (r.getY() + (r.getLongueur() / 2) - 20 + 10 < y){
			touches(sf::Keyboard::Up, false);
			touches(sf::Keyboard::Down, true);
		}
		else if (r.getY() + (r.getLongueur() / 2) - 20 - 10 > y){
			touches(sf::Keyboard::Down, false);
			touches(sf::Keyboard::Up, true);
		}
		else{ 
			touches(sf::Keyboard::Down, false);
			touches(sf::Keyboard::Up, false);
		}
	};
	/*
	* Si Up -1 si Down 1
	*/
	inline void ecouterClavier(sf::RenderWindow *fenetre){
		sf::Event event;
		while (fenetre->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				touches(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				touches(event.key.code, false);
				break;

			case sf::Event::Closed:
				fenetre->close();
				break;
			}
		}
	};
	inline void touches(sf::Keyboard::Key key, bool presser)
	{
		if (key == sf::Keyboard::Up)
			(presser) ? this->sens = -1 : this->sens = 0;
		else if (key == sf::Keyboard::Down)
			(presser) ? this->sens = 1 : this->sens = 0;
	};

	int sens;
	Detection *d;
	Curseur c;
	bool controleurVideo;
};
#endif // !Controleur_H
