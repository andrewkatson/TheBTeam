/*
 * Projectile.hpp
 *
 * Purpose: Manage a projectile's properties and behavior
 *
 * @author Jeremy Elkayam
 */

#ifndef CSCI437_PROJECTILE_HPP
#define CSCI437_PROJECTILE_HPP

#include "ActorInterface.hpp"

class Projectile : public ActorInterface {

protected:

  //Area on the board that this projectile effects.
  int areaOfEffect;

  //the x of the vector of movement
  int x;
  //the y of the vector of movement
  int y;

  //the unique identifier for the projectile when it is spawned
  int projectileID;

public:

  /*
   * Return the amount that this projectile penetrates the armor of a given unit
   *
   * @return the projectile's penetration of enemy armor in percent of total armor.
   */
  int getArmorPenetration() const;

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

  /*
   * set the vector for movement (defined by an x and y)
   * @param x: the x component of the vector
   * @param y: the y component of the vectors
   */
  void setVector(int x, int y);

  /*
   * set the identifier for this projectile
   * @param projectileID: the integer identifier (probably the address)
   */
  void setProjectileID(int ID);

};


#endif //CSCI437_PROJECTILE_HPP