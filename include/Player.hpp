/*
  Player.hpp

  Purpose: Store and manage player attributes with set/get methods

  @author Jeremy Elkayam
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "EventManager.hpp"
#include "TextLoader.hpp"
#include <memory>

using std::shared_ptr;
class Player{

private:

  /*
    balance: amount of currency the player currently possesses

    hitpoints: number of hit-points the player still has left
   */
  int balance,hitpoints;

  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;

  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;

public:

  /*
    Initialize the player class. Sets balance and hitpoints to their default
    values.
   */
  Player(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);

  void delegateMethod(const EventInterface& event);

  /*
    Return the player's currency balance as stored by the balance instance
    variable.

    @return the currency balance in [units].
   */
  int getBalance(){return balance;}

  /*
    Return the player's current hit-points.

    @return the amount of hit-points the player currently has.
   */
  int getHitpoints(){return hitpoints;}

  /*
    Set the balance to the given value.

    @param balance The new balance value for the player.
   */
  int updateBalance(int balance){this->balance=balance;}

  /*
    Set the player's current hit-points to the given value.

    @param points The new hit-point value for the player.
   */
  int updateHitpoints(int points){this->hitpoints=points;}

};

#endif
