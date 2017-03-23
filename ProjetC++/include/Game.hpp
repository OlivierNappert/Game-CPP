#ifndef _GAME_H
#define _GAME_H

#include <vector>
#include <string>
#include "Human.hpp"
#include "AI.hpp"
#include "Phase.hpp"
#include "Unit.hpp"

class Game
{
   private :
      std::vector<Player*> players;
      std::vector<Unit*> factoryUnits;
      Phase phase; 
      int mapSize;
      int goldPerTurn;
      
    public :
	Game(const std::vector<Player*> players_, const std::vector<Unit*> factoryUnits_, const Phase phase_, const int mapSize_, const int goldPerTurn_) : players(players_), factoryUnits(factoryUnits_), phase(phase_), mapSize(mapSize_), goldPerTurn(goldPerTurn_) {}
	~Game();

        /*
         * Fonction init
         * 
         * Initialise le jeu en créeant les joueurs
         */
        void initialize();
        
        /*
         * 
         * Fonction run
         * 
         * Lance la boucle principale du programme
         * 
         */
        void run();

        /*
         * Fonction sortByPrice
         *
         * Permet de trier les unites par prix croissant avec std::sort
         *
         */
        static bool sortByPrice(Unit* unit1, Unit* unit2);

        /*
         * Fonction giveGolds
         *
         * Donne a un joueur l'argent du debut de tour
         *
         */
        void giveGolds(Player& playing);

        /*
         * Fonction refreshUnits
         *
         * Redonne des pa et des pm aux units a la fin du tour des joueurs
         */
        void refreshUnits();
};
#endif
