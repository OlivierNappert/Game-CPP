#include "../include/Soldier.hpp"

/*
Sodier& Soldier::operator=(const Soldier& obj)
{
   Soldier temp(copy);
   std::swap(temp.hp, hp);
   std::swap(temp.pa, pa);
   std::swap(temp.pm, pm);
   std::swap(temp.attackValue, attackValue);
   std::swap(temp.moveValue, moveValue);
   std::swap(temp.range, range);
   std::swap(temp.cost, cost);
   std::swap(temp.pos, pos);
   std::swap(temp.unitID, unitID);
   std::swap(temp.superSoldier, superSoldier);

   return *this;

}
*/

void Soldier::refresh(){
	pa = superSoldier ? 2 : 1;
	pm = 1;
}

int Soldier::action1(){
    return ATTACK;
}

int Soldier::action2(){
    return MOVE;
}

int Soldier::action3(){
    if(pa > 0 || superSoldier)
        return ATTACK;
    
    return IDLE;
}

void Soldier::setSuperSoldier(){
	superSoldier = true;
	name = "SSoldier";
}

Soldier* Soldier::clone(){    
    return new Soldier(hp,pa,pm,attackValue,moveValue,range,cost,unitID);
}
