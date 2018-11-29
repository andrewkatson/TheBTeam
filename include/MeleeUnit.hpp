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

  //the money given to the player when they feed this unit
  int lunchMoney;

  //The unit's current hitpoints.
  int hitpoints;

  //The damage the unit can deal.
  int damage;

  //The amount of armor the unit has.
  int armor;

  //A reference to the unit that this unit is fighting.
  shared_ptr<MeleeUnit> engagedUnit;

  //The bar for rendering the unit's HP
  HitpointBar hpBar;

  //Seconds elapsed since the last change in sprite.
  float s_elapsed;

  //The index of the sprite that the actor is currently using.
  int current_sprite;

public:

  void update(float delta);

  /*
   * Set the coordinates of the actor to refer to its center
   */
  void setToCenter();

  void initSprite();

  int getLunchMoney() const;

  void setLunchMoney(int lunchMoney);

  void setHitpoints(int hitpoints);

  int getDamage() const;

  void setDamage(int damage);

  int getArmor() const;

  void setArmor(int armor);

  int getAttackRadius() const;

  shared_ptr<MeleeUnit> getEngagedUnit(){return engagedUnit;}

  void setAttackRadius(int attackRadius);

  /*
   * Default constructor
   */
  MeleeUnit(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader);

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
//  int getID(){return id;}
// Redundant AND confusing because ActorInterface has this same thing
// and it returns a long long (as it should). I think I did this some time ago
// and it should not work for this

  /*
    Returns the actor's sprite.

    @return the Sprite object that the interface contains.
   */
  sf::Sprite& getSprite(){return sprite;}//PEOPLE WHO KNOW MORE THAN ME: SHOULD THIS RETURN A REFERENCE?

  /*
    Move the actor according to its speed and the actor's innate properties.

    @param delta Time elapsed since the last game loop.
    @param xmult Either 1, 0, or -1. Determines the x-direction the unit is moving in.
    @param ymult Same as above but for y direction.

    This must be implemented by extending classes, since different types of
    actors obviously have different movement patterns.
  */
  void move(float delta,float xmult, float ymult);

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
