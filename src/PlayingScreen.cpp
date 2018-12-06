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


void PlayingScreen::initSpeedButtons() {


  string fontpath = textLoader -> getString(string("IDS_TFP"));

  //set up the back button
  slowPlayButton = unique_ptr<Button>(new Button(windowX, windowY, BOTTOMLEFT,
                                             textLoader -> getString(string("IDS_Button_Slow_Text")), textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> slowPlayButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
                                     this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                     this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> slowPlayButton -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Red")),
                                        this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Green")),
                                        this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->backButton -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Thickness")));

  //set the fill color for the button text
  this -> slowPlayButton -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Red")),
                                         this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Green")),
                                         this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Alpha")));

  //set the outline color for the text
  this -> slowPlayButton -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Red")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Green")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->slowPlayButton -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Thickness")));

  //set the text character size
  this->slowPlayButton -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Back_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->slowPlayButton) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> slowPlayButton) -> setButtonPosition(textLoader->getInteger("IDS_Slow_Button_Left_Pad"),windowY-textLoader->getInteger("IDS_Speed_Buttons_Y_Pad"));


  //set up the back button
  playButton = unique_ptr<Button>(new Button(windowX, windowY, BOTTOMLEFT,
                                             textLoader -> getString(string("IDS_Button_Normal_Speed_Text")), textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> playButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Red")),
                                     this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Blue")),
                                     this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Green")),
                                     this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> playButton -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Red")),
                                        this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Green")),
                                        this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->backButton -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Thickness")));

  //set the fill color for the button text
  this -> playButton -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Red")),
                                         this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Green")),
                                         this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Alpha")));

  //set the outline color for the text
  this -> playButton -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Red")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Green")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->playButton -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Thickness")));

  //set the text character size
  this->playButton -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Back_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->playButton) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> playButton) -> setButtonPosition(textLoader->getInteger("IDS_Normal_Speed_Button_Left_Pad"),windowY-textLoader->getInteger("IDS_Speed_Buttons_Y_Pad"));


  fastForwardButton = unique_ptr<Button>(new Button(windowX, windowY, BOTTOMLEFT,
                                             textLoader -> getString(string("IDS_Button_Fast_Speed_Text")), textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> fastForwardButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
                                     this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                     this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> fastForwardButton -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Red")),
                                        this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Green")),
                                        this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->backButton -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Thickness")));

  //set the fill color for the button text
  this -> fastForwardButton -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Red")),
                                         this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Blue")),
                                         this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Green")),
                                         this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Alpha")));

  //set the outline color for the text
  this -> fastForwardButton -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Red")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Green")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->fastForwardButton -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Thickness")));

  //set the text character size
  this->fastForwardButton -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Back_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->fastForwardButton) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> fastForwardButton) -> setButtonPosition(textLoader->getInteger("IDS_Fast_Speed_Button_Left_Pad"),windowY-textLoader->getInteger("IDS_Speed_Buttons_Y_Pad"));

  ultraFastForwardButton = unique_ptr<Button>(new Button(windowX, windowY, BOTTOMLEFT,
                                                    textLoader -> getString(string("IDS_Button_Very_Fast_Speed_Text")), textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> ultraFastForwardButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                            this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> ultraFastForwardButton -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Red")),
                                               this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Green")),
                                               this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->backButton -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Thickness")));

  //set the fill color for the button text
  this -> ultraFastForwardButton -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Red")),
                                                this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Green")),
                                                this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Alpha")));

  //set the outline color for the text
  this -> ultraFastForwardButton -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Red")),
                                                   this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Green")),
                                                   this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Alpha")));

  //set the button text outline thickness
  this->ultraFastForwardButton -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Thickness")));

  //set the text character size
  this->ultraFastForwardButton -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Back_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->ultraFastForwardButton) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> ultraFastForwardButton) -> setButtonPosition(textLoader->getInteger("IDS_Very_Fast_Speed_Button_Left_Pad"),windowY-textLoader->getInteger("IDS_Speed_Buttons_Y_Pad"));


}


/*
 * Initialize all the things used for drawing (shapes, fonts)
 */
void PlayingScreen::initDrawingMaterials(){

  if(!exitTexture.loadFromFile(textLoader->getString(string("IDS_Exit_Tile")))){
    cerr << "could not load in exit tile" << endl;
    assert(false);
  }

  //the size of each tile in x direction
  const float xTileSize = playingScreenHeader -> getTrueXTileSize();
  //the size of each tile in y direction
  const float yTileSize = playingScreenHeader -> getTrueYTileSize();

  //set its size
  exitTile.setSize(sf::Vector2f(xTileSize, yTileSize));

  //set the exit tile texture
  exitTile.setTexture(&exitTexture);

  initRallyPointButton();
  initUpgradeCircle();
  initSpeedButtons();
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

  //cout << "how< many rows " << rows << " "<< cols << endl;

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

  //cout << "how we feeling " << rows << " " << cols << endl;

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

  //cout << "row size of colors " << pathColorShifts.size() << " " <<pathColorShifts.at(0).size() << endl;
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


  if(slowPlayButton->isSelected(xPos,yPos) ||
          playButton->isSelected(xPos,yPos) ||
          fastForwardButton->isSelected(xPos,yPos) ||
    ultraFastForwardButton->isSelected(xPos,yPos)){

    this -> slowPlayButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

    this -> playButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

    this -> fastForwardButton-> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

    this -> ultraFastForwardButton-> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));


  }
  if(slowPlayButton->isSelected(xPos,yPos)){

    shared_ptr<EventInterface> speedChange = make_shared<SpeedChangeEvent>(textLoader->getDouble("IDS_Slow_Play_Speed"), nowInNano);

    this -> eventManager -> queueEvent(speedChange);

    this -> slowPlayButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  }

  if(playButton->isSelected(xPos,yPos)){

    shared_ptr<EventInterface> speedChange = make_shared<SpeedChangeEvent>(textLoader->getDouble("IDS_Play_Speed"), nowInNano);

    this -> eventManager -> queueEvent(speedChange);

    this -> playButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  }

  if(fastForwardButton->isSelected(xPos,yPos)){

    shared_ptr<EventInterface> speedChange = make_shared<SpeedChangeEvent>(textLoader->getDouble("IDS_Fast_Forward_Speed"), nowInNano);

    this -> eventManager -> queueEvent(speedChange);
    this -> fastForwardButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  }


  if(ultraFastForwardButton->isSelected(xPos,yPos)){

    shared_ptr<EventInterface> speedChange = make_shared<SpeedChangeEvent>(textLoader->getDouble("IDS_Ultra_Fast_Forward_Speed"), nowInNano);

    this -> eventManager -> queueEvent(speedChange);

    this -> ultraFastForwardButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Red")),
                                           this->textLoader -> getInteger(string("IDS_Selected_Speed_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
                                           this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  }


    //cout << "x " << xPos << " y " << yPos << endl;

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
 * Handle level changes by delegating to classes below this one that need to know
 */
void PlayingScreen::handleLevelChangeEvent(const EventInterface& event){
  playingScreenHeader -> initDrawingMaterials();
}

/*
 * Handle restart game changes by delegating to classes below this one that need to know
 */
void PlayingScreen::handleRestartGameEvent(const EventInterface& event){
  playingScreenHeader -> initDrawingMaterials();
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
  ////cout<<"drawing all the things"<<endl;


  //initlaize the color shift vectors
  //if we have not or this is a new board
  if(!haveSetColorShift || (pathColorShifts.size() != gameLogic->getRows() || pathColorShifts.at(0).size() != gameLogic->getCols())){
    //cout << "Called you " << endl;
    initColorShifts();
    haveSetColorShift=true;
  }


  drawFloorMap(window);
  ////cout<<"drawing all the things 1"<<endl;
  drawTowersAndObstacles(window);
  ////cout<<"drawing all the things 2"<<endl;
  //to avoid looping twice we draw all the units of the towers in the
  //same method as drawing the towers

  drawEnemyUnits(window);
  ////cout<<"drawing all the things 3"<<endl;
  drawProjectiles(window);
  ////cout<<"drawing all the things 4"<<endl;
  playingScreenHeader -> draw(window);
  ////cout<<"drawing all the things 5"<<endl;
  //draw the upgrade circle
  upgradeCircle -> draw(window);
  ////cout<<"drawing all the things 6"<<endl;
  //TODO change into real code for drawing the map!
  if(somethingChanged){
    //cout << endl << "THE FLOOR " << endl;
    const vector<vector<int>> floor = gameLogic -> getFloor();
    printVector(floor);

    //cout << endl << "ABOVE THE FLOOR" << endl;
    const vector<vector<int>> aboveFloor = gameLogic -> getAboveFloor();
    printVector(aboveFloor);

    //cout << endl << "DISTANCES " << endl;
    const vector<vector<int>> distances = gameLogic -> getDistances();
    printVector(distances);

    somethingChanged = false;

  }
  ////cout<<"we drew all the things"<<endl;

  drawSpeedButtons(window);
}

void PlayingScreen::drawSpeedButtons(sf::RenderWindow& window){
  slowPlayButton->draw(window);

  //below is a workaround because the draw was not showing the text because sfml is stupid
  sf::Text slow = slowPlayButton -> getButtonText();
  sf::Font mainFont;
  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    //cout << "No font!" << endl;
  }
  else{
    //  //cout << "loaded font!" << endl;
  }

  slow.setFont(mainFont);
  window.draw(slow);
  playButton->draw(window);

  sf::Text norm = playButton -> getButtonText();

  norm.setFont(mainFont);
  window.draw(norm);


  fastForwardButton->draw(window);

  sf::Text fast = fastForwardButton -> getButtonText();

  fast.setFont(mainFont);
  window.draw(fast);

  ultraFastForwardButton->draw(window);

  sf::Text veryfast = ultraFastForwardButton -> getButtonText();

  veryfast.setFont(mainFont);
  window.draw(veryfast);

/*

  ultraFastForwardButton->draw(window);

  sf::Text superfast = playButton -> getButtonText();

  norm.setFont(mainFont);
  window.draw(superfast);
*/
}

/*
 * Draw the floor of the map (i.e. anything on the floorGrid: floor tiles, path tiles, and exit )
 * @param window: the game window to draw on
 */
void PlayingScreen::drawFloorMap(sf::RenderWindow& window){
  //the 2d grid with ASCII representations of each tile
  const vector<vector<int>> floorGrid = gameLogic -> getFloor();

  ////cout << "floor is " << floorGrid.size() << " and " << floorGrid.at(0).size() << endl;

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
      ////cout << "row " << row << " " << col << endl;
      int floorValue = floorGrid.at(row).at(col);
     // //cout << "is issue here " << endl;
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
     // //cout << "exit loop " << endl;
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

      assert(row < pathColorShifts.size());
      assert(col < pathColorShifts.at(0).size());
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
    assert(row < pathColorShifts.size());
    assert(col < pathColorShifts.at(0).size());
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
     exitTile.setPosition(xPos, yPos);
     floorRect.setPosition(xPos, yPos);

     exitTile.setTexture(&exitTexture);

     //set the color of the rectangle
     sf::Color color(redComponent, greenComponent, blueComponent, alphaComponent);
     floorRect.setFillColor(color);

     //draw the rectangle
     //window.draw(exitTile);
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
    if(unit -> getHitpoints() > 0){
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

        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(xPos,yPos);
        rect.setOrigin(currentSprite.getOrigin());
        rect.setSize(sf::Vector2f(xDim, yDim));
        rect.setScale(xScale,yScale);
        window.draw(rect);

        //set the sprite position inside the class
        unit->setSpritePosition(xPos,yPos);

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

    //if the unit is not to be drawn (i.e. flicker)
    if(current -> canDraw() >= 1){

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


          //set the scale for the tower/obstalce to fill up the square
      if(current->getDirection()==M_PI || current->getDirection()==0){
        currentSprite.setScale(xScale, yScale);
        //set the scale for the tower/obstalce to fill up the square
        currentSprite.setScale(xScale, yScale);
      }else{
        currentSprite.setScale(yScale, xScale);
      }
          //set the position of the sprite to the top left of the rectangle
          currentSprite.setPosition(xPos, yPos);

          //set the sprite position inside the class
          //current->setSpritePosition(xPos,yPos);
          sf::RectangleShape rect;
          rect.setFillColor(sf::Color::Blue);
          rect.setPosition(xPos,yPos);
          rect.setOrigin(currentSprite.getOrigin());
          rect.setSize(sf::Vector2f(xDim, yDim));
          rect.setScale(xScale,yScale);
          window.draw(rect);
          //finally draw the sprite
          window.draw(currentSprite);

          // sf::CircleShape radiusCircle = current -> getRadiusCircle();
          // radiusCircle.setFillColor(sf::Color(150, 50, 250));
          // float radius = (float) current -> getRadius();
          // ////cout << radius << endl;
          // radiusCircle.setRadius(radius);
          // radiusCircle.setScale(xScale, yScale);
          // //reset the origin so any position set refers to the center of the circle
          // radiusCircle.setOrigin(radius, radius);
          // radiusCircle.setPosition((float)(xPos)+ (xDim)/2.0, (float) (yPos) + (yDim)/2.0);
          // window.draw(radiusCircle);
          ////cout << "drew radius" << endl;


          /*
          sf::CircleShape radiusCircle = current -> getRadiusCircle();
          radiusCircle.setFillColor(sf::Color(150, 50, 250));
          float radius = (float) current -> getRadius();
          ////cout << radius << endl;
          radiusCircle.setRadius(radius);
          radiusCircle.setScale(xScale, yScale);
          //reset the origin so any position set refers to the center of the circle
          radiusCircle.setOrigin(radius, radius);
          radiusCircle.setPosition((float)(xPos)+ (xDim)/2.0, (float) (yPos) + (yDim)/2.0);
          window.draw(radiusCircle);
          ////cout << "drew radius" << endl;

           */
    }
    else{
      //if we did not draw it (i.e. it if flickering) then increment the draw unit variable
      current->incrementDrawUnit();
    }
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
  ////cout << " here !" << endl;
  for(const vector<int> vec : v){
    for(auto it = vec.begin(); it != vec.end(); ++it){
      if(*it < 0){
        //cout << *it << " ";
      }
      else{
        //cout << *it << "  ";
      }
    }
    //cout << endl;
  }
  //cout <<endl;
}
