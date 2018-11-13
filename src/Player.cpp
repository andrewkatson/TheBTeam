/*
  Player.cpp

  Purpose: Store and manage player attributes with set/get methods

  @author Jeremy Elkayam
 */

#include "Player.hpp"

Player::Player(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader)
{
  balance= textLoader->getInteger(string("IDS_P_B"));
  hitpoints= textLoader->getInteger(string("IDS_P_HP"));
  wave=textLoader->getInteger(string("IDS_Default_Wave"));
  level=textLoader->getInteger(string("IDS_Default_Level"));
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
}
