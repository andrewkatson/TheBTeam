/*
  GameState.cpp

  Purpose: Store the current state of the game and provide methods to alter or
           get the current state of the game. Also stores game states. 

  @author Jeremy Elkayam
 */
#include "GameState.hpp"

GameState::GameState(){
  
}

void GameState::setState(int newState){
  this->currentState=newState;
}
