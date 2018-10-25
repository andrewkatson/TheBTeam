/*
  TowerManager.hpp

  Purpose: Manage the defensive tower units on the map

  @author Andrew Katson
 */

#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H
#include "TowerInterface.hpp"
#include "EventManager.hpp"
#include <vector>

using std::vector;
class TowerManager{

//event manager (used to register, deregister from events, and create them)
shared_ptr<EventManager> eventManager;

//All possible towers that can be purchased
vector<TowerInterface> towersToChoose;

//Towers placed on the board
vector<TowerInterface> towersPlaced;

public:
  TowerManager(shared_ptr<EventManager> eventManager);

  void delegateMethod(const EventInterface& event);
};
#endif
