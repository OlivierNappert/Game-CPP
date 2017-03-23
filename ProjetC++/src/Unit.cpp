#include "../include/Unit.hpp"

Unit::~Unit(){
    delete(this);
}

void Unit::attack(std::vector<Unit*> targets, const int direction, const int mapSize){
    if(pa > 0 && targets.size() > 0){
        for(unsigned int i = 0; i < targets.size(); i++){
            targets[i]->takeDamage(attackValue);
            if(unitID == 1 && targets[i]->getID() == 1 && targets[i]->getHp() <= 0){
                this->setSuperSoldier();
            }
        }
        pa --;
    }
}

bool Unit::playerInRange(const int direction, const int mapSize){
    if(direction == -1 && ( pos + range.rangeMin <= mapSize-1 && pos + range.rangeMax + (range.aoe -1) >= mapSize-1))
        return true;
    else if(direction == 1 && ( pos - range.rangeMin >= 0 && pos - (range.rangeMax + (range.aoe -1)) <= 0))
        return true;

    return false;
}

void Unit::move(const int obstaclePos, const int direction){
   
//    int maxPos; = (obstaclePos-pos)+ direction;
    
    int lastPos = pos;
    int maxPos = obstaclePos + direction;
    if(pos == maxPos)
        maxPos = 0;
    
    direction == -1 ? pos += std::min(moveValue, maxPos) : pos -= std::min(moveValue, maxPos) ;
    if(pos != lastPos)
        pm--;
}


void Unit::takeDamage(const int damage){
    hp -= damage;
}

void Unit::refresh(){
    pa = 1;
    pm = 1;
}

int Unit::getHp() const{
    return hp;
}

int Unit::getPa() const{
    return pa;
}

void Unit::minPa(){
    pa--;
}

int Unit::getPm() const{
    return pm;
}

int Unit::getID() const{
    return unitID;
}

int Unit::getCost() const{
    return cost;
}

int Unit::getPos() const{
    return pos;
}

void Unit::setPos(const int pos_){
    pos = pos_;
}

int Unit::getAttackValue() const{
    return attackValue;
}

int Unit::getMoveValue() const{
    return moveValue;
}

std::string Unit::getName() const
{
   return name;
}

Range Unit::getRange() const{
    return range;
}


