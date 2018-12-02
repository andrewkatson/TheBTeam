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
#include "Events/ProjectileExplosionEvent.hpp"
#include <chrono>
#include <algorithm>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::max;

class Projectile : public ActorInterface {

protected:

  //the x of the vector of movement
  float xVector;
  //the y of the vector of movement
  float yVector;
  //scale applied to the xvector
  float xVectorScale;
  //scale applied to the yvector
  float yVectorScale;
  //the x coordinate of the taget
  float xTarget;
  //the y coordinate of the target
  float yTarget;

  //the unique identifier for the projectile when it is spawned
  int projectileID;
  //The index of the sprite that the actor is currently using.
  int current_sprite;

public:
  Projectile(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader);

  /*
   * Set the coordinates of the actor to refer to its center
   */
  void setToCenter();

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
  void move(float delta);

  /*
   * set the vector for movement (defined by an x and y)
   * @param x: the x component of the vector
   * @param y: the y component of the vectors
   */
  void setVector(float x, float y);

  /*
   * set the positions for the target of the projectile
   * @param xScale: the x scaling for the vector towards the target
   * @param yScale: the y scaling for the vector towards the target
   */
  void setVectorScale(float xScale, float yScale);

  /*
   * set the positions for the target of the projectile
   * @param xpos: the x coordiante of the target of the projectile
   * @param ypos: the y coordinate of the target of the projectile
   */
  void setTargetPos(float x, float y);

  /*
   * set the identifier for this projectile
   * @param projectileID: the integer identifier (probably the address)
   */
  void setProjectileID(int ID);

  /*
   * @return the area of radius
   */
  int getAreaOfEffect(){return radius;}

  void update(float delta);

  /*
   * @return true if the projectile has hit the target
   */
  bool hasHitTarget();

  /*
   * If the projectile has hit the target we make an event for the projectile's
   * explosion that will be handeled by the gamelogic
   */
  void handleTargetHit();

  /*
   * Setting the fixtures for Box2D
   */
  void setFixtures();


};


#endif //CSCI437_PROJECTILE_HPP
