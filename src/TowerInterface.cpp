#include "TowerInterface.hpp"

//Constructor
TowerInterface::TowerInterface(){
}

//Destructor
TowerInterface::~TowerInterface(){
  world -> DestroyBody(body);
}
