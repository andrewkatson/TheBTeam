#include "PlayingScreen.hpp"



PlayingScreen::PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,  int windowX, int windowY) : mt(std::random_device()()){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> gameLogic = gameLogic;
  this -> playingScreenHeader = make_shared<PlayingScreenHeader>(eventManager, textLoader, gameLogic);
  somethingChanged = true;
  haveSetColorShift=false;
  this -> registerPersistentDelegates();
  this -> initDrawingMaterials();
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

  //register delegates for the header
  playingScreenHeader -> registerDelegates();
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
}


/*
 * Initialize all the things used for drawing (shapes, fonts)
 */
void PlayingScreen::initDrawingMaterials(){

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
  }
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

  //get the xposition
  float xPos = mpEventData -> x - playingScreenHeader -> getXOffSet();
  //get the y position
  float yPos = mpEventData -> y - playingScreenHeader -> getYOffSet();

  //get the size of a tile in the x
  float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //get the size of a tile in the y
  float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //what row is being clicked
  int row = (int) yPos / yTileSize;
  //what col is being clicked
  int col = (int) xPos / xTileSize;

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

  //draw the header
  playingScreenHeader -> draw(window);
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

    //the offset for the starting position if there is a header
    float xOffSet = playingScreenHeader -> getXOffSet();
    float yOffSet = playingScreenHeader -> getYOffSet();

    //the x and y position of this rectangle
    float xPos = col * xTileSize + xOffSet;
    float yPos = row * yTileSize + yOffSet;

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

  //the offset for the starting position if there is a header
  float xOffSet = playingScreenHeader -> getXOffSet();
  float yOffSet = playingScreenHeader -> getYOffSet();

  //the x and y position of this rectangle
  float xPos = col * xTileSize + xOffSet;
  float yPos = row * yTileSize + yOffSet;

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

     //the offset for the starting position if there is a header
     float xOffSet = playingScreenHeader -> getXOffSet();
     float yOffSet = playingScreenHeader -> getYOffSet();

     //the x and y position of this rectangle
     float xPos = col * xTileSize + xOffSet;
     float yPos = row * yTileSize + yOffSet;

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
  const int xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const int yTileSize = playingScreenHeader -> getTrueYTileSize();

  //circle used to draw a radius around the tower
  sf::CircleShape radiusCircle;

  //the four components for a color
  int redComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Red"));
  int greenComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Green"));
  int blueComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Blue"));
  int alphaComponent = textLoader -> getInteger(string("IDS_Radius_Circle_Fill_Color_Alpha"));

  //set the colors of the radius circle
  sf::Color color (redComponent, greenComponent, blueComponent, alphaComponent);
  radiusCircle.setFillColor(color);

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

    //the offset for the starting position if there is a header
    float xOffSet = playingScreenHeader -> getXOffSet();
    float yOffSet = playingScreenHeader -> getYOffSet();

    //the x and y position of this rectangle
    float xPos = col * xTileSize + xOffSet;
    float yPos = row * yTileSize + yOffSet;

    //the bounding rectangle will give us the dimensions of the sprite
    sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
    //the x dimension of the box
    int xDim = boundingBox.width;
    //the ydimension of the box
    int yDim = boundingBox.height;

    //the scale in the x direction
    float xScale = (float) xTileSize / (float) xDim;
    //the scale in the y direction
    float yScale = (float) yTileSize / (float) yDim;

    //set the scale for the tower/obstalce to fill up the square
    currentSprite.setScale(xScale, yScale);

    //set the position of the sprite to the top left of the rectangle
    currentSprite.setPosition(xPos, yPos);

    //updates the coordinates of the tower in case it moved
    //to always be the center of the tile it is placed at
    current -> setXCoordinate((float)(xPos)+ (xDim)/2.0);
    current -> setYCoordinate((float)(yPos) + (yDim)/2.0);

    //finally draw the sprite
    window.draw(currentSprite);

    if(current -> isMelee){
      //if this is a meleeType then we need to draw its units
      drawTowerUnits(current, window);
    }
    //if the radius of firing/spawning units is visible we draw it
    if(current -> isRadiusVisible()){
      float radius = (float) current -> getRadius();
      radiusCircle.setRadius(radius);
      radiusCircle.setScale(xScale, yScale);
      //reset the origin so any position set refers to the center of the circle
      radiusCircle.setOrigin(radius, radius);
      radiusCircle.setPosition((float)(xPos)+ (xDim)/2.0, (float) (yPos) + (yDim)/2.0);
      window.draw(radiusCircle);
    }
  }
}

/*
 * Draw all the units for the melee tower to the screen
 * @param meleeTower: the current tower
 * @param window: the game window to draw
 */
void PlayingScreen::drawTowerUnits(shared_ptr<TowerInterface> meleeTower, sf::RenderWindow& window){
  //TODO implementation
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
  const int xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const int yTileSize = playingScreenHeader -> getTrueYTileSize();

  //loop through all enemies on the board
  for(auto iterator : allEnemyUnits){
    //the id of the actor
    long long actorID = (iterator).first;

    //the current actor
    shared_ptr<ActorInterface> current = (iterator).second;

    //get the sprite to be drawn
    sf::Sprite currentSprite = current -> getSprite();

    //the offset for the starting position if there is a header
    float xOffSet = playingScreenHeader -> getXOffSet();
    float yOffSet = playingScreenHeader -> getYOffSet();

    //the x and y position of this rectangle
    float xPos = current -> getXCoordinate() + xOffSet;
    float yPos = current -> getYCoordinate() + yOffSet;

    //the bounding rectangle will give us the dimensions of the sprite
    sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
    //the x dimension of the box
    int xDim = boundingBox.width;
    //the ydimension of the box
    int yDim = boundingBox.height;

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

    //set the position of the actor to be the center of the bounding rectangle
    current -> setXCoordinate((xPos+xDim)/2);
    current -> setYCoordinate((yPos+yDim)/2);

    //finally draw the sprite
    window.draw(currentSprite);
  }
}

/*
 * Draw all the projectiles on the screen
 * @param window: the game window to draw on
 */
void PlayingScreen::drawProjectiles(sf::RenderWindow& window){
  vector<shared_ptr<ActorInterface>> allProjectiles = gameLogic -> getFiredProjectiles();

  //the number of rows
  const int rows = gameLogic->getRows();
  //the number of cols
  const int cols = gameLogic->getCols();

  //the size of each tile in x direction
  const int xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const int yTileSize = playingScreenHeader -> getTrueYTileSize();

  //loop through all enemies on the board
  for(shared_ptr<ActorInterface> current : allProjectiles){

    //get the sprite to be drawn
    sf::Sprite currentSprite = current -> getSprite();

    //the offset for the starting position if there is a header
    float xOffSet = playingScreenHeader -> getXOffSet();
    float yOffSet = playingScreenHeader -> getYOffSet();

    //the x and y position of this rectangle
    float xPos = current -> getXCoordinate() + xOffSet;
    float yPos = current -> getYCoordinate() + yOffSet;

    //the bounding rectangle will give us the dimensions of the sprite
    sf::FloatRect boundingBox = currentSprite.getGlobalBounds();
    //the x dimension of the box
    int xDim = boundingBox.width;
    //the ydimension of the box
    int yDim = boundingBox.height;

    //the scale in the x direction
    float xScale = (float) xTileSize / (float) xDim;
    //the scale in the y direction
    float yScale = (float) yTileSize / (float) yDim;

    //set the scale for the tower/obstalce to fill up the square
    currentSprite.setScale(xScale, yScale);

    //set the position of the sprite to the top left of the rectangle
    currentSprite.setPosition(xPos, yPos);

    //set the position of the actor to be the center of the bounding rectangle
    current -> setXCoordinate((xPos+xDim)/2);
    current -> setYCoordinate((yPos+yDim)/2);

    //pass the scale of the screen to the header to modify its vector trajectory
    if(playingScreenHeader -> headerRecalculated()){
      //cast to projectile before calling set vector scale
      Projectile* projectile = dynamic_cast<Projectile*>(current.get());

      projectile -> setVectorScale(xScale,yScale);
    }

    //finally draw the sprite
    window.draw(currentSprite);
  }
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
