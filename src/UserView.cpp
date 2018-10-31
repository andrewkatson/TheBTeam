#include "UserView.hpp"


UserView::UserView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic){

  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> userInputManager = unique_ptr<UserInputManager>(new UserInputManager(eventManager));
  this -> shutDownGame = false;
  this -> registerDelegates();
  this -> registerEvents();
  this -> gameLogic = gameLogic;
  check = 10;
  string mainFontPath = textLoader -> getString(string("IDS_MFP"));

  if(!font.loadFromFile(mainFontPath)){
    cout << "No font!" << endl;
  }
  else{
    cout << "loaded font!" << endl;
  }

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
  shared_ptr<Screen> mainMenuScreen = make_shared<MainMenuScreen>(MainMenuScreen(eventManager,windowX, windowY, 3, textLoader));
  //Options Menu Screen
  shared_ptr<Screen> optionsMenuScreen = make_shared<OptionsMenuScreen>(OptionsMenuScreen(eventManager, textLoader, windowX, windowY, 7, font));
  //Playing Screen
  shared_ptr<Screen> playingScreen = make_shared<PlayingScreen>(PlayingScreen(eventManager, textLoader,windowX, windowY));
  //Buy Tower Sreeen
  shared_ptr<Screen> buyTowerScreen = make_shared<BuyTowerScreen>(BuyTowerScreen(eventManager, textLoader,windowX, windowY));
  //Restart Screen
  shared_ptr<Screen> restartScreen = make_shared<RestartScreen>(RestartScreen(eventManager, textLoader,windowX, windowY));

  screens.push_back(mainMenuScreen);
  screens.push_back(optionsMenuScreen);
  screens.push_back(playingScreen);
  screens.push_back(buyTowerScreen);
  screens.push_back(restartScreen);
}

/*
 * Update the state. Which will change the screen
 */
void UserView::updateState(){
 State state = gameLogic -> getGameState();
 screen = (int)state;
}



/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void UserView::handleKeyPress(const EventInterface& event){
  cout << "check " << check << endl;
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

  cout << "key! " << key << endl;
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

void UserView::updateUserView(float deltaS, sf::RenderWindow &game){
  if(shutDownGame){
    shutDown(game);
  }
  game.clear();

  this -> userInputManager -> processUserInput(game);
  screens.at(screen) -> draw(game);

  game.display();
}

void UserView::shutDown(sf::RenderWindow &game){
  game.close();
}
