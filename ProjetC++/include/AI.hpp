#ifndef _AI_H
#define _AI_H

#include "Player.hpp"

class Unit;

class AI : public Player
{
   public :
      AI(const int hp_, const int gold_) : Player(hp_, gold_) {};
      ~AI() {};
      void play();
      void shop(std::vector<Unit*> factoryUnits, const int direction, const int mapSize);
};
#endif
