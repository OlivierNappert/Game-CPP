#include "../include/Catapult.hpp"
#include <iostream>
/*
Catapult& Catapult::operator=(const Catapult& obj)
{
   Catapult temp(obj);
   std::swap(temp.hp, hp);
   std::swap(temp.pa, pa);
   std::swap(temp.pm, pm);
   std::swap(temp.attackValue, attackValue);
   std::swap(temp.moveValue, moveValue);
   std::swap(temp.range, range);
   std::swap(temp.cost, cost);
   std::swap(temp.pos, pos);
   std::swap(temp.unitID, unitID);

   return *this;
}
*/

int Catapult::action1(){
    return ATTACK;
}

int Catapult::action2(){
    return IDLE;
}

int Catapult::action3(){
    if(pa > 0)
        return MOVE;
    
    return IDLE;
}


Catapult* Catapult::clone(){
    return new Catapult(hp,pa,pm,attackValue,moveValue,range,cost,unitID);
}
