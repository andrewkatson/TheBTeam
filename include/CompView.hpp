#ifndef COMPVIEW_H
#define COMPVIEW_H
#include "EventManager.hpp"
#include "TextLoader.hpp"
class CompView{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
public:
  CompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);

  void delegateMethod(const EventInterface& event);

  void updateCompView(float deltaS);

  void attackEnemies();

  void moveUnits();
  void delegateEvents();

};

#endif
