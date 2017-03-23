#include <iostream>
#include "../include/AI.hpp"
#include "../include/Unit.hpp"

void AI::shop(std::vector<Unit*> factoryUnits, const int direction, const int mapSize)
{
	if(units.size() == 0){
		for(int i = factoryUnits.size()-1; i >= 0; i--){
          if(hasEnoughGold(factoryUnits[i]->getCost())){
              addUnit(*factoryUnits[i],direction,mapSize);
              break;
          }
      }
	}

  else if(!unitOnBase(direction,mapSize)){
    for(int i = factoryUnits.size()-1; i >= 0; i--){
      if(hasEnoughGold(factoryUnits[i]->getCost())){
          addUnit(*factoryUnits[i],direction,mapSize);
          break;
      }
    }
  }
}
