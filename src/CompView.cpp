#include "CompView.hpp"

CompView::CompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,shared_ptr<PlayingScreenHeader> playingScreenHeader){
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> gameLogic = gameLogic;
  this -> waveManager = gameLogic->getWaveManager();
  this -> playingScreenHeader = playingScreenHeader;
}

void CompView::updateCompView(float deltaS){
  if(gameLogic->getGameState()==State::Playing && !waveManager->getSpawnedEnemyUnits().empty()){
    moveUnits(deltaS);
  }
}

void CompView::attackEnemies(){}

// if there is a collsion subtracting health vs damage
// if unit makes it to exit (grid space 0) subtract remain health from player health and then set player health.

void CompView::moveUnits(float deltaS){
  assert(!gameLogic->getSpawnedEnemyUnits().empty());

  // Poll the actor class for its speed and position on map, use the shortest distance >= 0
  //	and move that direction

  vector<vector<int>> dists=gameLogic->getDistances();
  vector<vector<int>> floor=gameLogic->getFloor();

  for(auto iterator : waveManager->getSpawnedEnemyUnits()){
    shared_ptr<MeleeUnit> currentUnit= iterator.second;

    //printf("loop thru a unit\n");

    if(!coordsInsideTile(currentUnit->getRow(),currentUnit->getCol(),currentUnit->getXCoordinate(),currentUnit->getYCoordinate())){
      //printf("updating tile...\nx: %f\ny: %f\n",currentUnit->getXCoordinate(),currentUnit->getYCoordinate());
      int newCol=currentUnit->getXCoordinate()/playingScreenHeader->getTrueXTileSize();
      int newRow=currentUnit->getYCoordinate()/playingScreenHeader->getTrueYTileSize();
      currentUnit->setRow(newRow);
      currentUnit->setCol(newCol);
    }//make sure the tile is up to date

    //printf("checked the tile\nrow: %d\ncol: %d\n",currentUnit->getRow(),currentUnit->getCol());


    if(gameLogic->isExit(currentUnit->getRow(),currentUnit->getCol())){
      shared_ptr<EventInterface> actorDestroyed = make_shared<ActorDestroyedEvent>(currentUnit->getID(),deltaS);
      shared_ptr<EventInterface> hitpointsLost = make_shared<LoseHitpointsEvent>(currentUnit->getHitpoints()/4,deltaS);

      this -> eventManager -> queueEvent(actorDestroyed);
      this -> eventManager -> queueEvent(hitpointsLost);
    }else { //these don't need to happen if the unit hit the exit

      int r = currentUnit->getRow();
      int c = currentUnit->getCol();
      //printf("row=%d col=%d x=%f y=%f\n",r,c,currentUnit->getXCoordinate(),currentUnit->getYCoordinate());

      std::map<int, pair<int, int>> dists_coords;

      vector<pair<int, int>> relative_positions={make_pair(0,1),make_pair(1,0),make_pair(0,-1),make_pair(-1,0)};

      int adjusted_r,adjusted_c;

      for(auto dir : relative_positions){
        //printf("row + %d col %d \nfloor:%ldx%ld\n",dir.first,dir.second,floor.size(),floor[0].size());
        adjusted_r = r + dir.first;
        adjusted_c = c + dir.second;
        //printf("adjusted: %d, %d\n",adjusted_r,adjusted_c);
        //printf("0<= adjusted_r? %d\nadjusted_r < floor.size()? %d\n0 <= adjusted_c? %d\nadjusted_c < floor[0].size()? %d\n",
        //      (0 <= adjusted_r), (adjusted_r < floor.size()), (0 <= adjusted_c), (adjusted_c < floor[0].size()));
        if((0 <= adjusted_r) && (adjusted_r < floor.size()) && (0 <= adjusted_c) && (adjusted_c < floor[0].size())) {
          //printf("above floor grid: %d\n",floor[r + dir.first][c + dir.second]);
          if (floor[r + dir.first][c + dir.second] > 0) {
            //printf("huge succeeded\n");
            dists_coords[dists[r + dir.first][c + dir.second]] = dir;
          }
        }
      }
      assert(!dists_coords.empty());
      //printf("map size: %ld\n",dists_coords.size());

      pair<int, int> new_direction = dists_coords.begin()->second; //get the one with the shortest distance

      printf("going to next: %d %d\n",new_direction.first,new_direction.second);

      float x_scale = 1 / (float) dists[0].size();
      float y_scale = 1 / (float) dists.size();

      //currentUnit->move(currentUnit->getSpeed(), new_direction.first * x_scale, new_direction.second * y_scale);

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

  //printf("x=%f\ny=%f\nmin_x=%f\nmax_x=%f\nmin_y=%f\nmax_y=%f\n\nmin_x < x?:%d\nx < max_x?:%d\nmin_y < y?:%d\ny < max_y?:%d\n",x,y,min_x,max_x,min_y,max_y,min_x < x, x < max_x, min_y < y, y < max_y);

  return (min_x < x && x < max_x) && (min_y < y && y < max_y);
};
