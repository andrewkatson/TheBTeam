#include "AllyCompView.hpp"

AllyCompView::AllyCompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,shared_ptr<PlayingScreenHeader> playingScreenHeader){
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> gameLogic = gameLogic;
  this -> waveManager = gameLogic->getWaveManager();
  this -> playingScreenHeader = playingScreenHeader;
}

void AllyCompView::updateCompView(float deltaS){
  if(gameLogic->getGameState()==State::Playing){
  }
}
