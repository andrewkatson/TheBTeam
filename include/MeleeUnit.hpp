/*
 * MeleeUnit.cpp
 *
 * Purpose: Handle all operations for melee based units
 *
 * @author Jeremy Elkayam
 */
#ifndef CSCI437_MELEEUNIT_HPP
#define CSCI437_MELEEUNIT_HPP

using namespace std;

#include <memory>
#include "ActorInterface.hpp"

class MeleeUnit : public ActorInterface {

public:

  //The unit's current hitpoints.
  int hitpoints;

  //The damage the unit can deal.
  int damage;

  //The radius of the unit's automatic attack.
  int attackRadius;

  //The amount of armor the unit has.
  int armor;

  //A reference to the unit that this unit is fighting.
  shared_ptr<ActorInterface> engagedUnit;

private:

  /*
   * Return the amount of hitpoints the unit has
   *
   * @return the number of hitpoints the unit currently possesses
   */
  int getHitpoints(){return hitpoints;}

  /*
   * Update the unit's hit points accordingly
   */
  void updateHitpoints();

  /*
   * Update the unit's armor value.
   */
  void updateArmor();

  /*
   * Return whether or not the unit can attack.
   *
   * @return true if unit can attack right now, false otherwise
   */
  bool canAttack();

  /*
   * Have the unit initiate an attack.
   */
  void attack();

};


#endif //CSCI437_MELEEUNIT_HPP
