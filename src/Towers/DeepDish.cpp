#include "../include/Towers/DeepDish.hpp"

DeepDish::DeepDish(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower() {
  this -> towerTypeID = towerTypeID;
}

void DeepDish::upgrade(){}
