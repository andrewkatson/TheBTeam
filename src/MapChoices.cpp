#include "MapChoices.hpp"

MapChoices::MapChoices(int obstacles, int cafeteria, int pathLength, int entries){
  this -> obstacleChoice = obstacles;
  this -> pathEntryChoice = entries;
  this -> pathLengthChoice = pathLength;
  this -> cafeteriaChoice = cafeteria;
}
