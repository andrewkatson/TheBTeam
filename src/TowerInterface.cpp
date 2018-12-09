#include "TowerInterface.hpp"

//Constructor
TowerInterface::TowerInterface(){
  totalUpgradesPurchased = 0;
  //the id is the address of the current object
  towerID = (long long) this;


}



//Destructor
TowerInterface::~TowerInterface(){

}
