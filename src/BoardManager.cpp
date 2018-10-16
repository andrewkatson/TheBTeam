#include "BoardManager.hpp"

BoardManager::BoardManager(){
  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(3,1,1,6), 10, 5));

}
