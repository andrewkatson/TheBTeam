#include "Obstacles/TrashCan.hpp"
TrashCan::TrashCan(shared_ptr<TextLoader> textLoader, string towerTypeID,shared_ptr<EventManager> eventManager) : Obstacle(eventManager, textLoader){
  this -> towerTypeID = towerTypeID;
  this -> price = textLoader -> getInteger(string("IDS_TC_PR"));
}
