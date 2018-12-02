#include "TowerInterface.hpp"

//Constructor
TowerInterface::TowerInterface(){
  //set the body to NULL in case we never set the world so the destructor does not try to destroy an unitialized body
  body = NULL;

  totalUpgradesPurchased = 0;

}

//Destructor
TowerInterface::~TowerInterface(){
  if(body){
    body -> DestroyFixture(fixture);
    world -> DestroyBody(body);
  }
}
