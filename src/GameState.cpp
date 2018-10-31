/*
  GameState.cpp

  Purpose: Store the current state of the game and provide methods to alter or
           get the current state of the game. Also stores game states.

  @author Jeremy Elkayam
 */
#include "GameState.hpp"

GameState::GameState(shared_ptr<EventManager> eventManager){
  //potentially make an Init state in which the game initializes itself?
  setState(State::MainMenu);
  this -> eventManager = eventManager;
}

void GameState::setState(State newState){
  this->currentState=newState;
}

void GameState::setState(int newState){
  this->currentState=(State)newState;
}
