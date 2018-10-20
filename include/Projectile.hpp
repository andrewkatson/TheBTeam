//
// Created by jeremy on 10/20/18.
//

#ifndef CSCI437_PROJECTILE_HPP
#define CSCI437_PROJECTILE_HPP

#include "ActorInterface.hpp"

class Projectile : public ActorInterface {

public:

  //The amount that this projectile penetrates a unit's armor [a percentage, maybe?]
  float armorPenetration;

  //Amount of damage dealt by this projectile.
  int damage;

  //Area on the board that this projectile effects.
  int affectedArea;

private:

  /*
   * Return the amount that this projectile penetrates the armor of a given unit
   *
   * @return the projectile's penetration of enemy armor in percent of total armor.
   */
  float getArmorPenetration() const;

  /*
   * Returns the damage this projectile deals.
   *
   * @return the projectile's damage dealt in hitpoints.
   */
  int getDamage() const;

  /*
   * Move the projectile based on its speed and direction.
   */
  void move(float deltaS);

};


#endif //CSCI437_PROJECTILE_HPP
