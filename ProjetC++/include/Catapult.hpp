#ifndef _CATAPULT_H
#define _CATAPULT_H

#include <iostream>
#include "Unit.hpp"

class Catapult : public Unit
{

	public:
		Catapult(const int hp_, const int pa_, const int pm_, const int attackValue_, const int moveValue_, const Range range_, const int cost_, int unitID_) : Unit(hp_, pa_, pm_, attackValue_, moveValue_, range_, cost_, unitID_, "catapult") {};
		//Catapult(const Catapult& copy) : Unit(copy) {};
		~Catapult() {};
		//Catapult& operator=(const Catapult& obj);
		int action1();
		int action2();
		int action3();
		Catapult* clone();
};

#endif
