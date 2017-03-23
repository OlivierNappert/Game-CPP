#include "../include/Player.hpp"
#include "../include/Unit.hpp"

#include <iostream>

Player::~Player(){
  units.clear();
}

int Player::getHp() const
{
   return hp;
}

int Player::getGold() const
{
   return gold;
}

std::vector<Unit*> Player::getUnits() const
{
   return units;
}

void Player::addGold(const int golds)
{
   gold += golds;
}

int Player::killUnits(){
    int golds = 0;
    
    for(unsigned int i = 0; i < units.size(); i++)
    {
        if(units[i]->getHp() <= 0)
	{
            golds += units[i]->getCost() / 2;
            units.erase(std::remove(units.begin(), units.end(), units[i]), units.end());
            i--;    // Car les elements suivants ont ete decalles vers la gauche
        }
    }
    
    return golds;
}

void Player::takeDamage(const int attackValue){
  hp -= attackValue;
}

bool Player::hasEnoughGold(const int cost){
  return cost <= gold;
}

void Player::addUnit(Unit& unit, const int direction, const int mapSize){
  int pos_ = 0;
  Unit* newUnit = unit.clone();
  direction == -1 ? pos_ = 0 : pos_ = mapSize-1;
  newUnit->setPos(pos_);
  units.push_back(newUnit);
  gold -= newUnit->getCost();
}

bool Player::unitOnBase(const int direction, const int mapSize){
  int basePos;
  direction == -1 ? basePos = 0 : basePos = mapSize-1;
  for(unsigned int i = 0; i < units.size(); i++){
    if(units[i]->getPos() == basePos)
      return true;
  }
  return false;
}
