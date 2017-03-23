#ifndef _PHASE_H
#define _PHASE_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

#include "Player.hpp"

//constantes definissant les actions des unites
#define IDLE 0
#define MOVE 1
#define ATTACK 2

//constantes pour l'affichage
#define WIDTH	     9 //largeur d'une case de la map sans sa colonne de droite
#define HORIZONTAL   "═"
#define VERTICAL     "║"
#define TOPCROSS     "╦"
#define BOTCROSS     "╩"
#define TRCORNER     "╗"
#define TLCORNER     "╔"
#define BRCORNER     "╝"
#define BLCORNER     "╚"

#if defined (__linux__) 
  #define CLEAR	"clear"
#elif defined (_WIN32) 
  #define CLEAR "cls"
#endif

class Unit;

class Phase
{             
    public:
        Phase(){};
        ~Phase() {};
        /*
         * 
         * Fonction closestObstacle
         * 
         * Retourne l'obstacle le plus proche d'une unite
         * 
         */
        int closestObstacle(std::vector<Unit*> playingUnits, std::vector<Unit*> notPlayingUnits, const int direction,
            const unsigned int index, const int mapSize);
        
        /*
         * 
         * Fonction getTargets
         * 
         * Renvoie le tableau de la ou des cibles d'une unite pour l'attaque
         * 
         */
        std::vector<Unit*> getTargets(std::vector<Unit*> playingUnits, std::vector<Unit*> notPlayingUnits,
            const int direction, const unsigned int index, const int mapSize, bool* attackPlayerP);
        
        /*
         * Fonction sortByPosition
         * 
         * Permet de definir l'ordre dans lequel trier les vectors d'unite avec la fonction std::sort
         * 
         */
        static bool sortByPosition(Unit* unit1, Unit* unit2);
        /*
         * Fonctions phase
         * 
         * Effectuent les operations associees a chaque phase de jeu
         */
        void phase1(Player& playing, Player& notPlaying, const int direction, const int mapSize);
        void phase2(Player& playing, Player& notPlaying, const int direction, const int mapSize);
        void phase3(Player& playing, Player& notPlaying, const int direction, const int mapSize);
        
        /*
         * Fonction cleanUnit 
         * 
         * Supprime les unites tombees au combat
         */
        void cleanUnits(Player& playing, Player& notPlaying);

    	/*
    	 * Fonction renderMap
    	 *
    	 * Entrees : une reference sur chaque joueur, la taille de la carte et le numero de la phase
    	 * Sorties : aucune
    	 *
    	 * Affiche l'etat actuel du jeu et l'ecrit dans un fichier.
    	 */
         void renderMap(Player& playing, Player& notPlaying, const int mapSize, const int phaseNb, const int direction, const int turn);

    	/*
    	 * Fonction getNameByPos
    	 *
    	 * Entrees : les 2 joueurs et la position a laquelle on cherche l'unite
    	 * Sorties : une string contenant le nom de l'unite
    	 *
    	 * Parcours les vecteurs d'unites des joueurs pour trouver le nom de l'unite a
    	 * une position donnee.
    	 */
    	std::string getNameByPos(Player& player1, Player& player2, const int pos);

    	/*
    	 * Fonction getHpByPos
    	 *
    	 * Entrees : les 2 joueurs et la position a laquelle on cherche l'unite
    	 * Sorties : un int contenant les hp de l'unite
    	 *
    	 * Parcours les vecteurs d'unites des joueurs pour trouver les hp d'une unite a
    	 * une position donnee.
    	 */
    	int getHpByPos(Player& player1, Player& player2, const int pos);

	/*
	 * Fonction getPlayerByPos
	 *
	 * Entrees : les 2 joueurs, la position a laquelle on cherche l'unite et la direction
	 * Sorties : le numero du joueur a qui appartient l'unite
	 *
	 * Parcour les vecteurs d'unites des 2 joueurs et renvoie 1 si l'unite presente
	 * a la case pos appartient au joueur 1, 2 si elle appartient au joueur 2 et
	 * 0 si aucune unite n'est presente a cette position
	 */
	int getPlayerByPos(Player& player1, Player& player2, const int pos, const int direction);

        /*
         * Fonction renderShop
         *
         * Affiche la boutique pour acheter des unites
         *
         */
        void renderShop();

        /*
         * Fonction checkWin
         *
         * Renvoie true si le joueur passe en argument est mort, false sinon
         *
         */
        bool checkWin(Player& player);

	/*
	 * Fonction toNumberOfDigits
	 *
	 * Entrees : un entier
	 * Sorties : un entier
	 *
	 * Calcul le nombre de digits d'un entier.
	 */
	int getNumberOfDigits(int n);
        
};
#endif

