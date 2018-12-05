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
    updateUnits(deltaS);
  }
}

void CompView::attackEnemies(){}

// if there is a collsion subtracting health vs damage
// if unit makes it to exit (grid space 0) subtract remain health from player health and then set player health.

void CompView::updateUnits(float deltaS){
  assert(!gameLogic->getSpawnedEnemyUnits().empty());

  // Poll the actor class for its speed and position on map, use the shortest distance >= 0
  //	and move that direction

  vector<vector<int>> dists=gameLogic->getDistances();
  vector<vector<int>> floor=gameLogic->getFloor();
  /*
  printf("my distances: \n");
  for(auto z : dists){
    for(auto g : z){
      printf("%3d",g);
    }
    printf("\n");
  }

  printf("my floor: \n");
  for(auto z : floor){
    for(auto g : z){
      printf("%3d",g);
    }
    printf("\n");
  }
   */

  std::mt19937 rnd_gen (rd ());

  uniform_real_distribution<double>x_overshoot(0,playingScreenHeader->getTrueXTileSize()*.95);
  uniform_real_distribution<double>y_overshoot(0,playingScreenHeader->getTrueYTileSize()*.95);

  for(auto iterator : waveManager->getSpawnedEnemyUnits()){
    shared_ptr<MeleeUnit> currentUnit= iterator.second;
    //if you're not engaged with a unit do all the movement collide
    if (currentUnit->getEngagedUnit() == NULL ){
      //printf("loop thru a unit\n");

      if(!coordsInsideTile(currentUnit->getRow(),currentUnit->getCol(),currentUnit->getXCoordinate(),currentUnit->getYCoordinate())){
        //printf("updating tile...\nx: %f\ny: %f\n",currentUnit->getXCoordinate(),currentUnit->getYCoordinate());
        int newCol=currentUnit->getXCoordinate()/playingScreenHeader->getTrueXTileSize();
        int newRow=currentUnit->getYCoordinate()/playingScreenHeader->getTrueYTileSize();
        currentUnit->setRow(newRow);
        currentUnit->setCol(newCol);
      }//make sure the tile is up to date

      //if the unit is dead create an actor destroyed event and do nothing
      if(currentUnit->getHitpoints() <= 0){
        cout << "unit is dead" << endl;
        //the time object of the class
        auto now = high_resolution_clock::now();
        //the actual count in nanoseconds for the time
        auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
        //if the enemy was engaged with a unit we need to denengage them both
        if(currentUnit->getEngagedUnit() != NULL){
          currentUnit->getEngagedUnit() -> setEngagedUnit(NULL);
          currentUnit->setEngagedUnit(NULL);
        }
        shared_ptr<EventInterface> actorDestroyed = make_shared<ActorDestroyedEvent>(currentUnit->getID(),currentUnit, nowInNano);
        shared_ptr<EventInterface> playSound = make_shared<PlaySoundEvent>("",textLoader->getString("IDS_Unit_Death_Noise"), nowInNano);
        this -> eventManager -> queueEvent(actorDestroyed);
        this -> eventManager -> queueEvent(playSound);
        continue;
      }

      //printf("checked the tile\nrow: %d\ncol: %d\n",currentUnit->getRow(),currentUnit->getCol());


      if(gameLogic->isExit(currentUnit->getRow(),currentUnit->getCol())){
        shared_ptr<EventInterface> actorDestroyed = make_shared<ActorDestroyedEvent>(currentUnit->getID(),currentUnit,deltaS);
        shared_ptr<EventInterface> hitpointsLost = make_shared<LoseHitpointsEvent>(currentUnit->getHitpoints()*textLoader->getDouble("IDS_Percentage_Unit_Hitpoint_Player_Damage"),deltaS);
        shared_ptr<EventInterface> playSound = make_shared<PlaySoundEvent>("",textLoader->getString("IDS_Unit_Escape_Noise"),deltaS);

        if(currentUnit->getEngagedUnit() != NULL){
          currentUnit->getEngagedUnit() -> setEngagedUnit(NULL);
          currentUnit->setEngagedUnit(NULL);
        }

        this -> eventManager -> queueEvent(actorDestroyed);
        this -> eventManager -> queueEvent(hitpointsLost);
        this -> eventManager -> queueEvent(playSound);
      }
      else { //these don't need to happen if the unit hit the exit

        int r = currentUnit->getRow();
        int c = currentUnit->getCol();
        //printf("row=%d col=%d x=%f y=%f\n",r,c,currentUnit->getXCoordinate(),currentUnit->getYCoordinate());

        std::map<int, double> dists_coords;

        vector<double> angles={0,M_PI/2,M_PI,3*M_PI/2};

        int adjusted_r,adjusted_c,dir_r,dir_c;


        for(auto dir : angles){
          //printf("row + %d col %d \nfloor:%ldx%ld\n",dir.first,dir.second,floor.size(),floor[0].size());

          dir_r=-sin(dir);
          dir_c=cos(dir);
          //printf("checking %d %d\n",dir_r,dir_c);
          adjusted_r = r + dir_r;
          adjusted_c = c + dir_c;
          //printf("adjusted: %d, %d\n",adjusted_r,adjusted_c);
          //printf("0<= adjusted_r? %d\nadjusted_r < floor.size()? %d\n0 <= adjusted_c? %d\nadjusted_c < floor[0].size()? %d\n",
          //      (0 <= adjusted_r), (adjusted_r < floor.size()), (0 <= adjusted_c), (adjusted_c < floor[0].size()));
          if((0 <= adjusted_r) && (adjusted_r < floor.size()) && (0 <= adjusted_c) && (adjusted_c < floor[0].size())) {
            //wprintf("floor grid: %d\n",floor[adjusted_r][adjusted_c]);
            if (floor[r + dir_r][c + dir_c] >= 0) {
              //printf("huge succeeded\n");
              dists_coords[dists[adjusted_r][adjusted_c]] = dir;
            }
          }
        }
        assert(!dists_coords.empty());
        //printf("map size: %ld\n",dists_coords.size());

        double new_direction = dists_coords.begin()->second; //get the one with the shortest distance

        //printf("going to next: %lf\n",new_direction);


        double curdir=currentUnit->getDirection();

        if(new_direction==curdir){
          currentUnit->setOvershooting(false);
        }
        else{
          if(currentUnit->isOvershooting()){
            //if it didn't hit its target yet, keep overshooting, otherwise stop
            bool passedTarget=((curdir==0 && currentUnit->getXCoordinate()>currentUnit->getOvershoot()) //going right, so the cor should be greater than the overshoot
                    || (curdir==M_PI/2 && currentUnit->getYCoordinate()<currentUnit->getOvershoot()) // going up, so the cor should be less
                    || (curdir==M_PI && currentUnit->getXCoordinate()<currentUnit->getOvershoot())
                    || (curdir==3*M_PI/2 && currentUnit->getYCoordinate()>currentUnit->getOvershoot()));

            if(!passedTarget){
              new_direction=currentUnit->getDirection();
            }

          }
          else {
            double overshoot;
            if(curdir==0){
              overshoot=currentUnit->getXCoordinate()+x_overshoot(rnd_gen);
            }else if(curdir==M_PI/2){
              overshoot=currentUnit->getYCoordinate()-y_overshoot(rnd_gen);
            }else if(curdir==M_PI){
              overshoot=currentUnit->getXCoordinate()-x_overshoot(rnd_gen);
            }else{
              overshoot=currentUnit->getYCoordinate()+y_overshoot(rnd_gen);
            }
            currentUnit->setOvershoot(overshoot);

            currentUnit->setOvershooting(true);

            new_direction=currentUnit->getDirection();
          }
          //new_direction=currentUnit->getDirection();
        }


        currentUnit->setDirection(new_direction);

        currentUnit->move(deltaS);

        currentUnit->update(deltaS);
      }
    }
    //else we'll call another function to attack the enemy (attackengagedunit)
    else {
      currentUnit->updateAttack(deltaS);
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
