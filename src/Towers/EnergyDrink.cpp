#include "../include/Towers/EnergyDrink.hpp"

EnergyDrink::EnergyDrink(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
}

void EnergyDrink::upgrade(){}
