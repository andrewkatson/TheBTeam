#ifndef COMPVIEW_H
#define COMPVIEW_H
#include "EventManager.hpp"
class CompView{
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
public:
  CompView(shared_ptr<EventManager> eventManager);

  void delegateMethod(const EventInterface& event);

  void updateCompView(float deltaS);

  void attackEnemies();

  void moveUnits();
  void delegateEvents();

};

#endif
