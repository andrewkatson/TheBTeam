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

  //the x of the vector of movement
  float xVector;
  //the y of the vector of movement
  float yVector;

  //the unique identifier for the projectile when it is spawned
  int projectileID;

public:
  //Area on the board that this projectile effects.
  int areaOfEffect;
  Projectile(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader);

  void initSprite();

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
  void move(float delta,int xmult=0, int ymult=0);

  /*
   * set the vector for movement (defined by an x and y)
   * @param x: the x component of the vector
   * @param y: the y component of the vectors
   */
  void setVector(float x, float y);

  /*
   * set the identifier for this projectile
   * @param projectileID: the integer identifier (probably the address)
   */
  void setProjectileID(int ID);

  void update(float delta);

};


#endif //CSCI437_PROJECTILE_HPP
