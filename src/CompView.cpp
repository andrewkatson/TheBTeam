#include "CompView.hpp"

CompView::CompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,shared_ptr<PlayingScreenHeader> playingScreenHeader){
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> gameLogic = gameLogic;
  this -> waveManager = gameLogic->getWaveManager();
  this -> playingScreenHeader = playingScreenHeader;
}

void CompView::updateCompView(float deltaS){
  if(gameLogic->getGameState()==State::Playing){
    moveUnits(deltaS);
  }
}

void CompView::attackEnemies(){}

// if there is a collsion subtracting health vs damage
// if unit makes it to exit (grid space 0) subtract remain health from player health and then set player health.

void CompView::moveUnits(float deltaS){

  // Poll the actor class for its speed and position on map, use the shortest distance >= 0
  //	and move that direction

  vector<vector<int>> dists=gameLogic->getDistances();

  //the unordered_map with all the melee units
  unordered_map<long long, shared_ptr<MeleeUnit>> spawnedUnits = waveManager -> getSpawnedEnemyUnits();

  for(unordered_map<long long, shared_ptr<MeleeUnit>>::const_iterator curr = spawnedUnits.begin(); curr != spawnedUnits.end(); ++curr){
    //the melee unit
    shared_ptr<MeleeUnit> unitToUpdate = (*curr).second;

    //figure out which square to move towards
    //move there
    //update your row and col
    unitToUpdate -> update(deltaS);
  }

}


void CompView::delegateEvents(){}

bool CompView::coordsInsideTile(int row, int col,double x, double y){
  float min_x=playingScreenHeader->getTrueXTileSize()*row;
  float max_x=playingScreenHeader->getTrueXTileSize()*(row+1);
  float min_y=playingScreenHeader->getTrueYTileSize()*col;
  float max_y=playingScreenHeader->getTrueYTileSize()*(col+1);

  return (min_x < x && x < max_x) && (min_y < y && y < max_y);
};
