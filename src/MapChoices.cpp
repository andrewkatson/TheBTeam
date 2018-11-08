#include "MapChoices.hpp"

MapChoices::MapChoices(int obstacles, cafeteria cafeteria,  int entries){

  //never want fewer than 1 obstacles
  this -> obstacleChoice = obstacles >= 1 ? obstacles : 1;
  this -> pathEntryChoice = entries;
  this -> cafeteriaChoice = cafeteria;

}
