#include "PlayingScreen.hpp"



PlayingScreen::PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,
   shared_ptr<GameLogic> gameLogic,
  int windowX, int windowY) : mt(std::random_device()()){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> gameLogic = gameLogic;
  this -> playingScreenHeader = make_shared<PlayingScreenHeader>(eventManager, textLoader, gameLogic);
  rowSelected = 0;
  colSelected = 0;
  this -> waveGoingOn = false;
  somethingChanged = true;
  haveSetColorShift=false;
  this -> registerPersistentDelegates();
  this -> initDrawingMaterials();
  headerRecalculated=0;
}

PlayingScreen::~PlayingScreen(){
  this -> deregisterPersistentDelegates();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void PlayingScreen::registerDelegates(){
  //bind our delegate function for map generation events
  EventManager::EventDelegate mapGeneratedEventDelegate = std::bind(&PlayingScreen::handleMapGenerated, this, _1);

  //make an event and get its type
  MapGeneratedEvent mapGeneratedEvent = MapGeneratedEvent();
  EventType mapGeneratedEventType = mapGeneratedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mapGeneratedEventDelegate,
  textLoader -> getString(string("IDS_PS_MG")),mapGeneratedEventType);


  //bind our delegate function for tower creation events
  EventManager::EventDelegate towerCreationEventDelegate = std::bind(&PlayingScreen::handleTowerCreation, this, _1);

  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerCreationEventDelegate,
  textLoader -> getString(string("IDS_PS_TC")),towerCreationEventType);


  //bind our delegate function for tower remove events
  EventManager::EventDelegate towerRemoveEventDelegate = std::bind(&PlayingScreen::handleTowerRemove, this, _1);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerRemoveEventDelegate,
  textLoader -> getString(string("IDS_PS_TR")),towerRemoveEventType);

  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&PlayingScreen::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_PS_KP")),keyPressEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&PlayingScreen::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_PS_MP")),mousePressEventType);


  EventManager::EventDelegate wcDelegate = std::bind(&PlayingScreen::handleWaveChange, this, _1);

  WaveChangeEvent wcEvent = WaveChangeEvent();
  EventType wceType = wcEvent.getEventType();
  this -> eventManager -> registerDelegate(wcDelegate, textLoader -> getString(string("IDS_PlayingScreen_WaveChange")),wceType);



  //register delegates for the header
  playingScreenHeader -> registerDelegates();
  //register delegates for the upgrade circle
  upgradeCircle -> registerDelegates();

}

/*
 * Register the delegate methods for this class
 * with any events it needs to know about
 * used for any delegate methods that should never be deregistered
 */
void PlayingScreen::registerPersistentDelegates(){

  //bind our delegate function for mouse presses
  EventManager::EventDelegate stateChangeDelegate = std::bind(&PlayingScreen::handleStateChange, this, _1);

  //make an event and get its type
  StateChangeEvent stateChangeEvent = StateChangeEvent();
  EventType stateChangeEventType = stateChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(stateChangeDelegate, textLoader -> getString(string("IDS_PS_SC")),stateChangeEventType);
}

/*
 * Deregister all persistent delegates
 */
void PlayingScreen::deregisterPersistentDelegates(){

  //make an event and get its type
  StateChangeEvent stateChangeEvent = StateChangeEvent();
  EventType stateChangeEventType = stateChangeEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PS_SC")),stateChangeEventType);

}


/*
 * Deregister the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void PlayingScreen::deregisterDelegates(){
  //make an event and get its type
  MapGeneratedEvent mapGeneratedEvent = MapGeneratedEvent();
  EventType mapGeneratedEventType = mapGeneratedEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(
  textLoader -> getString(string("IDS_PS_MG")),mapGeneratedEventType);

  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PS_TC"))
                                          ,towerCreationEventType);

  //make an event and get its type
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  //deregister the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PS_TR"))
                                          ,towerRemoveEventType);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PS_KP")),keyPressEventType);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PS_MP")),mousePressEventType);

  //deregister the delegates for the header
  playingScreenHeader -> deregisterDelegates();
  //deregister the deleagtes for the upgrade circle
  upgradeCircle -> deregisterDelegates();
}


/*
 * Initialize all the things used for drawing (shapes, fonts)
 */
void PlayingScreen::initDrawingMaterials(){
  initRallyPointButton();
  initUpgradeCircle();
}

/*
 * Initialize the rally point button
 */
void PlayingScreen::initRallyPointButton(){
  bool makeItCircle = true;
  //make a circular button for the rally point for any tower
  this -> rallyPointChange = unique_ptr<Button>(new Button(windowX, windowY, 0.0, 0.0, textLoader,
     textLoader->getString("IDS_Rally_Flag_Icon"), makeItCircle));
  //set the radius of the circle to be its initial size
  rallyPointChange -> setCircleRadius(textLoader->getInteger("IDS_Button_Radius"));
  //set the origin of the circle shape to be its center
  rallyPointChange -> setOrigin(textLoader->getInteger("IDS_Button_Radius"), textLoader->getInteger("IDS_Button_Radius"));

  //load in the color components of the button's color
  float redComponent = textLoader -> getInteger(string("IDS_Rally_Flag_Outline_Color_Red"));
  float greenComponent = textLoader -> getInteger(string("IDS_Rally_Flag_Outline_Color_Green"));
  float blueComponent = textLoader -> getInteger(string("IDS_Rally_Flag_Outline_Color_Blue"));
  float alphaComponent = textLoader -> getInteger(string("IDS_Rally_Flag_Outline_Color_Alpha"));
  //set the outline color for the rally point button
  rallyPointChange -> setOutlineColor(redComponent, greenComponent, blueComponent, alphaComponent);

  //set the outline color thickness
  rallyPointChange -> setOutlineThickness(textLoader->getInteger(string("IDS_Rally_Flag_Outline_Thickness")));
  //make it initially invisible
  rallyPointChange -> flipVisibility();
}

/*
 * Initialize the upgrade circle that is drawn above a tower when it is clicked with right click
 */
void PlayingScreen::initUpgradeCircle(){
  upgradeCircle = unique_ptr<UpgradeCircle>(new UpgradeCircle(eventManager, textLoader, gameLogic, windowX, windowY));
}

/*
 * Initialize the 2d vectors holding all the r,g,b color value shifts
 */
void PlayingScreen::initColorShifts(){
  initColorShiftsForFloor();
  initColorShiftsForPath();
}

/*
 * Initialize a 2d vector to hold r,g,b color values to allow us to shift
 * each tile by a consistent amount (for floorGrid)
 */
void PlayingScreen::initColorShiftsForFloor(){
  //rows
  int rows = gameLogic -> getRows();
  //cols
  int cols = gameLogic -> getCols();

  //set the number of rows
  floorColorShifts.resize(rows);

  //the distribution we generate numbers for
  std::uniform_int_distribution<int> dist(-1000,1000);

  //the ranges we can genearate a color shift value in
  int maxRedRangeShift = textLoader -> getInteger(string("IDS_Path_Tile_Red_Shift_Random_Range"));
  int maxGreenRangeShift = textLoader -> getInteger(string("IDS_Path_Tile_Green_Shift_Random_Range"));
  int maxBlueRangeShift = textLoader -> getInteger(string("IDS_Path_Tile_Blue_Shift_Random_Range"));

  //iterate through the board
  for(int row = 0; row < rows; row++){
    //set the number of columns
    floorColorShifts.at(row).resize(cols);
    for(int col = 0; col < cols; col++){
      //generate a red shift value
      int redShift = dist(mt)%maxRedRangeShift;
      //generate a blue shit value
      int blueShift = dist(mt)%maxBlueRangeShift;
      //generate a green shift value
      int greenShift = dist(mt)%maxGreenRangeShift;
      //create a tuple
      rgb colors = make_tuple(redShift, greenShift, blueShift);

      //add it to this row and col
      floorColorShifts.at(row).at(col) = colors;
    }
  }
}

/*
 * Initialize a 2d vector to hold r,g,b color values to allow us to shift
 * each tile by a consistent amount (for pathGrid)
 */
void PlayingScreen::initColorShiftsForPath(){

  //rows
  int rows = gameLogic -> getRows();
  //cols
  int cols = gameLogic -> getCols();

  //set the number of rows
  pathColorShifts.resize(rows);

  //the distribution we generate numbers for
  std::uniform_int_distribution<int> dist(-1000,1000);

  //the ranges we can genearate a color shift value in
  int maxRedRangeShift = textLoader -> getInteger(string("IDS_Path_Tile_Red_Shift_Random_Range"));
  int maxGreenRangeShift = textLoader -> getInteger(string("IDS_Path_Tile_Green_Shift_Random_Range"));
  int maxBlueRangeShift = textLoader -> getInteger(string("IDS_Path_Tile_Blue_Shift_Random_Range"));

  //iterate through the board
  for(int row = 0; row < rows; row++){
    //set the number of columns
    pathColorShifts.at(row).resize(cols);
    for(int col = 0; col < cols; col++){
      //generate a red shift value
      int redShift = dist(mt)%maxRedRangeShift;
      //generate a blue shit value
      int blueShift = dist(mt)%maxBlueRangeShift;
      //generate a green shift value
      int greenShift = dist(mt)%maxGreenRangeShift;
      //create a tuple
      rgb colors = make_tuple(redShift, greenShift, blueShift);

      //add it to this row and col
      pathColorShifts.at(row).at(col) = colors;
    }
  }
}

/*
 * Handle any map generated
 * @param event: event of the tower creation
 */
void PlayingScreen::handleMapGenerated(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * MapGeneratedEvent type which allows us to access variables and methods
   * specific to MapGeneratedEvent
   */
  const MapGeneratedEvent* mgEvent = static_cast<const MapGeneratedEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a TowerCreationEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  MapGeneratedEventData* mgEventData = static_cast<MapGeneratedEventData*>((mgEvent -> data).get());

  //allow the color shift vector to be recalculated
  haveSetColorShift = false;
}

/*
 * Handle any tower creation
 * @param event: event of the tower creation
 */
void PlayingScreen::handleTowerCreation(const EventInterface& event){
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

  somethingChanged = true;
}

/*
 * Handle a tower remove event
 * @param event: the tower remove event
 */
void PlayingScreen::handleTowerRemove(const EventInterface& event){
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

  somethingChanged = true;

}

/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void PlayingScreen::handleKeyPress(const EventInterface& event){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * KeyPressEvent type which allows us to access variables and methods
   * specific to KeyPressEvent
   */
  const KeyPressEvent* kpEvent = static_cast<const KeyPressEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a KeyPressEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  KeyPressEventData* kpEventData = static_cast<KeyPressEventData*>((kpEvent -> data).get());
  //get the key string identifier from the data
  string key = kpEventData -> keyID;

  if(key == "B"){
    shared_ptr<EventInterface> mainMenuState = make_shared<StateChangeEvent>(State::MainMenu, nowInNano);

    this -> eventManager -> queueEvent(mainMenuState);
  }else if(key == "W" && !waveGoingOn){
    printf("ok, starting a wave\n");
    shared_ptr<EventInterface> waveChangeEvent = make_shared<WaveChangeEvent>(playingScreenHeader->getWaveNumber(),nowInNano,true);

    eventManager -> queueEvent(waveChangeEvent);
  }
}

void PlayingScreen::handleWaveChange(const EventInterface& event){
  auto wcEvent = static_cast<const WaveChangeEvent *>(&event);
  auto wcEventData = static_cast<WaveChangeEventData *>((wcEvent->data).get());

  waveGoingOn = wcEventData->waveStart;
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void PlayingScreen::handleMousePress(const EventInterface& event){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * MousePressEvent type which allows us to access variables and methods
   * specific to MousePressEvent
   */
  const MousePressEvent* mpEvent = static_cast<const MousePressEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a KeyPressEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  MousePressEventData* mpEventData = static_cast<MousePressEventData*>((mpEvent -> data).get());

  //get whether this is a left or right click
  string mouseButtonPressed = mpEventData -> partOfMouse;

  //get the xposition
  float xPos = mpEventData -> x;
  //get the y position
  float yPos = mpEventData -> y;

  //get the size of a tile in the x
  float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //get the size of a tile in the y
  float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //what row is being clicked
  int row = (int) yPos / yTileSize;
  //what col is being clicked
  int col = (int) xPos / xTileSize;

  //get the currently selected tower (if the rally flag is visible a tower must be selected)
  const unordered_map<int, shared_ptr<TowerInterface>> towers = gameLogic -> getTowersPlaced();

  //if the current row and col does not have a tower on them
  //ensure that the rally flag is both invisible and unchecked
  int combinedRowCol = rowSelected*gameLogic->getCols() + colSelected;
  if(towers.find(combinedRowCol) == towers.end()){
    if(rallyPointChange -> isCurrentlyVisible()){
      rallyPointChange->flipVisibility();
    }
    if(rallyPointChange->isButtonClicked()){
      rallyPointChange->clickButton();
    }
  }

  //if the upgrade circle is displayed we ignore the click
  if(!(upgradeCircle -> isCurrentlyVisible())){
    //if this is a right click we still ignore the click
    if(mouseButtonPressed == "Left"){
      //if we have clicked the rally point flag icon
      if(rallyPointChange -> isCurrentlyVisible()){
        if(rallyPointChange -> isSelected(xPos, yPos)){

          int combinedRowCol = rowSelected*gameLogic->getCols() + colSelected;

          shared_ptr<TowerInterface> tower = towers.at(combinedRowCol);
          //check that it is within the bounds of the radius circle of the tower
          //if it is not then we cannot click the rally point flag
          //also check if this is a path tile or if this is the first click (i,e, the position is the center of the tower)
          if(clickWithinRange(xPos, yPos,tower) && ((clickedOnAPath(xPos, yPos)) || (firstTimeClickOnRallyFlag(tower)) && !(rallyPointChange -> isButtonClicked()))){
            rallyPointChange -> clickButton();
          }
          else{
            return;
          }
          if(rallyPointChange -> isButtonClicked()){
            //we want the header to ignore mouse presses when we have selected the flag icon
            playingScreenHeader -> flipClickCheck();
          }
          else{
            //if we have clicked it for a second time (thus unclick) and it was in bounds
            //then we reset the rally point for the tower
            MeleeTower* meleeTower = dynamic_cast<MeleeTower*>(tower.get());
            //if the clcik was out of range the rally point is not reset
            if(clickWithinRange(xPos, yPos, tower)){
              meleeTower->resetRallyPoint(xPos,yPos);
            }
            //allow the header to check again
            if(!(playingScreenHeader->clicksCheckedFor())){
              playingScreenHeader -> flipClickCheck();
            }
            //make sure that the flag is not visible
            if(rallyPointChange -> isCurrentlyVisible()){
              rallyPointChange -> flipVisibility();
            }
            //make sure it is unclicked
            if(rallyPointChange -> isButtonClicked()){
              rallyPointChange -> clickButton();
            }
          }
          //if we click the rally point flag we do not continue as normal
          return;
        }
      }
      //if the rally point is not visible AND we know the upgrade circle is not visible
      //then always unlock the header
      else{
        if(!(playingScreenHeader->clicksCheckedFor())){
          playingScreenHeader->flipClickCheck();
        }
      }

      //if the row and col are the same as the last click
      if(row == rowSelected && col == colSelected){
        if(gameLogic -> isTower (row,col)){
          const unordered_map<int, shared_ptr<TowerInterface>> towers = gameLogic -> getTowersPlaced();
          int combinedRowCol = row*gameLogic->getCols() + col;
          shared_ptr<TowerInterface> towerToSetVisibility = towers.at(combinedRowCol);
          towerToSetVisibility -> flipRadiusVisibility();
        }
      }
      //otherwise reset the pair after we check if we were just clicking on a tower
      //if so flip its visible radius off
      else{
        if(gameLogic -> isTower(rowSelected,colSelected)){
          const unordered_map<int, shared_ptr<TowerInterface>> towers = gameLogic -> getTowersPlaced();
          int combinedRowCol = rowSelected*gameLogic->getCols() + colSelected;
          shared_ptr<TowerInterface> towerToSetVisibility = towers.at(combinedRowCol);
          if(towerToSetVisibility->isRadiusVisible()){
            towerToSetVisibility -> flipRadiusVisibility();
          }
        }
        rowSelected = row;
        colSelected = col;
      }
    }
    else{
      if(gameLogic -> isTower(rowSelected,colSelected)){
        const unordered_map<int, shared_ptr<TowerInterface>> towers = gameLogic -> getTowersPlaced();
        int combinedRowCol = rowSelected*gameLogic->getCols() + colSelected;
        shared_ptr<TowerInterface> towerToSetVisibility = towers.at(combinedRowCol);
        if(towerToSetVisibility->isRadiusVisible()){
          towerToSetVisibility -> flipRadiusVisibility();
        }
      }
      rowSelected = row;
      colSelected = col;
    }
  }
  else{
    //we want to block clicks on the header if the upgrade circle is open
    if(playingScreenHeader->clicksCheckedFor()){
      playingScreenHeader->flipClickCheck();
    }
    if(gameLogic -> isTower(rowSelected,colSelected)){
      const unordered_map<int, shared_ptr<TowerInterface>> towers = gameLogic -> getTowersPlaced();
      int combinedRowCol = rowSelected*gameLogic->getCols() + colSelected;
      shared_ptr<TowerInterface> towerToSetVisibility = towers.at(combinedRowCol);
      if(towerToSetVisibility->isRadiusVisible()){
        towerToSetVisibility -> flipRadiusVisibility();
      }
    }
    rowSelected = row;
    colSelected = col;
  }
}

/*
 * @return whether the passed positions are within the towers radius
 */
bool PlayingScreen::clickWithinRange(float mouseX, float mouseY, shared_ptr<TowerInterface> tower){
  //the size of each tile in x direction
  const float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //get the sprite to be drawn
  sf::Sprite currentSprite = tower -> getSprite();

  //the bounding rectangle will give us the dimensions of the sprite
  sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
  //the x dimension of the box
  float xDim = boundingBox.width;
  //the ydimension of the box
  float yDim = boundingBox.height;

  //the x and y position of the tower
  float towerX = tower -> getXCoordinate();
  float towerY = tower -> getYCoordinate();

  //the scale in the x direction
  float xScale = (float) xTileSize / (float) xDim;
  //the scale in the y direction
  float yScale = (float) yTileSize / (float) yDim;

  //the radius of the tower's effect area (either respawn or shooting range)
  float radius = tower -> getRadius();

  //find distance of point from region bounded by the ellipse radius
  float distanceOfPoint = pow((mouseX - towerX),2)/pow((radius*xScale),2) +  pow((mouseY - towerY),2)/pow((radius*yScale),2);

  if(distanceOfPoint <= 1.0){
    return true;
  }
  return false;
}

/*
 * @return when the position passed refers to a path tile
 */
bool PlayingScreen::clickedOnAPath(float mouseX, float mouseY){
  //get the size of a tile in the x
  float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //get the size of a tile in the y
  float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //what row is being clicked
  int row = (int) mouseY / yTileSize;
  //what col is being clicked
  int col = (int) mouseX / xTileSize;

  return gameLogic->isPath(row,col);
}

/*
 * @return whether this click is one where the tower is at its initial placement
 */
bool PlayingScreen::firstTimeClickOnRallyFlag(shared_ptr<TowerInterface> tower){
  MeleeTower* meleeTower = dynamic_cast<MeleeTower*>(tower.get());

  return meleeTower->getRallyX() == meleeTower -> getXCoordinate() && meleeTower -> getRallyY() == meleeTower->getYCoordinate();
}

/*
 * Handle a state change
 * @param event: event of the state change
 */
void PlayingScreen::handleStateChange(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * StateChangeEvent type which allows us to access variables and methods
   * specific to StateChangeEvent
   */
  const StateChangeEvent* scEvent = static_cast<const StateChangeEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a StateChangeEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  StateChangeEventData* scEventData = static_cast<StateChangeEventData*>((scEvent -> data).get());

  State state = scEventData -> state;

  //we will only care if the state is the current one
  //because there will be data in it that we need
  if(state != State::Playing){
    return;
  }

  playingScreenHeader -> softReset();

}



void PlayingScreen::draw(sf::RenderWindow &window){


  //initlaize the color shift vectors
  //if we have not or this is a new board
  if(!haveSetColorShift){
    initColorShifts();
    haveSetColorShift=true;
  }
  drawFloorMap(window);
  drawTowersAndObstacles(window);
  //to avoid looping twice we draw all the units of the towers in the
  //same method as drawing the towers
  drawEnemyUnits(window);
  drawProjectiles(window);

  playingScreenHeader -> draw(window);

  //draw the upgrade circle
  upgradeCircle -> draw(window);

  //TODO change into real code for drawing the map!
  if(somethingChanged){
    cout << endl << "THE FLOOR " << endl;
    const vector<vector<int>> floor = gameLogic -> getFloor();
    printVector(floor);

    cout << endl << "ABOVE THE FLOOR" << endl;
    const vector<vector<int>> aboveFloor = gameLogic -> getAboveFloor();
    printVector(aboveFloor);

    cout << endl << "DISTANCES " << endl;
    const vector<vector<int>> distances = gameLogic -> getDistances();
    printVector(distances);

    somethingChanged = false;
  }
}

/*
 * Draw the floor of the map (i.e. anything on the floorGrid: floor tiles, path tiles, and exit )
 * @param window: the game window to draw on
 */
void PlayingScreen::drawFloorMap(sf::RenderWindow& window){
  //the 2d grid with ASCII representations of each tile
  const vector<vector<int>> floorGrid = gameLogic -> getFloor();

  assert(floorGrid.size()!=0);

  //the size of each tile in x direction
  const float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //set the rectangle used to draw to be these dimensions
  sf::RectangleShape floorRect(sf::Vector2f((float)xTileSize,(float) yTileSize));

  //iterate through the 2d grid
  for(int row = 0; row < floorGrid.size(); row++){
    for(int col = 0; col < floorGrid.at(0).size(); col++){
      int floorValue = floorGrid.at(row).at(col);
      //if this is a path
      if(floorValue > 0){
        drawFloorPath(window, row, col, yTileSize, xTileSize, floorValue, floorRect);
      }
      //if this is a floor tile
      else if(floorValue < 0){
        drawFloorTile(window, row, col, yTileSize, xTileSize, floorValue, floorRect);
      }
      //if this is the exit
      else if(floorGrid.at(row).at(col) == 0){
        drawFloorExit(window, row, col, yTileSize, xTileSize, floorRect);
      }
    }
  }
}

void PlayingScreen::drawFloorPath(sf::RenderWindow& window, int row, int col,
  float yTileSize, float xTileSize, int pathValue, sf::RectangleShape& floorRect){

    //the string built from path tile value
    string pathTypeBase = "IDS_Path_Tile_" + to_string(pathValue) + "_Fill_Color_";

    //check if the path exists
    int checkPathColorValue = textLoader -> getInteger(pathTypeBase + string("Red"));

    //hold our rgba values for this tile
    int redComponent;
    int greenComponent;
    int blueComponent;
    int alphaComponent;


    //if this was an actual path version
    if(checkPathColorValue != -1){

      //weird tuple syntax but it just grabs the color shift in the tuple for this row, col
      int redShift = get<0>(pathColorShifts.at(row).at(col));
      int greenShift = get<1>(pathColorShifts.at(row).at(col));
      int blueShift = get<2>(pathColorShifts.at(row).at(col));

      //set the colors from text files plus a small variation
      redComponent = textLoader -> getInteger(pathTypeBase + string("Red")) + redShift;
      greenComponent = textLoader -> getInteger(pathTypeBase + string("Green")) + greenShift;
      blueComponent = textLoader -> getInteger(pathTypeBase + string("Blue")) + blueShift;
      alphaComponent = textLoader -> getInteger(pathTypeBase + string("Alpha"));
    }
    //otherwise we assume the default settings for a tile
    else{
      redComponent = textLoader -> getInteger(string("IDS_Path__Tile_1_Fill_Color_Red"));
      greenComponent = textLoader -> getInteger(string("IDS_Path_Tile_1_Fill_Color_Green"));
      blueComponent = textLoader -> getInteger(string("IDS_Path_Tile_1_Fill_Color_Blue"));
      alphaComponent = textLoader -> getInteger(string("IDS_Path_Tile_1_Fill_Color_Alpha"));
    }


    //the x and y position of this rectangle
    float xPos = col * xTileSize;
    float yPos = row * yTileSize;

    //set the position of the rectangle
    floorRect.setPosition(xPos, yPos);

    //set the color of the rectangle
    sf::Color color(redComponent, greenComponent, blueComponent, alphaComponent);
    floorRect.setFillColor(color);

    //draw the rectangle
    window.draw(floorRect);

}
void PlayingScreen::drawFloorTile(sf::RenderWindow& window, int row, int col,
   float yTileSize, float xTileSize, int tileValue, sf::RectangleShape& floorRect){

  //the cafeteria choice
  const MapChoices choices = gameLogic -> getMapCustomizationChoices();
  cafeteria cafeteriaChoice =  choices.cafeteriaChoice;

  //the number of tile types for each cafeteria level
  int numTileTypes = textLoader -> getInteger(string("IDS_Cafeteria_Tile_Types"));

  assert(numTileTypes != -1);

  //the remainder will determine which version of a tile we look for
  int tileVersion = ((-1)*tileValue)%numTileTypes;

  assert(tileVersion >=0);

  //the string built from the cafeteria choice and tile version
  string tileTypeBase = "IDS_" + to_string((int)cafeteriaChoice) + "_Floor_Tile_" + to_string(tileVersion) + "_Fill_Color_";


  //check if the tile exists
  int checkTileColorValue = textLoader -> getInteger(tileTypeBase +string("Red"));

  //hold our rgba values for this tile
  int redComponent;
  int greenComponent;
  int blueComponent;
  int alphaComponent;

  //if this was an actual tile version
  if(checkTileColorValue != -1){

    //weird tuple syntax but it just grabs the color shift in the tuple for this row, col
    int redShift = get<0>(pathColorShifts.at(row).at(col));
    int greenShift = get<1>(pathColorShifts.at(row).at(col));
    int blueShift = get<2>(pathColorShifts.at(row).at(col));


    redComponent = textLoader -> getInteger(tileTypeBase + string("Red")) + redShift;
    greenComponent = textLoader -> getInteger(tileTypeBase + string("Green")) + greenShift;
    blueComponent = textLoader -> getInteger(tileTypeBase + string("Blue")) + blueShift;
    alphaComponent = textLoader -> getInteger(tileTypeBase + string("Alpha"));
  }
  //otherwise we assume the default settings for a tile
  else{
    redComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Red"));
    greenComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Green"));
    blueComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Blue"));
    alphaComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Alpha"));
  }

  //the x and y position of this rectangle
  float xPos = col * xTileSize;
  float yPos = row * yTileSize;

  //set the position of the rectangle
  floorRect.setPosition(xPos, yPos);

  //set the color of the rectangle
  sf::Color color(redComponent, greenComponent, blueComponent, alphaComponent);
  floorRect.setFillColor(color);

  //draw the rectangle
  window.draw(floorRect);
}
void PlayingScreen::drawFloorExit(sf::RenderWindow& window, int row, int col,
   float yTileSize, float xTileSize, sf::RectangleShape& floorRect){

     int redComponent = textLoader -> getInteger(string("IDS_Exit_Fill_Color_Red"));
     int greenComponent = textLoader -> getInteger(string("IDS_Exit_Fill_Color_Green"));
     int blueComponent = textLoader -> getInteger(string("IDS_Exit_Fill_Color_Blue"));
     int alphaComponent = textLoader -> getInteger(string("IDS_Exit_Fill_Color_Alpha"));

     //the x and y position of this rectangle
     float xPos = col * xTileSize;
     float yPos = row * yTileSize;

     //set the position of the rectangle
     floorRect.setPosition(xPos, yPos);

     //set the color of the rectangle
     sf::Color color(redComponent, greenComponent, blueComponent, alphaComponent);
     floorRect.setFillColor(color);

     //draw the rectangle
     window.draw(floorRect);

}

/*
 * Draw the Towers and Obstacles currently placed on the board
 * @param window: the game window to draw on
 */
void PlayingScreen::drawTowersAndObstacles(sf::RenderWindow& window){
  const unordered_map<int, shared_ptr<TowerInterface>> towersPlaced = gameLogic -> getTowersPlaced();

  //the number of rows
  const int rows = gameLogic->getRows();
  //the number of cols
  const int cols = gameLogic->getCols();

  //the size of each tile in x direction
  const float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //the four components for a color
  int redComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Red"));
  int greenComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Green"));
  int blueComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Blue"));
  int alphaComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Alpha"));

  //set the colors of the radius circle
  sf::Color color (redComponent, greenComponent, blueComponent, alphaComponent);

  //iterate through the towers/obstacles placed on the board
  for(auto iterator : towersPlaced){
    //the position of the tower/obstacle
    int combinedRowCol = (iterator).first;
    //the row of the tower/obstacle
    int row = combinedRowCol / cols;
    //the col of the tower/obstacle
    int col = combinedRowCol % cols;

    //the current tower/obstacle
    shared_ptr<TowerInterface> current = (iterator).second;

    //get the sprite to be drawn
    sf::Sprite currentSprite = current -> getSprite();

    //the bounding rectangle will give us the dimensions of the sprite
    sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
    //the x dimension of the box
    float xDim = boundingBox.width;
    //the ydimension of the box
    float yDim = boundingBox.height;

    float xScale = current -> getXScale();
    float yScale = current -> getYScale();

    float x = xTileSize / xDim;
    float y = yTileSize / yDim;

    //the x and y position of this rectangle
    float xPos = col * xTileSize;
    float yPos = row * yTileSize;

    //set the scale for the tower/obstalce to fill up the square
    currentSprite.setScale(xScale, yScale);

    //set the position of the sprite to the top left of the rectangle
    currentSprite.setPosition(xPos, yPos);
    //finally draw the sprite
    window.draw(currentSprite);

    if(current -> isMelee){
      //if this is a meleeType then we need to draw its units
      drawTowerUnits(current, window);
    }
    //if the radius of firing/spawning units is visible we draw it
    if(current -> isRadiusVisible()){
      drawTowerRadius(current,window, xScale, yScale, color);
    }
  }
}

/*
 * Draw all the units for the melee tower to the screen
 * @param tower: the current tower
 * @param window: the game window to draw
 */
void PlayingScreen::drawTowerUnits(shared_ptr<TowerInterface> tower, sf::RenderWindow& window){
  MeleeTower* meleeTower = dynamic_cast<MeleeTower*>(tower.get());

  assert(meleeTower != NULL);

  //all the units spawned by this tower
  vector<shared_ptr<MeleeUnit>> units = meleeTower -> getUnits();

  assert(units.size() != 0);


  //the size of each tile in x direction
  const float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //iterate through all the units
  for(shared_ptr<MeleeUnit>& unit : units){

    //only draw them if they have health
    if(unit -> getHitpoints() != 0){
      //get the sprite to be drawn
      sf::Sprite currentSprite = unit -> getSprite();

      //the x and y position of this rectangle
      float xPos = unit -> getXCoordinate();
      float yPos = unit -> getYCoordinate();


      float towerX = meleeTower -> getXCoordinate();
      float towerY = meleeTower -> getYCoordinate();

      //only draw the units if they do not have the coordinates
      //that are the same as the tower center (i.e. their initialization coordinates)
      if(!(xPos == towerX && yPos == towerY)){
        //the bounding rectangle will give us the dimensions of the sprite
        sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
        //the x dimension of the box
        float xDim = boundingBox.width;
        //the ydimension of the box
        float yDim = boundingBox.height;

        //the scaling used for the units so that they do not fill up an entire square
        float unitScaleX = textLoader -> getDouble(string("IDS_Unit_Size_Scale_X"));
        float unitScaleY =  textLoader -> getDouble(string("IDS_Unit_Size_Scale_Y"));

        //the scale in the x direction
        float xScale = (float) xTileSize / ((float) xDim*unitScaleX);
        //the scale in the y direction
        float yScale = (float) yTileSize / ((float) yDim*unitScaleY);

        //set the scale for the tower/obstalce to fill up the square
        currentSprite.setScale(xScale, yScale);

        //set the position of the sprite to the top left of the rectangle
        currentSprite.setPosition(xPos, yPos);

        //finally draw the sprite
        window.draw(currentSprite);
      }
    }
  }
}


/*
 * Draw the semi-transparent circle around the tower indicating its effect radius
 * and if this is a melee tower it will draw a button that allows us to change the rally point
 * @param tower: the tower with the radius
 * @param window: the window being drawn on
 * @param xScale: the scale in the x direction
 * @param yScale: the scale in the y direciton
 * @param color: the color used for all radius circles
 */
 void PlayingScreen::drawTowerRadius(shared_ptr<TowerInterface> tower, sf::RenderWindow& window, float xScale, float yScale, sf::Color color){
   //circle used to draw a radius around the tower
   sf::CircleShape radiusCircle = tower -> getRadiusCircle();
   radiusCircle.setFillColor(color);
   float radius = (float) tower -> getRadius();
   radiusCircle.setRadius(radius);
   radiusCircle.setScale(xScale, yScale);
   //reset the origin so any position set refers to the center of the circle
   radiusCircle.setOrigin(radius, radius);
   radiusCircle.setPosition(tower -> getXCoordinate(), tower->getYCoordinate());
   window.draw(radiusCircle);

   //if the tower is a melee tower we will drawn a circle that lets us change its rally point
   if(tower -> isMelee){
     //set the button to visible if it is not
     if(!(rallyPointChange -> isCurrentlyVisible())){
       rallyPointChange -> flipVisibility();
     }

     MeleeTower* meleeTower = dynamic_cast<MeleeTower*>(tower.get());
     if (rallyPointChange -> isButtonClicked()){
       sf::Vector2i mousePos = mouse.getPosition(window);

       rallyPointChange -> setButtonPosition(mousePos.x, mousePos.y);
     }
     else{
       rallyPointChange -> setButtonPosition(meleeTower->getRallyX(), meleeTower->getRallyY());
     }

     //scale the button
     rallyPointChange -> setButtonScale(xScale, yScale);

     rallyPointChange -> draw(window);
   }
 }


/*
 * Draw all the enemy units on the screen
 * @param window: the game window to draw on
 */
void PlayingScreen::drawEnemyUnits(sf::RenderWindow& window){
  unordered_map<long long,shared_ptr<MeleeUnit>> allEnemyUnits = gameLogic -> getSpawnedEnemyUnits();
  //the number of rows
  const int rows = gameLogic->getRows();
  //the number of cols
  const int cols = gameLogic->getCols();

  //the size of each tile in x direction
  const float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //the four components for a color
  int redComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Red"));
  int greenComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Green"));
  int blueComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Blue"));
  int alphaComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Alpha"));

  //set the colors of the radius circle
  sf::Color color (redComponent, greenComponent, blueComponent, alphaComponent);

  //loop through all enemies on the board
  for(auto iterator : allEnemyUnits){
    //the id of the actor
    long long actorID = (iterator).first;

    //the current actor
    shared_ptr<ActorInterface> current = (iterator).second;

    //get the sprite to be drawn
    sf::Sprite currentSprite = current -> getSprite();

    //the x and y position of this rectangle
    float xPos = current -> getXCoordinate();
    float yPos = current -> getYCoordinate();

    //the bounding rectangle will give us the dimensions of the sprite
    sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
    //the x dimension of the box
    float xDim = boundingBox.width;
    //the ydimension of the box
    float yDim = boundingBox.height;

    //the scaling used for the units so that they do not fill up an entire square
    float unitScaleX = textLoader -> getDouble(string("IDS_Unit_Size_Scale_X"));
    float unitScaleY =  textLoader -> getDouble(string("IDS_Unit_Size_Scale_Y"));

    //the scale in the x direction
    float xScale = (float) xTileSize / ((float) xDim*unitScaleX);
    //the scale in the y direction
    float yScale = (float) yTileSize / ((float) yDim*unitScaleY);

    if(current->getDirection()==M_PI || current->getDirection()==0){
      //set the scale for the tower/obstalce to fill up the square
      currentSprite.setScale(xScale, yScale);
    }else{
      currentSprite.setScale(yScale, xScale);
    }

    //set the position of the sprite to the top left of the rectangle
    currentSprite.setPosition(xPos, yPos);

    //finally draw the sprite
    window.draw(currentSprite);

    // sf::CircleShape radiusCircle = current -> getRadiusCircle();
    // radiusCircle.setFillColor(sf::Color(150, 50, 250));
    // float radius = (float) current -> getRadius();
    // //cout << radius << endl;
    // radiusCircle.setRadius(radius);
    // radiusCircle.setScale(xScale, yScale);
    // //reset the origin so any position set refers to the center of the circle
    // radiusCircle.setOrigin(radius, radius);
    // radiusCircle.setPosition((float)(xPos)+ (xDim)/2.0, (float) (yPos) + (yDim)/2.0);
    // window.draw(radiusCircle);
    //cout << "drew radius" << endl;


    /*
    sf::CircleShape radiusCircle = current -> getRadiusCircle();
    radiusCircle.setFillColor(sf::Color(150, 50, 250));
    float radius = (float) current -> getRadius();
    //cout << radius << endl;
    radiusCircle.setRadius(radius);
    radiusCircle.setScale(xScale, yScale);
    //reset the origin so any position set refers to the center of the circle
    radiusCircle.setOrigin(radius, radius);
    radiusCircle.setPosition((float)(xPos)+ (xDim)/2.0, (float) (yPos) + (yDim)/2.0);
    window.draw(radiusCircle);
    //cout << "drew radius" << endl;

     */


  }
}

/*
 * Draw all the projectiles on the screen
 * @param window: the game window to draw on
 */
void PlayingScreen::drawProjectiles(sf::RenderWindow& window){
  unordered_map<long long, shared_ptr<ActorInterface>> allProjectiles = gameLogic -> getFiredProjectiles();

  //the number of rows
  const int rows = gameLogic->getRows();
  //the number of cols
  const int cols = gameLogic->getCols();

  //the size of each tile in x direction
  const float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //loop through all enemies on the board
  for(auto it : allProjectiles){
    shared_ptr<ActorInterface> current = it.second;

    //get the sprite to be drawn
    sf::Sprite currentSprite = current -> getSprite();

    //the bounding rectangle will give us the dimensions of the sprite
    sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
    //the x dimension of the box
    float xDim = boundingBox.width;
    //the ydimension of the box
    float yDim = boundingBox.height;

    //the scaling used for the projectiles so that they do not fill up an entire square
    float projectileScaleX = textLoader -> getDouble(string("IDS_Projectile_Size_Scale_X"));
    float projectileScaleY =  textLoader -> getDouble(string("IDS_Projectile_Size_Scale_Y"));

    //the scale in the x direction
    float xScale = (float) xTileSize / ((float) xDim*projectileScaleX);
    //the scale in the y direction
    float yScale = (float) yTileSize / ((float) yDim*projectileScaleY);

    //the x and y position of this rectangle
    float xPos = current -> getXCoordinate();
    float yPos = current -> getYCoordinate();

    //set the scale for the tower/obstalce to fill up the square
    currentSprite.setScale(xScale, yScale);

    //set the position of the sprite to the top left of the rectangle
    currentSprite.setPosition(xPos, yPos);

    //pass the scale of the screen to the header to modify its vector trajectory
    if(wasHeaderRecalculated()){
      //cast to projectile before calling set vector scale
      Projectile* projectile = dynamic_cast<Projectile*>(current.get());

      projectile -> setVectorScale(xScale,yScale);
    }

    //finally draw the sprite
    window.draw(currentSprite);
  }
}

/*
 * @return true if the header has been recaluclated
 */
bool PlayingScreen::wasHeaderRecalculated(){
  if(headerRecalculated < playingScreenHeader -> getHeaderRecalculatedTimes()){
    headerRecalculated = playingScreenHeader -> getHeaderRecalculatedTimes();
    return true;
  }
  return false;
}

template <class T>
void PlayingScreen::printVector(const vector<vector<T>> &v){
  //cout << " here !" << endl;
  for(const vector<int> vec : v){
    for(auto it = vec.begin(); it != vec.end(); ++it){
      if(*it < 0){
        cout << *it << " ";
      }
      else{
        cout << *it << "  ";
      }
    }
    cout << endl;
  }
  cout <<endl;
}
