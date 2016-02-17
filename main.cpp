#include<iostream>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include"FenetreVue.h"
#include"Controleur.h"
#include"Modele.h"
#include <stdio.h>

const bool CONTROLE_FLUXVIDEO = true;

int main(){
	// Fps of the game
	const sf::Time ImageParSeconde = (CONTROLE_FLUXVIDEO) ? sf::seconds(1.f / 30.f) : sf::seconds(1.f / 100.f);
	sf::Clock timer;
	sf::Time derniereMaj = sf::Time::Zero;
	Controleur ctrl(CONTROLE_FLUXVIDEO);
	Modele modele(CONTROLE_FLUXVIDEO);
	FenetreVue vue(600, 450, CONTROLE_FLUXVIDEO);
	sf::RenderWindow* window = vue.creerFenetre();

	// Clear screen
	window->clear();
	vue.dessiner();
	// Update the window
	window->display();
	while (window->isOpen())
	{
		// Count the time for each iteration of the loop
		sf::Time tempsPasser = timer.restart();
		derniereMaj += tempsPasser;
		// Regulate number of frame per second
		while (derniereMaj > ImageParSeconde){
			derniereMaj -= ImageParSeconde;
			modele.genererBonus(ImageParSeconde);
			ctrl.ecouterControleutilisateur(window, modele.getH().getRaquetteRef());
			modele.bougerRaquette(ctrl.getSens(), ImageParSeconde.asSeconds());
			modele.bougerIA(ImageParSeconde.asSeconds());
			modele.bougerBalle(ImageParSeconde.asSeconds());
			vue.actualiser(modele.getH(), modele.getIA(), modele.getB(), modele.getBonus(), ctrl.getCurseur());
			if (CONTROLE_FLUXVIDEO){
				// Clear screen
				window->clear();
				vue.dessiner();
				// Update the window
				window->display();
			}
		}
		// Clear screen
		window->clear();
		vue.dessiner();
		// Update the window
		window->display();
	}
	return 0;
}