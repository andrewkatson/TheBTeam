/*
  Player.cpp

  Purpose: Store and manage player attributes with set/get methods

  @author Jeremy Elkayam
 */

#include "Player.hpp"

Player::Player(shared_ptr<EventManager> eventManager)
{
  balance=100;
  hitpoints=100;
  this -> eventManager = eventManager;
}

void Player::delegateMethod(const EventInterface& event){}
