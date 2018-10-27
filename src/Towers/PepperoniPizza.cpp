#include "../include/Towers/PepperoniPizza.hpp"
PepperoniPizza::PepperoniPizza(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void PepperoniPizza::upgrade(){}
