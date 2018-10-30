/*
  GameLogic.cpp

  Purpose: Handle all logical processes for Food Fight.

  @author Andrew Katson, Jeremy Elkayam
 */
#include "GameLogic.hpp"

//Constructor.
GameLogic::GameLogic(shared_ptr<TextLoader> textLoader, int windowX, int windowY){
  this -> textLoader = textLoader;
  this -> eventManager = make_shared<EventManager>(EventManager());
  this -> boardManager = unique_ptr<BoardManager>(new BoardManager(eventManager, textLoader));
  this -> gameState = unique_ptr<GameState>(new GameState(eventManager));
  this -> towerManager = unique_ptr<TowerManager>(new TowerManager(eventManager, textLoader, boardManager -> getYDim(), boardManager -> getXDim()));
  this -> player = unique_ptr<Player>(new Player(eventManager, textLoader));
  this -> soundManager = unique_ptr<SoundManager>(new SoundManager(eventManager));
  this -> waveManager = unique_ptr<WaveManager>(new WaveManager(eventManager, textLoader));
  this -> projectileManager = unique_ptr<ProjectileManager>(new ProjectileManager(eventManager));
  this -> registerDelegates();

  this -> windowX = windowX;
  this -> windowY = windowY;
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void GameLogic::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate keyPressDelegate = std::bind(&GameLogic::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent keyPressEvent = KeyPressEvent();
  EventType keyPressEventType = keyPressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(keyPressDelegate, textLoader -> getString(string("IDS_GLD_KP")),keyPressEventType);
  //bind our delegate function for mouse presses
  EventManager::EventDelegate mousePressDelegate = std::bind(&GameLogic::handleMousePress, this, _1);

  //make an event and get its type
  MousePressEvent mousePressEvent = MousePressEvent();
  EventType mousePressEventType = mousePressEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mousePressDelegate, textLoader -> getString(string("IDS_GLD_MP")),mousePressEventType);
}


//Called once every loop. Update according to elapsed time.
void GameLogic::updateGameLogic(float deltaS){
  this -> eventManager -> processEvent();
}
/*
 * Handle any key press from the user
 * @param event: event of the key press
 */
void GameLogic::handleKeyPress(const EventInterface& event){
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
    shutDown();
  }
  else if(key == "Q"){
    shutDown();
  }
}

/*
 * Handle any mouse press from the user
 * @param event: event of the mouse press
 */
void GameLogic::handleMousePress(const EventInterface& event){
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

//return a reference to the event manager
shared_ptr<EventManager> GameLogic::getEventManager(){
  return this -> eventManager;
}

/*
 * @param row: the row of the target
 * @param col: the col of the target
 * @return whether the user can buy the obstacle/tower at the space selected
 */
bool GameLogic::canBuy(int row, int col){
  bool obstacleOrTower = (boardManager -> isTowerOrObstacle(row,col));
  //check if there is even a tower or obstacle at the position
  if(!obstacleOrTower){
    return false;
  }

  //return whether the obstacle/tower at this position is too expensive
  return getTowerPrice(row,col) <= player -> getBalance();
}

/*
 * Return the price of a tower at the speicifed grid location
 * @param row: the row of the tower on the grid
 * @param col: the col of the tower on the grid
 */
int GameLogic::getTowerPrice(int row, int col){
  return towerManager -> getTowerPrice(row, col);
}

/*
 * Handle any cleanup required for shutting down the game
 */
void GameLogic::shutDown(){

}
