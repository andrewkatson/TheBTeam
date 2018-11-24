#include "CompView.hpp"
#include "GameState.hpp"

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

  for(int z=0;z<waveManager->getSpawnedEnemyUnits().size();z++){

    shared_ptr<MeleeUnit> currentUnit=waveManager->getSpawnedEnemyUnits()[z];

    if(!coordsInsideTile(currentUnit->getRow(),currentUnit->getCol(),currentUnit->getXCoordinate(),currentUnit->getXCoordinate())){
      int newCol=currentUnit->getXCoordinate()/playingScreenHeader->getTrueXTileSize();
      int newRow=currentUnit->getYCoordinate()/playingScreenHeader->getTrueYTileSize();
      currentUnit->setRow(newRow);
      currentUnit->setRow(newCol);
    }//make sure the col is up to date


    if(gameLogic->isExit(currentUnit->getRow(),currentUnit->getCol())){
      shared_ptr<EventInterface> actorDestroyed = make_shared<ActorDestroyedEvent>(currentUnit->getID(),deltaS);
      shared_ptr<EventInterface> hitpointsLost = make_shared<LoseHitpointsEvent>(currentUnit->getHitpoints()/4,deltaS);

      this -> eventManager -> queueEvent(actorDestroyed);
      this -> eventManager -> queueEvent(hitpointsLost);
    }else { //these don't need to happen if the unit hit the exit

      int r = currentUnit->getRow();
      int c = currentUnit->getCol();

      std::map<int, pair<int, int>> dists_coords;

      pair<int, int> relative_position;

      relative_position.first = -1;
      relative_position.second = 0;

      dists_coords[dists[r + relative_position.first][c + relative_position.second]] = relative_position;

      relative_position.first = 1;

      dists_coords[dists[r + relative_position.first][c + relative_position.second]] = relative_position;

      relative_position.first = 0;
      relative_position.second = 1;

      dists_coords[dists[r + relative_position.first][c + relative_position.second]] = relative_position;

      relative_position.first = 0;
      relative_position.second = -1;

      dists_coords[dists[r + relative_position.first][c + relative_position.second]] = relative_position;


      pair<int, int> new_direction = dists_coords.begin()->second; //get the one with the shortest distance

      float x_scale = 1 / (float) dists[0].size();
      float y_scale = 1 / (float) dists.size();

      currentUnit->move(currentUnit->getSpeed(), new_direction.first * x_scale, new_direction.second * y_scale);

      currentUnit->update(deltaS);
    }
  }
}


void CompView::delegateEvents(){}

bool CompView::coordsInsideTile(int row, int col,double x, double y){
  float min_x=playingScreenHeader->getTrueXTileSize()*col;
  float max_x=playingScreenHeader->getTrueXTileSize()*(col+1);
  float min_y=playingScreenHeader->getTrueYTileSize()*row;
  float max_y=playingScreenHeader->getTrueYTileSize()*(row+1);

  return (min_x < x && x < max_x) && (min_y < y && y < max_y);
};