#include "PlayingScreen.hpp"



PlayingScreen::PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic, int windowX, int windowY) : mt(std::random_device()()){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> gameLogic = gameLogic;
  this -> buyTower = unique_ptr<Button>(new Button(windowX, windowY, TOPRIGHT, textLoader -> getString(string("IDS_Buy_Tower_Button_Message")), textLoader));
  somethingChanged = true;
  haveSetColorShift=false;
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

}


/*
 * Initialize all the things used for drawing (shapes, fonts)
 */
void PlayingScreen::initDrawingMaterials(){
  initBuyTowerButton();
}

/*
 * Initialize the data for the BuyTower button
 */
void PlayingScreen::initBuyTowerButton(){
  // set the fill color for the button rectangle
  this -> buyTower -> setFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> buyTower -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->buyTower -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Thickness")));

  //set the fill color for the button text
  this -> buyTower -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  this -> buyTower -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->buyTower -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Thickness")));

  //set the text character size
  this->buyTower -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Buy_Tower_Text_Size")));

  //rescale the button and reset it
  (this -> buyTower) -> setButtonPosition( TOPRIGHT);

  //make the button invisible to begin with
  (this->buyTower) -> flipVisibility();
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
  float xPos = mpEventData -> x;
  //get the y position
  float yPos = mpEventData -> y;

  //check if BuyTower button is being clicked
  bool buyTowerClicked = (this->buyTower) -> isSelected(xPos,yPos);
  if(buyTowerClicked){
    shared_ptr<EventInterface> buyTowerState = make_shared<StateChangeEvent>(State::BuyTower, nowInNano);

    this -> eventManager -> queueEvent(buyTowerState);
  }

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
  drawBuyTowerButton(window);


}

/*
 * Draw the buy tower button
 * @param window: the game window to draw on
 */
void PlayingScreen::drawBuyTowerButton(sf::RenderWindow& window){

  //if the button is invisible do not draw it
  if(!buyTower -> isCurrentlyVisible()){
    return;
  }

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_Black_Berry_Jam"));

  if(!mainFont.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }

  text = buyTower -> getButtonText();
  text.setFont(mainFont);

  window.draw(buyTower -> getButtonRect());
  window.draw(text);
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
  const int xTileSize = gameLogic -> getTileXSize();
  //the size of each tile in y direction
  const int yTileSize = gameLogic -> getTileYSize();

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
      //if this is a floor
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
  int yTileSize, int xTileSize, int pathValue, sf::RectangleShape& floorRect){

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

      //weird tuple syntax but it just grabs the r in the tuple for this row, col
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
   int yTileSize, int xTileSize, int tileValue, sf::RectangleShape& floorRect){

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

    //weird tuple syntax but it just grabs the r in the tuple for this row, col
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
   int yTileSize, int xTileSize, sf::RectangleShape& floorRect){

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
