#include "GameLogic.hpp"

GameLogic::GameLogic(){

  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(1,1,1,1), 10, 5));

  this -> mapFactory -> generateMap();
}

void GameLogic::updateGameLogic(float deltaS){}
