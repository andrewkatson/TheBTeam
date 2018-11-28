#include "BuyTowerScreen.hpp"

BuyTowerScreen::BuyTowerScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> gameLogic = gameLogic;
  this -> initDrawingMaterials();
  this -> registerPersistentDelegates();
}

/*
 * Initlaize anything required to be drawn on the screen
 */
void BuyTowerScreen::initDrawingMaterials(){
  initText();
  initBackButton();
}

/*
 * Initialize any parts of the text that will not change
 */
void BuyTowerScreen::initText(){
    this -> currentTitle = textLoader->getString(string("IDS_Buy_Tower_Title_Text_Existing_Tower_Or_Empty_Space"));
}

/*
 * Initalize the back button
 */
void BuyTowerScreen::initBackButton(){
  string fontpath = textLoader -> getString(string("IDS_TFP"));

  //set up the back button
  backButton = unique_ptr<Button>(new Button(windowX, windowY, BOTTOMLEFT,
    textLoader -> getString(string("IDS_Buy_Tower_Back_Button")), textLoader, fontpath));

  // set the fill color for the button rectangle
  this -> backButton -> setFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Fill_Color_Alpha")));

  // set the outline color for the button
  this -> backButton -> setOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Color_Alpha")));

  //set the button outline thickness
  //this->backButton -> setOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Outline_Thickness")));

  //set the fill color for the button text
  this -> backButton -> setTextFillColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Alpha")));
  cout  << "red for text  " << this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Red")) << " and blue "<< this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Blue")) << " and green " << this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Green")) << " and alpha " << this->textLoader -> getInteger(string("IDS_Back_Button_Text_Fill_Color_Alpha")) << endl;

  //set the outline color for the text
  this -> backButton -> setTextOutlineColor(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Blue")),this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Alpha")));

  cout  << "red for text outline  " << this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Red")) << " and blue "<< this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Blue")) << " and green " << this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Green")) << " and alpha " << this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Color_Alpha")) << endl;

  //set the button text outline thickness
  this->backButton -> setTextOutlineThickness(this->textLoader -> getInteger(string("IDS_Back_Button_Text_Outline_Thickness")));

  //set the text character size
  this->backButton -> setTextSize(this->windowX / this->textLoader->getInteger(string("IDS_Back_Button_Text_Size")));

  //set the font inside the button so it can be used to calculate a bounds
  (this->backButton) -> setFont(fontpath);

  //rescale the button and reset it
  (this -> backButton) -> setButtonPosition( BOTTOMLEFT);
}


void BuyTowerScreen::draw(sf::RenderWindow &window){
  drawTitle(window);

  backButton -> draw(window);

  //below is a workaround because the draw was not showing the text because sfml is stupid
  sf::Text text = backButton -> getButtonText();
  sf::Font mainFont;
  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_TFP"));

  if(!mainFont.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }

  text.setFont(mainFont);
  window.draw(text);

  //iterate through the options on the screen and draw them one by one
  for(shared_ptr<BuyTowerOption>  towerOption : options){
    towerOption -> draw(window);
  }
}

/*
 * Draw the title for the screen
 */
void BuyTowerScreen::drawTitle(sf::RenderWindow& window){
  //used to make the font local
  string secondaryFontPath = textLoader -> getString(string("IDS_SFP"));

  //locally load the font
  if(!font.loadFromFile(secondaryFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }
  sf::Text title;

  // select the font
  title.setFont(font); // font is a sf::Font
  title.setString(currentTitle);

  int titleTextSize = this->textLoader->getInteger(string("IDS_Buy_Tower_Title_Text_Size"));
  title.setCharacterSize(titleTextSize);
  title.setPosition(this->windowX /3 + title.getCharacterSize(),
                      this->windowY/8 - title.getCharacterSize());
  sf::Color color (this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Red")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Blue")), this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Green")),
  this->textLoader -> getInteger(string("IDS_Buy_Tower_Title_Text_Fill_Color_Alpha")));
  title.setFillColor(color);
  window.draw(title);
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void BuyTowerScreen::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&BuyTowerScreen::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_BTS_KP")),keyPressEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&BuyTowerScreen::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_BTS_MP")),mousePressEventType);

}

/*
 * Register the delegate methods for this class
 * with any events it needs to know about
 * used for any delegate methods that should never be deregistered
 */
void BuyTowerScreen::registerPersistentDelegates(){

  //bind our delegate function for mouse presses
  EventManager::EventDelegate stateChangeDelegate = std::bind(&BuyTowerScreen::handleStateChange, this, _1);

  //make an event and get its type
  StateChangeEvent stateChangeEvent = StateChangeEvent();
  EventType stateChangeEventType = stateChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(stateChangeDelegate, textLoader -> getString(string("IDS_BTD_SC")),stateChangeEventType);
}

/*
 * Deregisetr the delegated methods for this class
 * so they are not called when we switch off this screen
 */
void BuyTowerScreen::deregisterDelegates(){
  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_BTS_KP")),keyPressEventType);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> deregisterDelegate(textLoader -> getString(string("IDS_BTS_MP")),mousePressEventType);
}


/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void BuyTowerScreen::handleKeyPress(const EventInterface& event){
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
    shared_ptr<EventInterface> playingState = make_shared<StateChangeEvent>(State::Playing, nowInNano);

    this -> eventManager -> queueEvent(playingState);
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void BuyTowerScreen::handleMousePress(const EventInterface& event){
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

  //if true then we return to the playing screen
  bool boughtSomething = false;

  //check for every option if it is selected
  //if it is then we send that data to the gameLogic
  for(shared_ptr<BuyTowerOption> towerOption : options){
    if(towerOption->isClicked(xPos, yPos)){
      //attempt to purchase the tower type at the location
      //if this is an obstacle it will be removed
      if(areBuying){
        boughtSomething = gameLogic -> attemptPurchaseTower(row, col, towerOption -> towerToShow -> getType());
        break;
      }
      else{
        boughtSomething = gameLogic -> attemptSellTower(row, col);
        break;
      }
    }
  }

  if(boughtSomething){
    //the time object of the class
    auto now = high_resolution_clock::now();
    //the actual count in nanoseconds for the time
    auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

    shared_ptr<EventInterface> playGameState = make_shared<StateChangeEvent>(State::Playing,nowInNano);

    this -> eventManager -> queueEvent(playGameState);
  }

  if(backButton->isSelected(xPos,yPos)){
    //the time object of the class
    auto now = high_resolution_clock::now();
    //the actual count in nanoseconds for the time
    auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

    shared_ptr<EventInterface> playGameState = make_shared<StateChangeEvent>(State::Playing,nowInNano);

    this -> eventManager -> queueEvent(playGameState);
  }
}

/*
 * Handle a state change
 * @param event: event of the state change
 */
void BuyTowerScreen::handleStateChange(const EventInterface& event){
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
  if(state != State::BuyTower){
    return;
  }

  row = scEventData -> row;
  col = scEventData -> col;
  areBuying = scEventData -> buy;

  //update the text on the screen to reflect the circumstances of the row, col
  //i.e. is this a tower we are upgrading or selling, is this an obstacle we are
  //removing
  setTextToNewTile();

  //get the tower(s) or obstacles we can buy/sell at this position
  //and populate the options with them
  populateOptionsVector();

}

/*
 * Set the current title text to reflect what is located at the
 * selected tile position
 */
 void BuyTowerScreen::setTextToNewTile(){

   //change what the buyTower button says depending on the what is at the tile
   if(gameLogic->isTower(row,col)){
     //if we are currently buying the tower then we set differnet text than if we are selling one
     if(areBuying){
          changeTitleString(textLoader->getString("IDS_Buy_Tower_Title_Text_Existing_Tower_Or_Empty_Space"));
     }
     else{
          changeTitleString(textLoader->getString("IDS_Buy_Tower_Title_Text_Existing_Tower_To_Sell"));
     }
   }
   else if(gameLogic->isObstacle(row,col)){
     changeTitleString(textLoader->getString("IDS_Buy_Tower_Existing_Obstacle"));
   }
   else if(gameLogic->isEmptySpace(row,col)){
     changeTitleString(textLoader->getString("IDS_Buy_Tower_Title_Text_Existing_Tower_Or_Empty_Space"));
   }
 }

 /*
  * Change the title of the buy tower screen text
  */
 void BuyTowerScreen::changeTitleString(string newTitle){
   this -> currentTitle = newTitle;
 }


/*
 * Generate a tower option to correspond to each tower interface generated
 * for the current row and col selected (i.e. if you are upgrading a tower you
 * get all its upgrade options)
 */
void BuyTowerScreen::populateOptionsVector(){

  //the amount of money the player has
  int balance = (gameLogic -> getPlayer()).getBalance();

  //whether we show the statistics of the option or not
  //set to false for obstacle
  bool showStats = !(gameLogic->isObstacle(row,col));

  vector<shared_ptr<TowerInterface>> towerOptions;
  //if the current space is empty
  if(gameLogic->isEmptySpace(row,col)){
    towerOptions = gameLogic -> allUpgradesForTower(row,col);
  }
  //if the current space is a tower
  else if(gameLogic->isTower(row,col)){
    //if we are upgrading the tower
    if(areBuying){
      towerOptions = gameLogic -> allUpgradesForTower(row,col);
    }
    //if we are selling the tower
    else{
      towerOptions.push_back(gameLogic -> getTowerPlaced(row,col));
    }
  }
  //if we are removing an obstacle
  else if(gameLogic->isObstacle(row,col)){
    towerOptions.push_back(gameLogic -> getTowerPlaced(row,col));
  }
  else{
    cout << "Should never reach here!" << endl;
    assert(true == false);
  }

  //the font path that will be shared for all the tower options
  string fontPath = textLoader -> getString(string("IDS_SFP"));

  //padding in the x and y direction for the options
  float yPadding = (float) textLoader -> getInteger(string("IDS_Buy_Tower_Screen_Options_Padding_Y"));
  float xPadding = (float) textLoader -> getInteger(string("IDS_Buy_Tower_Screen_Options_Padding_X"));

  //the index of the tower option we are currently drawing
  int indexTowerOption = 0;

  //clear the current vector of tower options
  options.clear();

  //the ySize of tower Option
  float ySize = (gameLogic->getWindowY()/(towerOptions.size()*2+1));
  //the xSize of a tower Option
  float xSize = (gameLogic->getWindowX()/(towerOptions.size()*2+1));

  //the xPos of the last tower Option
  float xPos = (indexTowerOption)*xSize + xPadding *(indexTowerOption+1);
  //the yPos of the last tower Option
  float yPos = (gameLogic->getWindowY())/3;

  //vector to hold the maximum value for every MeleeTower
  vector<int> meleeTowerMaxStats(6,0);
  //vector to hold the maximum value for every RangeTower
  vector<int> rangeTowerMaxStats(4,0);

  //make buy tower option object for every tower
  //and gather the statistics
  for(shared_ptr<TowerInterface> tower : towerOptions){

    xPos = (2*indexTowerOption+1)*xSize;

    //whether this is a valid option (i.e. enough mooney)
    //if we are selling then it is always valid
    bool isClickable = !(areBuying) ?  !(areBuying) :  balance >= tower -> getPrice() ? true : false;

    shared_ptr<BuyTowerOption> newOption = make_shared<BuyTowerOption>(textLoader, xPos, yPos, xSize, ySize,
    fontPath, tower, showStats,  windowX, windowY, areBuying, isClickable);

    if(showStats){
      //get the statistics for the tower being drawn as an option
      shared_ptr<vector<int>> towerStats = tower -> getStatistics();
      //iterate through the statstics and store them if they are larger than the current max
      for(int index = 0; index < towerStats->size(); index++){
        //store different statistics if this is a melee or ranged tower
        if(tower->isMelee){
          if(towerStats->at(index) > meleeTowerMaxStats.at(index)){
            meleeTowerMaxStats.at(index) = towerStats->at(index);
          }
        }
        else{
          if(towerStats->at(index) > rangeTowerMaxStats.at(index)){
            rangeTowerMaxStats.at(index) = towerStats->at(index);
          }
        }
      }
    }

    options.push_back(newOption);

    indexTowerOption++;
  }

  if(showStats){
    //finally identify and highlight any differentials between the maximum stat in each category
    // and each tower of the same type
    identifyDifferentialsInStatistics(meleeTowerMaxStats, rangeTowerMaxStats, towerOptions);
  }
}

/*
 * Iterate through the tower optons and identify and highlight differentials between the maximum
 * in each category and all the other towers of the same type
 * @param meleeTowerMaxStats: the stored max stats of all the melee towers
 * @param rangeTowerMaxStats: the stored max stats of all the ranged towers
 * @param towerOptions: the tower options on this screen
 */
 void BuyTowerScreen::identifyDifferentialsInStatistics(vector<int>& meleeTowerMaxStats, vector<int>& rangeTowerMaxStats,
   vector<shared_ptr<TowerInterface>> towerOptions){

  for(int towerOption = 0; towerOption < towerOptions.size(); towerOption++){
    //get the statistics for the tower being drawn as an option
    shared_ptr<vector<int>> towerStats = towerOptions.at(towerOption) -> getStatistics();

    //iterate through the statstics and store them if they are larger than the current max
    for(int index = 0; index < towerStats->size(); index++){
      //store different statistics if this is a melee or ranged tower
      if(towerOptions.at(towerOption)->isMelee){
        int differential =  towerStats->at(index) - meleeTowerMaxStats.at(index);
        options.at(towerOption) -> indicateStatDifferential(index, differential);
      }
      else{
        int differential = towerStats->at(index) - rangeTowerMaxStats.at(index);
        options.at(towerOption) -> indicateStatDifferential(index, differential);
      }
    }
    //realign the buttons once we have edited their text
    options.at(towerOption) -> realignStatButtons();
  }
}
