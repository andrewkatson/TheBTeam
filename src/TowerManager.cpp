#include "TowerManager.hpp"

TowerManager::TowerManager(shared_ptr<EventManager> eventManager){
  this -> eventManager = eventManager;
}

//handle new event
void TowerManager::delegateMethod(const EventInterface& event){}
