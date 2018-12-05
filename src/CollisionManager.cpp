#include "CollisionManager.hpp"


CollisionManager::CollisionManager(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager,
  shared_ptr<WaveManager> waveManager,
  shared_ptr<ProjectileManager> projectileManager){
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> waveManager = waveManager;
  this -> projectileManager = projectileManager;
  //the scaling used for the units so that they do not fill up an entire square
  unitScaleX = textLoader -> getDouble(string("IDS_Unit_Size_Scale_X"));
  unitScaleY =  textLoader -> getDouble(string("IDS_Unit_Size_Scale_Y"));
  registerDelegates();
}

CollisionManager::~CollisionManager(){
  deregisterDelegates();
  //cout << "num made " << nummade << " num destroyed " << numdestroyed << endl;

  for(auto it : towersPlaced){
    //cout << "towers "<< it.second.size() << endl;
  }

  for(auto it : alliedUnits){
    //cout << "allied units " << it.second.size() << endl;
  }

  for(auto it : enemyUnits){
    //cout << "Enemy units " << it.second.size() << endl;
    if(it.second.size() != 0){
      //cout << "position is " << it.first / cols << " " << it.first % cols << endl;
    }
  }
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void CollisionManager::registerDelegates(){
  //bind our delegate function for tower creation events
  EventManager::EventDelegate towerCreationEventDelegate = std::bind(&CollisionManager::handleTowerCreation, this, _1);

  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerCreationEventDelegate, textLoader -> getString(string("IDS_Collision_Manager_Tower_Creation")),towerCreationEventType);

  //bind our delegate function for tower remove events
  EventManager::EventDelegate towerRemoveEventDelegate = std::bind(&CollisionManager::handleTowerRemove, this, _1);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerRemoveEventDelegate, textLoader -> getString(string("IDS_Collision_Manager_Tower_Remove")),towerRemoveEventType);

  //bind our delegate function for actor creations (specifically projectiles)
  EventManager::EventDelegate actorCreatedDelegate = std::bind(&CollisionManager::handleActorCreated, this, _1);

  //make an event and get its type
  ActorCreatedEvent actorCreatedEvent = ActorCreatedEvent();
  EventType actorCreatedEventType = actorCreatedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorCreatedDelegate, textLoader -> getString(string("IDS_Collision_Manager_Actor_Creation")),actorCreatedEventType);

  //bind our delegate function for actor destructions (specifically projectiles)
  EventManager::EventDelegate actorDestroyedDelegate = std::bind(&CollisionManager::handleActorDestroyed, this, _1);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorDestroyedDelegate, textLoader -> getString(string("IDS_ProjectileManager_ActorCreated")),actorDestroyedEventType);
}


/*
 * Deregister all event delegates for this class
 */
void CollisionManager::deregisterDelegates(){
  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Collision_Manager_Tower_Creation")),towerCreationEventType);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Collision_Manager_Tower_Remove")),towerRemoveEventType);

  //make an event and get its type
  ActorCreatedEvent actorCreatedEvent = ActorCreatedEvent();
  EventType actorCreatedEventType = actorCreatedEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate( textLoader -> getString(string("IDS_Collision_Manager_Actor_Creation")),actorCreatedEventType);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_Collision_Manager_Actor_Destroy")),actorDestroyedEventType);
}

/*
 * Handle a tower creation event
 * @param event: the tower creation event
 */
void CollisionManager::handleTowerCreation(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * TowerCreationEvent type which allows us to access variables and methods
   * specific to TowerCreationEvent
   */
  const TowerCreationEvent* tcEvent = static_cast<const TowerCreationEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a TowerCreationEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  TowerCreationEventData* tcEventData = static_cast<TowerCreationEventData*>((tcEvent -> data).get());
  //get the tower id
  int towerPosID = tcEventData -> towerPosID;
  //get the type of the tower (an index corresponding to a type in towersToChoose)
  string towerTypeID = tcEventData -> towerTypeID;

  //decode the ID so that it is a row and column
  int row = towerPosID / cols;
  int col = towerPosID % cols;

}

/*
 * Handle a tower remove event
 * @param event: the tower remove event
 */
void CollisionManager::handleTowerRemove(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * TowerRemoveEvent type which allows us to access variables and methods
   * specific to TowerRemoveEvent
   */
  const TowerRemoveEvent* trEvent = static_cast<const TowerRemoveEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a TowerRemoveEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  TowerRemoveEventData* trEventData = static_cast<TowerRemoveEventData*>((trEvent -> data).get());
  //get the tower id
  int towerPosID = trEventData -> towerPosID;

  //decode the ID so that it is a row and column
  int row = towerPosID / cols;
  int col = towerPosID % cols;

}

void CollisionManager::handleActorCreated(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * ActorCreatedEvent type which allows us to access variables and methods
   * specific to ActorCreatedEvent
   */
  const ActorCreatedEvent* acEvent = static_cast<const ActorCreatedEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a ActorCreatedEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  ActorCreatedEventData* acEventData = static_cast<ActorCreatedEventData*>((acEvent -> data).get());
  //get the identifier for whether this is a projectile or not
  bool isProjectile = acEventData -> isProjectile;

  //the actor that was created
  shared_ptr<ActorInterface> actorCreated = acEventData -> actorCreated;

  //the row and col of the actor
  int row = actorCreated -> getRow();
  int col = actorCreated -> getCol();

  if(isProjectile){

    //add it to the map of projectiles
    projectilesFired.insert({actorCreated->getID(), actorCreated});
  }
  else{
    //if this is an allied unit we place it in a map only for the allied units
    if(actorCreated->isAnAlly()){
      //the row and col the ally is currently at
      //cout << "row " << actorCreated -> getRow() << " col " << actorCreated -> getCol() << endl;
      //cout << "x pos " << actorCreated -> getXCoordinate() << " y " << actorCreated -> getYCoordinate() << endl;
      if(inMap(row,col)){
        int combinedRowCol = actorCreated -> getRow() * cols + actorCreated -> getCol();
        //if there is not a row, col stored then we need to set one up
        if(alliedUnits.find(combinedRowCol) == alliedUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          alliedUnits.insert({combinedRowCol, emptyMap});
        }
        alliedUnits.at(combinedRowCol).insert({actorCreated->getID(), actorCreated});
      }
    }
    else{
      //the row and col the enemy is currently at
      //cout << "row en " << actorCreated -> getRow() << " col " << actorCreated -> getCol() << endl;
      //cout << "x pos en " << actorCreated -> getXCoordinate() << " y " << actorCreated -> getYCoordinate() << endl;
      if(inMap(row,col)){
        nummade++;
        int combinedRowCol = actorCreated -> getRow() * cols + actorCreated -> getCol();
        //if there is not a row, col stored then we need to set one up
        if(enemyUnits.find(combinedRowCol) == enemyUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          enemyUnits.insert({combinedRowCol, emptyMap});
        }
        enemyUnits.at(combinedRowCol).insert({actorCreated->getID(), actorCreated});
      }
    }
  }
}

void CollisionManager::handleActorDestroyed(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * ActorDestroyedEvent type which allows us to access variables and methods
   * specific to ActorDestroyedEvent
   */
  const ActorDestroyedEvent* adEvent = static_cast<const ActorDestroyedEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a ActorDestroyedEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  ActorDestroyedEventData* adEventData = static_cast<ActorDestroyedEventData*>((adEvent -> data).get());
  //get the id of the actor to check if it was a projectile
  long long actorDestroyedID = adEventData -> actorID;

  shared_ptr<ActorInterface> actorDestroyed = adEventData -> actorDestroyed;

  //the row and col of the actor
  int row = actorDestroyed -> getRow();
  int col = actorDestroyed -> getCol();

  //we do not destroy it normally if it is not a projectile
  if(!(actorDestroyed->isAProjectile())){
    //if this is an allied unit we place it in a map only for the allied units
    if(actorDestroyed->isAnAlly()){
      //the row and col the ally is currently at
      if(inMap(row,col)){
        int combinedRowCol = actorDestroyed -> getRow() * cols + actorDestroyed -> getCol();
        if(alliedUnits.find(combinedRowCol) == alliedUnits.end()){
          cerr << "allied unit not found in map on destruction " << endl;
          assert(true == false);
        }
        alliedUnits.at(combinedRowCol).erase(actorDestroyed->getID());
      }
    }
    else{
      //the row and col the enemy is currently at
      if(inMap(row,col)){
        numdestroyed++;
        int combinedRowCol = actorDestroyed -> getRow() * cols + actorDestroyed -> getCol();
        if(enemyUnits.find(combinedRowCol) == enemyUnits.end()){
          cerr << "enemy unit not found in map on destruction " << endl;
          assert(true == false);
        }
        enemyUnits.at(combinedRowCol).erase(actorDestroyed->getID());
      }
    }
  }
}

/*
 * Set the size of a row and col in pixels
 */
void CollisionManager::setGridDimensions(float x, float y){
  xTileSize = x;
  yTileSize = y;

  //update the tile stand in to reflect the size
  tile.setSize(sf::Vector2f(xTileSize, yTileSize));
}

/*
 * Set the dimensions of the grid
 */
void CollisionManager::setDimensions(int rows, int cols){
  this -> rows = rows;
  this -> cols = cols;
}

/*
 * Store a new tower created and store it after determining its location
 */
void CollisionManager::addNewTower(shared_ptr<TowerInterface> tower){
  //add the tower into any row and col that its radius touches
  addTowerByRadius(tower);
}

/*
 * Remove a tower stored in the list of collisions using its location and radius to determine what
 * cells in the unordered map it is part of
 */
void CollisionManager::removeOldTower(shared_ptr<TowerInterface> tower){
  //calculate the four corners of the ellipse that surrounds the tower (its range of rally or shooting)
  //and get pairs that represent the minimum row and the minimum col as well as the maximum row and the maximum col
  vector<intPair> minAndMax = minAndMaxRowCol(tower);

  assert(minAndMax.size()==2);

    //loop from minRow to maxRow
    for(int row = minAndMax.at(0).first; row <= minAndMax.at(1).first; row++){
      //loop from minCol to maxCol
      for(int col = minAndMax.at(0).second; col <= minAndMax.at(1).second; col++){
        //set the position this tile would be in
        tile.setPosition(sf::Vector2f(col*xTileSize, row*yTileSize));

        //if the tile we have set is within the circle
        if(tileInRadius(tower)){
          //cout << "intersecting! " << endl;
          //cout << "row " << row << " and col " << col << endl;

          int combinedRowCol = row*cols + col;
          //if the row,col pair does not have any towers in it we have to make one
          if(towersPlaced.find(combinedRowCol) == towersPlaced.end()){
            //should never go here
            cerr << "Collision Manager trying to remove a tower in a space it does not exist" << endl;
            assert(false);
          }

          //then place the tower to be at that combined row col
          towersPlaced.at(combinedRowCol).erase({tower->getID()});
      }
    }
  }
}

/*
 * Handle when a tower is upgraded in its radius to recalculate the row and cols it belongs to
 */
void CollisionManager::handleTowerRadiusUpgrade(shared_ptr<TowerInterface> towerUpgraded){
  addTowerByRadius(towerUpgraded);

}

/*
 * Calculate all the rows and columns a tower is "in" by using its radius
 * @param tower: the tower that is having its position on the board calculated
 */
void CollisionManager::addTowerByRadius(shared_ptr<TowerInterface> tower){
  //calculate the four corners of the ellipse that surrounds the tower (its range of rally or shooting)
  //and get pairs that represent the minimum row and the minimum col as well as the maximum row and the maximum col
  vector<intPair> minAndMax = minAndMaxRowCol(tower);

  assert(minAndMax.size()==2);

  //loop from minRow to maxRow
  for(int row = minAndMax.at(0).first; row <= minAndMax.at(1).first; row++){
    //loop from minCol to maxCol
    for(int col = minAndMax.at(0).second; col <= minAndMax.at(1).second; col++){
      //set the position this tile would be in
      tile.setPosition(sf::Vector2f(col*xTileSize, row*yTileSize));

      //if the tile we have set is within the circle
      if(tileInRadius(tower)){
        cout << "intersecting! " << endl;
        cout << "row " << row << " and col " << col << endl;

        int combinedRowCol = row*cols + col;
        //if the row,col pair does not have any towers in it we have to make one
        if(towersPlaced.find(combinedRowCol) == towersPlaced.end()){
          unordered_map<long long, shared_ptr<TowerInterface>> emptyMap;
          towersPlaced.insert({combinedRowCol, emptyMap});
        }

        //then place the tower to be at that combined row col
        towersPlaced.at(combinedRowCol).insert({tower->getID(), tower});
      }
    }
  }
}

/*
 * Calculate the four corners of the tower's radius. Checks whether a point lies
 * outside the map and corrects for it.
 * @return vector<intPair>: the two positions that represent the minimum row,col and the max row,col
 */
vector<intPair> CollisionManager::minAndMaxRowCol(shared_ptr<TowerInterface> tower){
  vector<intPair> minAndMaxPositions;

  //calculate the left position
  float leftX = tower->getXCoordinate()-tower->getXScale()*tower->getRadius();
  float leftY = tower->getYCoordinate();

  //if the left positions are anywhere over the edge
  if(leftX < 0.0){
    leftX = 0.0;
  }

  //the row and col pair on the left side
  int leftRow = leftY / yTileSize;
  int leftCol = leftX / xTileSize;

  //calculate the right position
  float rightX = tower->getXCoordinate()+tower->getXScale()*tower->getRadius();
  float rightY = tower->getYCoordinate();

  //if the right position is anywhere over the edge
  if(rightX > xTileSize*cols){
    rightX = xTileSize*cols - 1.0;
  }

  //the row and col pair on the right side
  int rightRow = rightY / yTileSize;
  int rightCol = rightX / xTileSize;

  //calculate the top position
  float topX = tower->getXCoordinate();
  float topY = tower->getYCoordinate()-tower->getYScale()*tower->getRadius();

  //if the top position is anywhere over the edge
  if(topY < 0){
    topY = 0.0;
  }

  //the row and col pair on the top side
  int topRow = topY / yTileSize;
  int topCol = topX / xTileSize;

  //calculate the bottom position
  float bottomX = tower->getXCoordinate();
  float bottomY = tower->getYCoordinate()+tower->getYScale()*tower->getRadius();

  //if the bottom position is anywhere over the edge
  if(bottomY > yTileSize*rows){
    bottomY = yTileSize*rows - 1.0;
  }

  //the row and col pair on the bottom side
  int bottomRow = bottomY / yTileSize;
  int bottomCol = bottomX / xTileSize;

  cout << "left " << leftRow << " " << leftCol << endl;
  cout << "right "  << rightRow << " " << rightCol << endl;
  cout << "top " << topRow << " " << topCol << endl;
  cout << "bottom " << bottomRow << " " << bottomCol << endl;

  //push in pairs representing the min row,min col and the max row and max col
  int minRow = (leftRow< rightRow) ? (leftRow < topRow ? (leftRow < bottomRow ? leftRow : bottomRow) : (topRow < bottomRow ? topRow : bottomRow)) : (rightRow <  topRow ? (rightRow < bottomRow ? rightRow : bottomRow) : (topRow < bottomRow ? topRow : bottomRow));
  int minCol = (leftCol< rightCol) ? (leftCol < topCol ? (leftCol < bottomCol ? leftCol : bottomCol) : (topCol < bottomCol ? topCol : bottomCol)) : (rightCol <  topCol ? (rightCol < bottomCol ? rightCol : bottomCol) : (topCol < bottomCol ? topCol : bottomCol));
  int maxRow = (leftRow> rightRow) ? (leftRow > topRow ? (leftRow > bottomRow ? leftRow : bottomRow) : (topRow > bottomRow ? topRow : bottomRow)) : (rightRow >  topRow ? (rightRow > bottomRow ? rightRow : bottomRow) : (topRow > bottomRow ? topRow : bottomRow));
  int maxCol =  (leftCol> rightCol) ? (leftCol > topCol ? (leftCol > bottomCol ? leftCol : bottomCol) : (topCol > bottomCol ? topCol : bottomCol)) : (rightCol >  topCol ? (rightCol > bottomCol ? rightCol : bottomCol) : (topCol > bottomCol ? topCol : bottomCol));

  cout << "mins " << minRow << " " << minCol << endl;
  cout << "maxs " << maxRow << " " << maxCol << endl;

  minAndMaxPositions.push_back(make_pair(minRow, minCol));
  minAndMaxPositions.push_back(make_pair(maxRow, maxCol));

  return minAndMaxPositions;
}

/*
 * @return bool: whether the tile is in the circle radius
 */
 bool CollisionManager::tileInRadius(shared_ptr<TowerInterface> tower){
   vector<floatPair> eightPoints = getFourCornersOfTileAndMidpoints();

   float towerX = tower -> getXCoordinate();
   float towerY = tower -> getYCoordinate();
   float towerRadius = tower->getRadius();
   float xScale = tower->getXScale();
   float yScale = tower->getYScale();

   //iterate through all four corners and if one lies within the bounds (And midpoints)
   //of the radius (which should be an ellipse) return true
   for(floatPair corner : eightPoints){
     //find distance of point from region bounded by the ellipse radius
     float distanceOfPoint = pow((corner.first - towerX),2)/pow((towerRadius*xScale),2) +  pow((corner.second - towerY),2)/pow((towerRadius*yScale),2);

     if(distanceOfPoint <= 1.0){
       return true;
     }
   }

   return false;
 }

/*
 * @return vector<floatPair>: all the four corners of the tile object and the midpoints
 */
vector<floatPair> CollisionManager::getFourCornersOfTileAndMidpoints(){
  vector<floatPair> eightPoints;

  sf::Vector2f dimensions = tile.getSize();
  sf::Vector2f position = tile.getPosition();

  //the eight corners
  eightPoints.push_back(make_pair(position.x, position.y));
  eightPoints.push_back(make_pair(position.x+dimensions.x, position.y));
  eightPoints.push_back(make_pair(position.x, position.y+dimensions.y));
  eightPoints.push_back(make_pair(position.x+dimensions.x, position.y+dimensions.y));

  //the midpoints of each side
  eightPoints.push_back(make_pair(position.x+(dimensions.x)/2.0, position.y));
  eightPoints.push_back(make_pair(position.x, position.y+(dimensions.y)/2.0));
  eightPoints.push_back(make_pair(position.x+dimensions.x, position.y + (dimensions.y)/2.0));
  eightPoints.push_back(make_pair(position.x+(dimensions.x)/2.0, position.y + dimensions.y));
  return eightPoints;
}

/*
 * Check for collisions between all objects within the same row, col
 */
void CollisionManager::checkForCollisions(float delta){
  //update the position of everything that can be moving
  updateAllUnitPositions();

  //run through all the populated rows and col (i.e. the ones touched by towers)
  //and check if they are impacting any units
  for(auto gridWithTowerRadius : towersPlaced){

    //if there are any towers here we check for collisions
    if(gridWithTowerRadius.second.size() != 0){

      //find the corresponding row,col pair in the map of enemy units
      int combinedRowCol = gridWithTowerRadius.first;

      //if there are none in this row, col we do not need to check
      if(enemyUnits.find(combinedRowCol) != enemyUnits.end()){

        //iterate through each tower that overlaps at this grid
        for(auto towerAndKeyAtGrid : gridWithTowerRadius.second){

          //iterate through the enemy units at this position
          for(auto gridWithEnemyUnits : enemyUnits.at(combinedRowCol)){

            //if there is a collision we only tell the tower since
            //only that will be taking any action
            auto isCollision = [this] (shared_ptr<ActorInterface> enemyUnit, shared_ptr<TowerInterface> tower)
            {
              sf::Sprite enemySprite = enemyUnit->getSprite();
              //the bounding rectangle will give us the dimensions of the sprite
              sf::FloatRect boundingBox = enemySprite.getGlobalBounds();
              //the x dimension of the box
              float xDim = boundingBox.width;
              //the ydimension of the box
              float yDim = boundingBox.height;
              //the scale in the x direction
              float xScaleSprite = (float) xTileSize / ((float) xDim*unitScaleX);
              //the scale in the y direction
              float yScaleSprite = (float) yTileSize / ((float) yDim*unitScaleY);

              enemySprite.setScale(xScaleSprite,yScaleSprite);
              enemySprite.setPosition(enemyUnit->getXCoordinate(), enemyUnit->getYCoordinate());

              //get the eight points that are on the bounding box of the rectangle relevant to this calculation
              auto eightPoints = [this](sf::FloatRect rect){
                vector<floatPair> eightPoints;

                //the eight corners
                eightPoints.push_back(make_pair(rect.left, rect.top));
                eightPoints.push_back(make_pair(rect.left+rect.width, rect.top));
                eightPoints.push_back(make_pair(rect.left, rect.top+rect.height));
                eightPoints.push_back(make_pair(rect.left+rect.width, rect.top+rect.height));

                //the midpoints of each side
                eightPoints.push_back(make_pair(rect.left+(rect.width)/2.0, rect.top));
                eightPoints.push_back(make_pair(rect.left, rect.top+(rect.height)/2.0));
                eightPoints.push_back(make_pair(rect.left+rect.width, rect.top + (rect.height)/2.0));
                eightPoints.push_back(make_pair(rect.left+(rect.width)/2.0, rect.top + rect.height));
                return eightPoints;
              }(enemySprite.getGlobalBounds());

              float towerX = tower -> getXCoordinate();
              float towerY = tower -> getYCoordinate();
              float towerRadius = tower->getRadius();
              float xScale = tower->getXScale();
              float yScale = tower->getYScale();

              //iterate through all four corners and if one lies within the bounds (And midpoints)
              //of the radius (which should be an ellipse) return true
              for(floatPair corner : eightPoints){
                //find distance of point from region bounded by the ellipse radius
                float distanceOfPoint = pow((corner.first - towerX),2)/pow((towerRadius*xScale),2) +  pow((corner.second - towerY),2)/pow((towerRadius*yScale),2);
                if(distanceOfPoint <= 1.0){
                  return true;
                }
              }
              return false;
            }(gridWithEnemyUnits.second, towerAndKeyAtGrid.second);

            if(isCollision){
              //if there is a collision the tower should attack the unit
              towerAndKeyAtGrid.second -> attack(gridWithEnemyUnits.second, delta);
            }
          }
        }
      }
    }
  }
}

/*
 * Special Function to calculate all collisions when a projectile explodes
 * called by GameLogic
 */
void CollisionManager::projectileExplosionCollisionCheck(shared_ptr<ActorInterface> projectile){
  //get the current row and col position of the projectile
  int currRow = projectile -> getYCoordinate() / yTileSize;
  int currCol = projectile -> getXCoordinate() / xTileSize;

  //get the minimum and maximum row,col pairs for the projectile
  vector<intPair> minAndMax = [this] (shared_ptr<ActorInterface> projectile){
    vector<intPair> minAndMaxPositions;

    //calculate the left position
    float leftX = projectile->getXCoordinate()-projectile->getXTowerScale()*projectile->getRadius();
    float leftY = projectile->getYCoordinate();

    //if the left positions are anywhere over the edge
    if(leftX < 0.0){
      leftX = 0.0;
    }

    //the row and col pair on the left side
    int leftRow = leftY / yTileSize;
    int leftCol = leftX / xTileSize;

    //calculate the right position
    float rightX = projectile->getXCoordinate()+projectile->getXTowerScale()*projectile->getRadius();
    float rightY = projectile->getYCoordinate();

    //if the right position is anywhere over the edge
    if(rightX > xTileSize*cols){
      rightX = xTileSize*cols - 1.0;
    }

    //the row and col pair on the right side
    int rightRow = rightY / yTileSize;
    int rightCol = rightX / xTileSize;

    //calculate the top position
    float topX = projectile->getXCoordinate();
    float topY = projectile->getYCoordinate()-projectile->getYTowerScale()*projectile->getRadius();

    //if the top position is anywhere over the edge
    if(topY < 0){
      topY = 0.0;
    }

    //the row and col pair on the top side
    int topRow = topY / yTileSize;
    int topCol = topX / xTileSize;

    //calculate the bottom position
    float bottomX = projectile->getXCoordinate();
    float bottomY = projectile->getYCoordinate()+projectile->getYTowerScale()*projectile->getRadius();

    //if the bottom position is anywhere over the edge
    if(bottomY > yTileSize*rows){
      bottomY = yTileSize*rows - 1.0;
    }

    //the row and col pair on the bottom side
    int bottomRow = bottomY / yTileSize;
    int bottomCol = bottomX / xTileSize;

    //push in pairs representing the min row,min col and the max row and max col
    int minRow = (leftRow< rightRow) ? (leftRow < topRow ? (leftRow < bottomRow ? leftRow : bottomRow) : (topRow < bottomRow ? topRow : bottomRow)) : (rightRow <  topRow ? (rightRow < bottomRow ? rightRow : bottomRow) : (topRow < bottomRow ? topRow : bottomRow));
    int minCol = (leftCol< rightCol) ? (leftCol < topCol ? (leftCol < bottomCol ? leftCol : bottomCol) : (topCol < bottomCol ? topCol : bottomCol)) : (rightCol <  topCol ? (rightCol < bottomCol ? rightCol : bottomCol) : (topCol < bottomCol ? topCol : bottomCol));
    int maxRow = (leftRow> rightRow) ? (leftRow > topRow ? (leftRow > bottomRow ? leftRow : bottomRow) : (topRow > bottomRow ? topRow : bottomRow)) : (rightRow >  topRow ? (rightRow > bottomRow ? rightRow : bottomRow) : (topRow > bottomRow ? topRow : bottomRow));
    int maxCol =  (leftCol> rightCol) ? (leftCol > topCol ? (leftCol > bottomCol ? leftCol : bottomCol) : (topCol > bottomCol ? topCol : bottomCol)) : (rightCol >  topCol ? (rightCol > bottomCol ? rightCol : bottomCol) : (topCol > bottomCol ? topCol : bottomCol));

    minAndMaxPositions.push_back(make_pair(minRow, minCol));
    minAndMaxPositions.push_back(make_pair(maxRow, maxCol));

    return minAndMaxPositions;
  }(projectile);


  //now we have to iterate through the row, col square described by the min, max pairs
  //and check for collisions withitn our radius
  assert(minAndMax.size()==2);


  //loop from minRow to maxRow
  for(int row = minAndMax.at(0).first; row <= minAndMax.at(1).first; row++){
    //loop from minCol to maxCol
    for(int col = minAndMax.at(0).second; col <= minAndMax.at(1).second; col++){
      //the combination of row and col
      int combinedRowCol = row * cols + col;

      //if there are none in this row, col we do not need to check
      if(enemyUnits.find(combinedRowCol) != enemyUnits.end()){
        //iterate through the enemy units at this position
        for(auto gridWithEnemyUnits : enemyUnits.at(combinedRowCol)){

          //if there is a collision we only tell the tower since
          //only that will be taking any action
          auto isCollision = [this] (shared_ptr<ActorInterface> enemyUnit, shared_ptr<ActorInterface> projectile)
          {
            sf::Sprite enemySprite = enemyUnit->getSprite();
            //the bounding rectangle will give us the dimensions of the sprite
            sf::FloatRect boundingBox = enemySprite.getGlobalBounds();
            //the x dimension of the box
            float xDim = boundingBox.width;
            //the ydimension of the box
            float yDim = boundingBox.height;

            //the scale in the x direction
            float xScaleSprite = (float) xTileSize / ((float) xDim*unitScaleX);
            //the scale in the y direction
            float yScaleSprite = (float) yTileSize / ((float) yDim*unitScaleY);

            enemySprite.setScale(xScaleSprite,yScaleSprite);
            enemySprite.setPosition(enemyUnit->getXCoordinate(), enemyUnit->getYCoordinate());
            //get the eight points that are on the bounding box of the rectangle relevant to this calculation
            auto eightPoints = [this](sf::FloatRect rect){
              vector<floatPair> eightPoints;

              //the eight corners
              eightPoints.push_back(make_pair(rect.left, rect.top));
              eightPoints.push_back(make_pair(rect.left+rect.width, rect.top));
              eightPoints.push_back(make_pair(rect.left, rect.top+rect.height));
              eightPoints.push_back(make_pair(rect.left+rect.width, rect.top+rect.height));

              //the midpoints of each side
              eightPoints.push_back(make_pair(rect.left+(rect.width)/2.0, rect.top));
              eightPoints.push_back(make_pair(rect.left, rect.top+(rect.height)/2.0));
              eightPoints.push_back(make_pair(rect.left+rect.width, rect.top + (rect.height)/2.0));
              eightPoints.push_back(make_pair(rect.left+(rect.width)/2.0, rect.top + rect.height));
              return eightPoints;
            }(enemySprite.getGlobalBounds());

            float projectileX = projectile -> getXCoordinate();
            float projectileY = projectile -> getYCoordinate();
            float projectileRadius = projectile->getRadius();
            float xScale = projectile->getXTowerScale();
            float yScale = projectile->getYTowerScale();
            //for enemies we have a higher bar of collisions
            int counterPointsInside = 0;

            //iterate through all four corners and if one lies within the bounds (And midpoints)
            //of the radius (which should be an ellipse) return true
            for(floatPair corner : eightPoints){
              //find distance of point from region bounded by the ellipse radius
              float distanceOfPoint = pow((corner.first - projectileX),2)/pow((projectileRadius*xScale),2) +  pow((corner.second - projectileY),2)/pow((projectileRadius*yScale),2);

              if(distanceOfPoint <= 1.0){
                return true;
              }
            }
            return false;
          }(gridWithEnemyUnits.second, projectile);

          if(isCollision){
            Projectile* attackWithProjectile = dynamic_cast<Projectile*>(projectile.get());
            //if there is a collision the tower should attack the unit
            attackWithProjectile -> damageUnit(gridWithEnemyUnits.second);
          }
        }
      }
    }
  }
}

/*
 * Update the position of all the units to reflect their current positions
 */
void CollisionManager::updateAllUnitPositions(){
  updateAllAllyUnitPositions();
  updateAllEnemyUnitPositions();
}

/*
 * Update the position of all units that are allies
 */
void CollisionManager::updateAllAllyUnitPositions(){
  //iterate through every row,col keyed map of units
  for(auto it : alliedUnits){
    int combinedRowCol = it.first;

    //iterate through each unit at the current row, col
    for(auto unitMap : it.second){
      shared_ptr<ActorInterface> alliedUnit = unitMap.second;

      int currentCombinedRowCol = alliedUnit->getRow() * cols + alliedUnit->getCol();

      //if the unit is no longer in the row, col pair then change its position in the map
      if(currentCombinedRowCol != combinedRowCol){
        alliedUnits.at(combinedRowCol).erase(alliedUnit->getID());

        //ensure that there is a new row,col pair map to place in
        if(alliedUnits.find(currentCombinedRowCol) == alliedUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          alliedUnits.insert({currentCombinedRowCol,emptyMap});
        }

        //place it at the new row, col pair
        alliedUnits.at(currentCombinedRowCol).insert({alliedUnit->getID(), alliedUnit});
      }
    }
  }
}

/*
 * Update the position of all units that are enemies
 */
void CollisionManager::updateAllEnemyUnitPositions(){
  //iterate through every row,col keyed map of units
  for(auto it : enemyUnits){
    int combinedRowCol = it.first;

    //iterate through each unit at the current row, col
    for(auto unitMap : it.second){
      shared_ptr<ActorInterface> enemyUnit = unitMap.second;

      int currentCombinedRowCol = enemyUnit->getRow() * cols + enemyUnit->getCol();

      //if the unit is no longer in the row, col pair then change its position in the map
      if(currentCombinedRowCol != combinedRowCol){
        numdestroyed++;
        enemyUnits.at(combinedRowCol).erase(enemyUnit->getID());

        //ensure that there is a new row,col pair map to place in
        if(enemyUnits.find(currentCombinedRowCol) == enemyUnits.end()){
          unordered_map<long long, shared_ptr<ActorInterface>> emptyMap;
          enemyUnits.insert({currentCombinedRowCol,emptyMap});
        }
        enemyUnits.at(currentCombinedRowCol).insert({enemyUnit->getID(), enemyUnit});
      }
    }
  }
}

/*
 * @return bool: whether this is in the map
 */
bool CollisionManager::inMap(int row, int col){
  if(row < 0 || row >= rows){
    return false;
  }
  if(col < 0 || col >= cols){
    return false;
  }
  return true;
}

/*
 * @return bool: whether this is in the window area
 */
bool CollisionManager::inMap(float x, float y){
  float windowX = rows * yTileSize;
  float windowY = cols * xTileSize;
  float e = 0.001;

  if(x < 0 || !(x <= windowX + e)){
    return false;
  }
  if(y < 0 || !(y <= windowY + e)){
    return false;
  }
  return true;
}
