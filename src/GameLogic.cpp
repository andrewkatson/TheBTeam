#include "GameLogic.hpp"

GameLogic::GameLogic(){

  this -> boardManager = unique_ptr<BoardManager>(new BoardManager());
}

void GameLogic::updateGameLogic(float deltaS){
  
  
}
