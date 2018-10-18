#include "MapChoices.hpp"

MapChoices::MapChoices(int obstacles, int cafeteria,  int entries){

  //never want fewer than 3 obstacles
  this -> obstacleChoice = obstacles >= 3 ? obstacles : 3;
  this -> pathEntryChoice = entries;
  this -> cafeteriaChoice = cafeteria;
}
