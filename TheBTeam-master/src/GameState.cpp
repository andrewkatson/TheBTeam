/*
  GameState.cpp

  Purpose: Store the current state of the game and provide methods to alter or
           get the current state of the game. Also stores game states. 

  @author Jeremy Elkayam
 */
#include "GameState.hpp"

GameState::GameState(){
  //potentially make an Init state in which the game initializes itself?
  setState(State::Title);
}

void GameState::setState(State newState){
  this->currentState=newState;
}
