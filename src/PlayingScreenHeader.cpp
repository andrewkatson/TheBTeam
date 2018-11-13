#include "PlayingScreenHeader.hpp"


PlayingScreenHeader::PlayingScreenHeader(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic){
  this->eventManager=eventManager;
  this->textLoader=textLoader;
  this->gameLogic=gameLogic;
  this -> windowX = gameLogic -> getWindowX();
  this-> windowY = gameLogic -> getWindowY();
  string fontpath = textLoader -> getString(string("IDS_FFP"));
  this -> buyTower = unique_ptr<Button>(new Button(windowX, windowY, TOPRIGHT,
    textLoader -> getString(string("IDS_Buy_Tower_Empty_Space")), textLoader, fontpath));

  visible = true;
  initDrawingMaterials();

  ySize = getMaximumY();
}

/*
 * Set up any objects that can be drawn
 */
void PlayingScreenHeader::initDrawingMaterials(){
  initBuyTowerButton();
  initHitpointsButton();
  initBalanceButton();
  initLevelButton();
  initWaveButton();
}

/*
 * Set up the buy tower button
 */
void PlayingScreenHeader::initBuyTowerButton(){
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

  string fontpath = textLoader -> getString(string("IDS_FFP"));
  //set the font inside the button so it can be used to calculate a bounds
  (this->buyTower) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> buyTower) -> setButtonPosition( TOPRIGHT);

  //make the button invisible to begin with
  (this->buyTower) -> flipVisibility();
}

/*
 * Initalize the hitpoints button to be displayed in the header
 */
void PlayingScreenHeader::initHitpointsButton(){

  //get the starting hitpoints
  Player player = gameLogic -> getPlayer();

  int startingHitpoints = player.getHitpoints();


  cout << startingHitpoints << endl;

  string fontpath = textLoader -> getString(string("IDS_TFP"));
  Button hitpoints = Button(windowX, windowY, TOPLEFT,
    textLoader -> getString(string("IDS_Hitpoints_Button_Text")) + " " + to_string(startingHitpoints),
      textLoader, fontpath);

  // set the fill color for the button rectangle
  hitpoints.setFillColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Fill_Color_Alpha")));

  // set the outline color for the button
  hitpoints.setOutlineColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Color_Alpha")));

  //set the button outline thickness
  this->buyTower -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Hitpoints_Outline_Thickness")));

  //set the fill color for the button text
  hitpoints.setTextFillColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Fill_Color_Alpha")));


  //set the outline color for the text
  hitpoints.setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  hitpoints.setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Hitpoints_Text_Outline_Thickness")));

  //set the text character size
  hitpoints.setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Hitpoints_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  hitpoints.setFont(fontpath);

  //rescale the button and reset it
  hitpoints.setButtonPosition(TOPLEFT);

  //push this button into the vector of buttons to be drawn
  headerVariables.push_back(hitpoints);
}

/*
 * Initalize the balance button to be displayed in the header
 */
void PlayingScreenHeader::initBalanceButton(){
  string fontpath = textLoader -> getString(string("IDS_FFP"));
  Button balance = Button(windowX, windowY, TOPRIGHT,
    textLoader -> getString(string("IDS_Balance_Button_Text")), textLoader, fontpath);
}

/*
 * Initalize the level button to be displayed in the header
 */
void PlayingScreenHeader::initLevelButton(){
  string fontpath = textLoader -> getString(string("IDS_FFP"));
  Button level = Button(windowX, windowY, TOPRIGHT,
    textLoader -> getString(string("IDS_Level_Button_Text")), textLoader, fontpath);
}

/*
 * Initalize the wave button to be displayed in the header
 */
void PlayingScreenHeader::initWaveButton(){
  string fontpath = textLoader -> getString(string("IDS_FFP"));
  Button wave = Button(windowX, windowY, TOPRIGHT,
    textLoader -> getString(string("IDS_Wave_Button_Text")), textLoader, fontpath);
}

/*
 * @return the maximum y dimension of any object in the header
 */
float PlayingScreenHeader::getMaximumY(){
  sf::RectangleShape rect = buyTower -> getButtonRect();
  sf::Vector2f size = rect.getSize();

  int playingScreenHeaderPadding = textLoader->getInteger(string("IDS_Playing_Screen_Header_Padding"));
  return size.y + playingScreenHeaderPadding;
}


/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void PlayingScreenHeader::registerDelegates(){

  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&PlayingScreenHeader::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_PSH_KP")),keyPressEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&PlayingScreenHeader::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_PSH_MP")),mousePressEventType);
}

/*
 * Deregister the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void PlayingScreenHeader::deregisterDelegates(){

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PSH_KP")),keyPressEventType);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_PSH_MP")),mousePressEventType);

}

void PlayingScreenHeader::setSelectedTile(int row, int col){
  this->rowSelected = row;
  this->colSelected = col;
}

/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void PlayingScreenHeader::handleKeyPress(const EventInterface& event){
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

  //if H then we flip the visibility
  if(key == "H"){
    flipVisibility();
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void PlayingScreenHeader::handleMousePress(const EventInterface& event){
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
  float xPos = mpEventData -> x - getXOffSet();
  //get the y position
  float yPos = mpEventData -> y - getYOffSet();

  //get the size of a tile in the x
  float xTileSize = getTrueXTileSize();
  //get the size of a tile in the y
  float yTileSize = getTrueYTileSize();

  //what row is being clicked
  int row = (int) yPos / yTileSize;
  //what col is being clicked
  int col = (int) xPos / xTileSize;

  //check if BuyTower button is being clicked
  //modify the xposition to reflect if there is an offset
  //otherwise it will not register the click
  bool buyTowerClicked = (this->buyTower) -> isSelected(xPos + getXOffSet(),yPos + getYOffSet());
  if(buyTowerClicked){
    shared_ptr<EventInterface> buyTowerState = make_shared<StateChangeEvent>(State::BuyTower, row, col, nowInNano);

    this -> eventManager -> queueEvent(buyTowerState);
    return;
  }

  //only check if we are clickinga tile when the cursor is within the game
  //area, subtracting the offset will render some clicks outside
  if(xPos >= 0 && yPos >= 0){
    //change what the buyTower button says depending on the what is at the tile
    if(gameLogic->isTower(row,col)){
      (this->buyTower) -> setString(textLoader->getString("IDS_Buy_Tower_Existing_Tower"));
      (this->buyTower) -> setButtonPosition(TOPRIGHT);
    }
    else if(gameLogic->isObstacle(row,col)){
      (this->buyTower) -> setString(textLoader->getString("IDS_Buy_Tower_Existing_Obstacle"));
      (this->buyTower) -> setButtonPosition(TOPRIGHT);
    }
    else if(gameLogic->isEmptySpace(row,col)){
      (this->buyTower) -> setString(textLoader->getString("IDS_Buy_Tower_Empty_Space"));
      (this->buyTower) -> setButtonPosition(TOPRIGHT);
    }
    //if the tile is a path or exit tile and the button is visible turn it off
    else if(gameLogic->isExit(row,col) || gameLogic -> isPath(row,col)) {
      if((this->buyTower)->isCurrentlyVisible()){
          (this->buyTower)->flipVisibility();
      }
      rowSelected = row;
      colSelected = col;
      return;
    }

    //if we have selected the same row and col as the last click then we
    //flip the visibility of the button
    if(row == rowSelected && colSelected == col){
      (this->buyTower)->flipVisibility();
    }
    else{
      rowSelected = row;
      colSelected = col;
    }
  }
}

/*
 * Flip the visibility for the screen
 */
void PlayingScreenHeader::flipVisibility(){
  visible = visible == true ? false : true;
}

/*
 * @return the size of an x tile which is determined by the dimensions and whether or
 * not the header is visible
 */
float PlayingScreenHeader::getTrueXTileSize(){
  return gameLogic -> getTileXSize();
}

/*
 * @return the size of an y tile which is determined by the dimensions and whether or
 * not the header is visible
 */
float PlayingScreenHeader::getTrueYTileSize(){
  if(!visible){
    return gameLogic -> getTileYSize();
  }
  else{
    int windowY = gameLogic -> getWindowY();
    int newWindowY = windowY - ySize;
    float yTileSize = newWindowY / gameLogic->getRows();
    return yTileSize;
  }
}

/*
 * @return the offset in the x direction for the header
 */
float PlayingScreenHeader::getXOffSet(){
  return 0.0;
}

/*
 * @return the offset in the y direction for the header
 */
float PlayingScreenHeader::getYOffSet(){
  if(!visible){
    return 0.0;
  }
  return ySize;
}

void PlayingScreenHeader::draw(sf::RenderWindow &window){
  //handle the buy tower button separately
  drawBuyTowerButton(window);
  //draw the rest of the header if it is visible
  if(visible){
    drawHeaderButtons(window);
  }
}


/*
 * Draw the buy tower button
 * @param window: the game window to draw on
 */
void PlayingScreenHeader::drawBuyTowerButton(sf::RenderWindow& window){

  //if the button is invisible do not draw it
  if(!buyTower -> isCurrentlyVisible()){
    return;
  }

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_FFP"));

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
 * Draw all the buttons in the header (hitpoints, balance, level, wave)
 * @param window: the game window to draw on
 */
void PlayingScreenHeader::drawHeaderButtons(sf::RenderWindow& window){
  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }
  for(Button toDraw : headerVariables){
    text = toDraw.getButtonText();
    text.setFont(mainFont);

    window.draw(toDraw.getButtonRect());
    window.draw(text);
  }
}
