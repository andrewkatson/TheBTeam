#include "BoardManager.hpp"

BoardManager::BoardManager(){
  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(1,1,1,6), 10, 5));

  this -> mapFactory -> generateMap();
}
