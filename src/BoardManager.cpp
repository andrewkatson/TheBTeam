#include "BoardManager.hpp"

BoardManager::BoardManager(){
  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(1,1,3)));

}
