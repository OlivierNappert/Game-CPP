#include "../include/Bowman.hpp"

/*
Bowman& Bowman::operator=(const Bowman& obj)
{
   Bowman temp(obj);
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

int Bowman::action1(){
    return ATTACK;
}

int Bowman::action2(){
    return MOVE;
}

int Bowman::action3(){
    return IDLE;
}


Bowman* Bowman::clone(){
    return new Bowman(hp,pa,pm,attackValue,moveValue,range,cost,unitID);
}
