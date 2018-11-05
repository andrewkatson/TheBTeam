#include "Obstacle.hpp"


Obstacle::Obstacle(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
}

void Obstacle::upgrade(){

}

void Obstacle::update(float delta){

}
