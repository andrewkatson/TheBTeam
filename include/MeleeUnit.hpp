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
#include "HitpointBar.hpp"

class MeleeUnit : public ActorInterface {

protected:

  //the money given to the player when he feeds this unit
  int lunchMoney;

  //The unit's current hitpoints.
  int hitpoints;

  //The damage the unit can deal.
  int damage;

  //The amount of armor the unit has.
  int armor;

  //The radius of the unit's automatic attack.
  int attackRadius;

  //A reference to the unit that this unit is fighting.
  shared_ptr<MeleeUnit> engagedUnit;

  //The bar for rendering the unit's HP
  HitpointBar hpBar;

public:
  /*
   * Default constructor
   */
  MeleeUnit();

  /*
   * Return the amount of hitpoints the unit has
   *
   * @return the number of hitpoints the unit currently possesses
   */
  int getHitpoints(){return hitpoints;}

  /*
   * Update the unit's hit points accordingly
   */
  void updateHitpoints(int damage);

  /*
   * Update the unit's armor value.
   */
  void updateArmor(int damage);

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

  /*
   * @return the unit's hitpoint bar
   */
  HitpointBar getHpBar();

  /*
    Returns the unique identifier for the actor.

    @return an integer representing the actor's identity
   */
  int getID(){return id;}

  /*
    Returns the actor's sprite.

    @return the Sprite object that the interface contains.
   */
  sf::Sprite& getSprite(){return sprite;}//PEOPLE WHO KNOW MORE THAN ME: SHOULD THIS RETURN A REFERENCE?

  /*
    Move the actor according to its speed and the actor's innate properties.

    This must be implemented by extending classes, since different types of
    actors obviously have different movement patterns.
  */
  void move(float deltaS);

  /*
    Determine whether or not the object's collision box is colliding with the
    given collision box. By default, this is determined by whether or not the
    wo collision boxes intersect.

    @return true if the actor's collision box is colliding with colliding_with,
            false otherwise.
   */
  bool isCollision(sf::FloatRect colliding_with);

};


#endif //CSCI437_MELEEUNIT_HPP