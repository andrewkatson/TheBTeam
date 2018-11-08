#include "PlayingScreen.hpp"


PlayingScreen::PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic, int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> gameLogic = gameLogic;
  this -> buyTower = Button(windowX, windowY, TOPRIGHT, textLoader -> getString(string("IDS_Buy_Tower_Button_Message")), textLoader);
  somethingChanged = true;
  this -> initDrawingMaterials();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void PlayingScreen::registerDelegates(){
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
  this -> buyTower.setFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> buyTower.setOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->buyTower.setOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Outline_Thickness")));

  //set the fill color for the button text
  this -> buyTower.setTextFillColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  this -> buyTower.setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->buyTower.setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Buy_Tower_Text_Outline_Thickness")));

  //set the text character size
  this->buyTower.setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Buy_Tower_Text_Size")));

  //rescale the button and reset it
  (this -> buyTower).setButtonPosition( TOPRIGHT);

  //make the button invisible to begin with
  (this->buyTower).flipVisibility();
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
  bool buyTowerClicked = (this->buyTower).isSelected(xPos,yPos);
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

  drawBuyTowerButton(window);
  drawFloorMap(window);

}

/*
 * Draw the buy tower button
 * @param window: the game window to draw on
 */
void PlayingScreen::drawBuyTowerButton(sf::RenderWindow& window){

  //if the button is invisible do not draw it
  if(!buyTower.isCurrentlyVisible()){
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

  text = buyTower.getButtonText();
  text.setFont(mainFont);

  window.draw(buyTower.getButtonRect());
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

  //iterate through the 2d grid
  for(int row = 0; row < floorGrid.size(); row++){
    for(int col = 0; col < floorGrid.at(0).size(); col++){
      int floorValue = floorGrid.at(row).at(col);
      //if this is a path
      if(floorValue > 0){
        drawFloorPath(window, row, col, yTileSize, xTileSize, floorValue);
      }
      //if this is a floor
      else if(floorValue < 0){
        drawFloorTile(window, row, col, yTileSize, xTileSize, floorValue);
      }
      //if this is the exit
      else if(floorGrid.at(row).at(col) == 0){
        drawFloorExit(window, row, col, yTileSize, xTileSize);
      }
    }
  }
}

void PlayingScreen::drawFloorPath(sf::RenderWindow& window, int row, int col, int yTileSize, int xTileSize, int pathValue){



}
void PlayingScreen::drawFloorTile(sf::RenderWindow& window, int row, int col, int yTileSize, int xTileSize, int tileValue){
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
    redComponent = textLoader -> getInteger(tileTypeBase + string("Red"));
    greenComponent = textLoader -> getInteger(tileTypeBase + string("Green"));
    blueComponent = textLoader -> getInteger(tileTypeBase + string("Blue"));
    alphaComponent = textLoader -> getInteger(tileTypeBase + string("Alpha"));
  }
  //otherwise we assume the default settings for a tile
  else{
    redComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Red"));
    greenComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Green"));
    blueComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Blue"));
    alphaComponent = textLoader -> getInteger(string("IDS_1_Floor_Tile_0_Fill_Color_Alpha"));
  }


}
void PlayingScreen::drawFloorExit(sf::RenderWindow& window, int row, int col, int yTileSize, int xTileSize){

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
