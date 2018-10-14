#include "GameLogic.hpp"

GameLogic::GameLogic(){

  this -> mapFactory = unique_ptr<MapFactory>(new MapFactory(new MapChoices(1,1,1,1), 5, 5));
}

void GameLogic::updateGameLogic(float deltaS){}
