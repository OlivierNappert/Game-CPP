#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <algorithm>
#include <iostream>

class Unit;

class Player
{
   public :
      Player(const int  hp_, const int gold_) : hp(hp_), gold(gold_) {units.reserve(12);};
      virtual ~Player();
      int getHp() const;
      int getGold() const;
      std::vector<Unit*> getUnits() const;

      /*
       * Fonction addGold
       *
       * Entrees : int golds : quantite de gold a ajoute au joueur
       * Sorties : aucune
       *
       * Ajoute la quantite de gold passee en parametre au joueur.
       */
      void addGold(const int golds);
      
      /*
       * Fonction killUnits
       *
       * Detruit les unites dont les points de vie sont inferieurs a 0
       *
       */
      int killUnits();

      /*
       * Fonction takeDamage
       *
       * Inflige des degats au joueur
       *
       */
      void takeDamage(const int attackValue);

      /*
       * Fonction hasEnoughGold
       *
       * Renvoie true si le joueur peut acheter l'unite, false sinon
       *
       */
      bool hasEnoughGold(const int cost);

      /*
       * Fonction addUnit
       *
       * Ajoute une unite aux rangs du joueur
       *
       */
      void addUnit(Unit& unit, const int direction, const int mapSize);


        /*
         * Fonction shop
         *
         * Permet au joueur d'ajouter une unite a ses rangs moyennant paiement
         *
         */

      /*
       * Fonction unitOnBase
       *
       * Renvoie true si une unite se trouve sur la base du joueur
       */
      bool unitOnBase(const int direction, const int mapSize);
      virtual void shop(std::vector<Unit*> factoryUnits, const int direction, const int mapSize) = 0;
      
   protected :
      int hp;
      int gold;
      std::vector<Unit*> units;
};
#endif
