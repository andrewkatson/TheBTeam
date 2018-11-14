/*
  Player.hpp

  Purpose: Store and manage player attributes with set/get methods

  @author Jeremy Elkayam
 */

#ifndef PLAYER_H
#define PLAYER_H
#include "EventManager.hpp"
#include "TextLoader.hpp"
#include "Events/LoseHitpointsEvent.hpp"
#include "Events/WaveChangeEvent.hpp"
#include "Events/LevelChangeEvent.hpp"
#include "Events/BalanceChangeEvent.hpp"
#include <memory>
#include <chrono>

using std::shared_ptr;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
class Player{

private:

  /*
    balance: amount of currency the player currently possesses

    hitpoints: number of hit-points the player still has left

    wave: the current wave number

    level: the current level number
   */
  int balance,hitpoints, wave, level;

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

  void registerEvents();

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
    @return the player's wave as stored by the wave variable
.
   */
  int getWave(){return wave;}

  /*
    @return the current level .
   */
  int getLevel(){return level;}

  /*
    Set the balance to the given value.

    @param balance The new balance value for the player.
   */
  void updateBalance(int balance);

  /*
   * Add the passed value to the balance
   * and create an event
   */
  void modifyBalance(int modifyBy);

  /*
    Set the player's current hit-points to the given value.

    @param points The new hit-point value for the player.
   */
  void updateHitpoints(int points);

  /*
   * Subtract the passed value to the hitpoints
   */
  void modifyHitpoints(int pointsToDeduct);

  /*
   * Set the wave to be the passed wave number
   */
  void updateWave(int wave);

  /*
   * Set the level to be the passed wave number
   */
  void updateLevel(int level);


};

#endif
