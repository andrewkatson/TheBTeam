#include "UserView.hpp"


UserView::UserView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic){

  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> userInputManager = unique_ptr<UserInputManager>(new UserInputManager(eventManager));
  this -> shutDownGame = false;
  this -> registerDelegates();
  this -> registerEvents();
  this -> gameLogic = gameLogic;
  this -> initScreens();
  this -> updateState();
}

UserView::~UserView(){

}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void UserView::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&UserView::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_UVD_KP")),keyPressEventType);

  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&UserView::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_UVD_MP")),mousePressEventType);


  //bind our delegate function for mouse presses
  EventManager::EventDelegate stateChangeDelegate = std::bind(&UserView::handleStateChange, this, _1);

  //make an event and get its type
  StateChangeEvent stateChangeEvent = StateChangeEvent();
  EventType stateChangeEventType = stateChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(stateChangeDelegate, textLoader -> getString(string("IDS_UVD_SC")),stateChangeEventType);
}

//TODO MOVE TO GAMESCREEN WHEN IT IS MADE
/*
 * any events created by this class must be registered with the
 * Event Manager
 */
void UserView::registerEvents(){
  //make a generic tower creation event, get its type, and register it
  TowerCreationEvent event = TowerCreationEvent();
  EventType type = event.getEventType();
  this -> eventManager -> registerEvent(type);
}

/*
 * Initialize all the screens that can be made by the user view
 */
void UserView::initScreens(){
  //Main Menu Screen
  shared_ptr<Screen> mainMenuScreen = make_shared<MainMenuScreen>(eventManager,windowX, windowY, 3, textLoader);
  //main menu is the defualt screen so its delegates are registered by default
  mainMenuScreen -> registerDelegates();

  //Options Menu Screen
  shared_ptr<Screen> optionsMenuScreen = make_shared<OptionsMenuScreen>(eventManager, textLoader, windowX, windowY, 6, font);
  //Buy Tower Sreeen
  shared_ptr<Screen> buyTowerScreen = make_shared<BuyTowerScreen>(eventManager, textLoader,gameLogic, windowX, windowY);
  //Playing Screen
  shared_ptr<Screen> playingScreen = make_shared<PlayingScreen>(eventManager, textLoader,gameLogic, windowX, windowY);
  //Restart Screen
  shared_ptr<Screen> restartScreen = make_shared<RestartScreen>(eventManager, textLoader,windowX, windowY);

  screens.push_back(mainMenuScreen);
  screens.push_back(optionsMenuScreen);
  screens.push_back(playingScreen);
  screens.push_back(buyTowerScreen);
  screens.push_back(restartScreen);
}

/*
 * Initlaize any data related to font
 */
void UserView::initText(){
  string mainFontPath = textLoader -> getString(string("IDS_MFP"));

  if(!font.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
  //  cout << "loaded font!" << endl;
  }

}

/*
 * Update the state. Which will change the screen
 */
void UserView::updateState(){
 screen = gameLogic -> getGameState();
}



/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void UserView::handleKeyPress(const EventInterface& event){
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

  if(key == "CLOSE"){
    shutDownGame = true;
  }
  else if(key == "Q"){
    shutDownGame = true;
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void UserView::handleMousePress(const EventInterface& event){
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

}

/*
 * Handle a state change
 * @param event: event of the state change (i.e. play to options )
 */
void UserView::handleStateChange(const EventInterface& event){
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
  //get integer of the state change
  State state = scEventData -> state;

  //deregister all the delegates for the old state
  (this->screens).at((int)screen) -> deregisterDelegates();

  //change the screen to the current state
  screen = state;

  //register all the delegagtes for the new state
  (this->screens).at((int)screen) -> registerDelegates();
}

void UserView::updateUserView(float deltaS, sf::RenderWindow &game){
  if(shutDownGame){
    shutDown(game);
  }
  game.clear();
  this -> userInputManager -> processUserInput(game);
  screens.at((int)screen) -> draw(game);
  game.display();
}

void UserView::shutDown(sf::RenderWindow &game){
  game.close();
}
