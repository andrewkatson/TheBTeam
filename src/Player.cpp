/*
  Player.cpp

  Purpose: Store and manage player attributes with set/get methods

  @author Jeremy Elkayam
 */

#include "Player.hpp"

Player::Player(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader)
{
  balance=textLoader -> getConstant(string("IDS_P_HP"));
  hitpoints=textLoader -> getConstant(string("IDS_P_B"));
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
}
