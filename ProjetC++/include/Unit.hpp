#ifndef _UNIT_H
#define _UNIT_H

#include "Player.hpp"
#include <vector>
#include <string>

#define IDLE 0
#define MOVE 1
#define ATTACK 2

struct Range
{
  int rangeMin;
  int rangeMax;
  int aoe;
};
                
class Unit
{
  protected:
    int hp;
    int pa;
    int pm;
    int attackValue;
    int moveValue;
    Range range;
    int cost;
    int pos;
    int unitID;
    std::string name;

  public:
    Unit(const int hp_, const int pa_, const int pm_, const int attackValue_, const int moveValue_, const Range range_, const int cost_, const int unitID_, const std::string name_) : hp(hp_), pa(pa_), pm(pm_), attackValue(attackValue_), moveValue(moveValue_), range(range_),cost(cost_), unitID(unitID_), name(name_) {};
    virtual ~Unit();
    /*
    * Fonction abstraite refresh
    *
    * Donne a une unite ses points de deplacement et d'attaque maximums pour un tour 
    */
    virtual void refresh();

    /*
    * Fonctions abstraite action
    *
    * Indique a une unite l'action a effectuer lors des phases
    */
    virtual int action1() = 0;
    virtual int action2() = 0;
    virtual int action3() = 0;

    virtual void setSuperSoldier(){};

    /*
     * Fonction clone
     *
     * Clone une unite pour donner a une autre unite les memes stats
     */
    virtual Unit* clone() = 0;

    /*
    * Fonction attack
    *
    * Permettra a une unite d'attaquer 
    */
    void attack(std::vector<Unit*> targets, const int direction, const int mapSize);

    /*
    * Fonction move
    *
    * Permettra a une unite de se deplacer 
    */
    void move(const int obstaclePos,const int direction);

    /*
    * Fonction tameDamage
    *
    * Inflige des degats a une unite apres s'etre fait attaquer 
    */
    void takeDamage(const int damage);

    /*
    * 
    * Surchage de l'operateur < pour trier par position
    * 
    */
    // bool operator< (const Unit* other) const { return this->pos < other->pos; } devrait etre inutile maintenant
    int getHp() const;
    int getPa() const;
    void minPa();
    int getPm() const;
    int getID() const;
    int getCost() const;
    int getPos() const;
    void setPos(const int pos_);
    int getAttackValue() const;
    int getMoveValue() const;
    std::string getName() const;
    Range getRange() const;

    /*
    * Fonction playerInRange
    *
    * Renvoie true si le joueur ennemie est a porte de l'unite, false sinon
    *
    */
    bool playerInRange(const int direction, const int mapSize);
};

#endif
