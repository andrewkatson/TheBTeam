#include "../include/Towers/Slushie.hpp"

Slushie::Slushie(shared_ptr<TextLoader> textLoader, string towerTypeID) : RangeTower(){
  this -> towerTypeID = towerTypeID;
}

void Slushie::upgrade(){}
