#ifndef _SOLDIER_H
#define _SOLDIER_H

#include "Unit.hpp"

class Soldier : public Unit
{
	private:
		bool superSoldier;

	public:
		Soldier(const int hp_, const int pa_, const int pm_, const int attackValue_, const int moveValue_, const Range range_, const int cost_, const int unitID_) : Unit(hp_, pa_, pm_, attackValue_, moveValue_, range_, cost_ , unitID_, "soldier"), superSoldier(false) {};
		//Soldier(const Soldier& copy) : Unit(copy) { superSoldier = copy.superSoldier };
		~Soldier() {};
		//Soldier& operator=(const Soldier& obj);
		int action1();
		int action2();
		int action3();
    void refresh();
		void setSuperSoldier();
		Soldier* clone();
};

#endif
