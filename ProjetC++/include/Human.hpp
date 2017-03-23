#ifndef _HUMAN_H
#define _HUMAN_H

#include "../include/Player.hpp"

class Unit;

class Human : public Player
{
   public :
      Human(const int hp_, const int gold_) : Player(hp_, gold_) {};
      ~Human() {};
      void shop(std::vector<Unit*> factoryUnits, const int direction, const int mapSize);
};
#endif
