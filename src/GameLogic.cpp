/*
  GameLogic.cpp

  Purpose: Handle all logical processes for Food Fight.

  @author Andrew Katson, Jeremy Elkayam
 */
#include "GameLogic.hpp"

//Constructor.
GameLogic::GameLogic(){

  this -> boardManager = unique_ptr<BoardManager>(new BoardManager());
  this -> gameState = unique_ptr<GameState>(new GameState());
  this -> towerManager = unique_ptr<TowerManager>(new TowerManager());
  this -> eventManager = make_shared<EventManager>(EventManager());
}

//Called once every loop. Update according to elapsed time.
void GameLogic::updateGameLogic(float deltaS){


}
