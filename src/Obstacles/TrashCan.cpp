#include "Obstacles/TrashCan.hpp"
TrashCan::TrashCan(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader) : Obstacle(eventManager, textLoader){
  this -> towerTypeID = textLoader -> getTypeID(string("IDS_TCO"));
  this -> price = textLoader -> getInteger(string("IDS_TC_PR"));
}
