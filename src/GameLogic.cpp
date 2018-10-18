/*
  GameLogic.cpp
  
  Purpose: Handle all logical processes for Food Fight.

  @author Andrew Katson, Jeremy Elkayam
 */
#include "GameLogic.hpp"

//Constructor.
GameLogic::GameLogic(){

  this -> boardManager = unique_ptr<BoardManager>(new BoardManager());
}

//Called once every loop. Update according to elapsed time.
void GameLogic::updateGameLogic(float deltaS){
  
  
}
