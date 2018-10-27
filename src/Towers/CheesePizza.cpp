#include "../include/Towers/CheesePizza.hpp"

CheesePizza::CheesePizza(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
}

void CheesePizza::upgrade(){}
