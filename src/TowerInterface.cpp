#include "TowerInterface.hpp"

//Constructor
TowerInterface::TowerInterface(){
  //set the body to NULL in case we never set the world so the destructor does not try to destroy an unitialized body
  body = NULL;

}

//Destructor
TowerInterface::~TowerInterface(){
  if(body){
    world -> DestroyBody(body);
  }
}
