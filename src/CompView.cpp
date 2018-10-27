#include "CompView.hpp"

CompView::CompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
}

void CompView::delegateMethod(const EventInterface& event){}


void CompView::updateCompView(float deltaS){}

void CompView::attackEnemies(){}

// if there is a collsion subtracting health vs damage
// if unit makes it to exit (grid space 0) subtract remain health from player health and then set player health.

void CompView::moveUnits(){

}

// Poll the actor class for its speed and position on map, use the shortest distance >= 0
//	and move that direction

void CompView::delegateEvents(){}
