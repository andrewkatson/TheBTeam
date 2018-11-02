/*
  GameState.cpp

  Purpose: Store the current state of the game and provide methods to alter or
           get the current state of the game. Also stores game states.

  @author Jeremy Elkayam
 */
#include "GameState.hpp"

GameState::GameState(shared_ptr<EventManager> eventManager){
  //potentially make an Init state in which the game initializes itself?
  State main = State::MainMenu;
  setState(main);
  this -> eventManager = eventManager;
}

void GameState::setState(State& newState){
  this->currentState=newState;
}
