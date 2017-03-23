#ifndef _BOWMAN_H
#define _BOWMAN_H

#include "Unit.hpp"

class Bowman : public Unit
{

	public:
		Bowman(const int hp_, const int pa_, const int pm_, const int attackValue_, const int moveValue_, const Range range_, const int cost_, const int unitID_) : Unit(hp_, pa_, pm_, attackValue_, moveValue_, range_, cost_, unitID_, "bowman") {};
		//Bowman(const Bowman& copy) : Unit(copy) {};
		~Bowman() {};
		//Bowman& operator=(const Bowman& obj);
		int action1();
		int action2();
		int action3();
		Bowman* clone();
};

#endif
