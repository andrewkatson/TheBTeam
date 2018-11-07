#include "PlayingScreen.hpp"


PlayingScreen::PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic, int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> gameLogic = gameLogic;
  this -> buyTower = Button(windowX, windowY, TOPRIGHT, textLoader -> getString(string("IDS_Buy_Tower_Button_Message")), textLoader);
  somethingChanged = true;
  this -> registerDelegates();
  this -> setDrawingMaterials();
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
}

/*
 * Initialize all the things used for drawing (shapes, fonts)
 */
void PlayingScreen::setDrawingMaterials(){
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

  //used to make the font local
  string mainFontPath = textLoader -> getString(string("IDS_MFP"));

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
