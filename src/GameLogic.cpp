/*
  GameLogic.cpp

  Purpose: Handle all logical processes for Food Fight.

  @author Andrew Katson, Jeremy Elkayam
 */
#include "GameLogic.hpp"

//Constructor.
GameLogic::GameLogic(shared_ptr<TextLoader> textLoader, int windowX, int windowY){
  this -> textLoader = textLoader;
  this -> eventManager = make_shared<EventManager>();
  this -> boardManager = unique_ptr<BoardManager>(new BoardManager(eventManager, textLoader));
  this -> gameState = unique_ptr<GameState>(new GameState(eventManager));
  this -> towerManager = unique_ptr<TowerManager>(new TowerManager(eventManager, textLoader));
  this -> player = unique_ptr<Player>(new Player(eventManager, textLoader));
  this -> soundManager = unique_ptr<SoundManager>(new SoundManager(eventManager));
  this -> waveManager = unique_ptr<WaveManager>(new WaveManager(eventManager, textLoader));
  this -> projectileManager = unique_ptr<ProjectileManager>(new ProjectileManager(eventManager));
  this -> registerEvents();
  this -> registerDelegates();
  test = true;
  this -> windowX = windowX;
  this -> windowY = windowY;
}

/*
 * any events created by this class must be registered with the
 * Event Manager
 */
 void GameLogic::registerEvents(){
   //make a generic tower creation event, get its type, and register it
   TowerCreationEvent towerCreationEvent = TowerCreationEvent();
   EventType towerCreationEventType = towerCreationEvent.getEventType();

   this -> eventManager -> registerEvent(towerCreationEventType);

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

  //bind our delegate function for mouse presses
  EventManager::EventDelegate stateChangeDelegate = std::bind(&GameLogic::handleStateChange, this, _1);

  //make an event and get its type
  StateChangeEvent stateChangeEvent = StateChangeEvent();
  EventType stateChangeEventType = stateChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(stateChangeDelegate, textLoader -> getString(string("IDS_GLD_SC")),stateChangeEventType);
}


//Called once every loop. Update according to elapsed time.
void GameLogic::updateGameLogic(float deltaS){
  this -> eventManager -> processEvent();

  if(boardManager -> hasMap() && test == true){
    int row = 3;
    int col = 3;
    vector<shared_ptr<TowerInterface>> allTowers = allUpgradesForTower(row, col);

    if(allTowers.size() != 0){
      shared_ptr<TowerInterface> tower = allTowers.at(0);
      string towerType = tower -> getType();
      if(canBuy(towerType)){
        createATower(row,col,towerType);
      }

      cout << "is there a tower now? " << boardManager -> isTower(row, col) << endl;
      if(boardManager -> isTower(row, col)){
        removeATower(row,col);
      }
    }

    test = false;
  }

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

/*
 * Handle a state change
 * @param event: event of the state change (i.e. play to options )
 */
void GameLogic::handleStateChange(const EventInterface& event){
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

  //set the current state to be the state changed
  gameState -> setState(state);

  //if the state is playing we generate a new map
  //only if one is not currently existing
  if(!(boardManager -> hasMap()) && State::Playing == state){
    makeNewMap();
  }
}

/*
 * Have a new map generated (callable by the UserView)
 */
 void GameLogic::makeNewMap(){
   this -> boardManager -> newMap();
   int xDim = boardManager -> getXDim();
   int yDim = boardManager -> getYDim();
   this -> towerManager -> setDimensions(xDim, yDim);
   placeObstacles();
 }

/*
 * Send the list of obstacles and their types from the
 * board manager to the tower manager for their creation
 */
void GameLogic::placeObstacles(){
  //an unordered map where the type of the obstacle is the key
  //and the position is a pair
  unordered_map<int, intPair> obstacleValueToPos;
  obstacleValueToPos = boardManager -> getAllObstacles();

  towerManager -> addObstacles(obstacleValueToPos);
}


//return a reference to the event manager
shared_ptr<EventManager> GameLogic::getEventManager(){
  return this -> eventManager;
}

/*
 * Return a vector with all the towers that can be used to upgrade
 * @param row: the row of the tower
 * @param col: the col of the tower
 */
vector<shared_ptr<TowerInterface>>& GameLogic::allUpgradesForTower(int row, int col){
  static vector<shared_ptr<TowerInterface>> noTowers;
  //return an empty vector if the space is a path, exit, or an obstacle
  if(boardManager -> isExit(row,col)){
    return noTowers;
  }
  if(boardManager -> isPath(row,col)){
    return noTowers;
  }
  //if there is an obstacle here than we want the obstacle
  //because we are just trying to remove it
  if(boardManager -> isObstacle(row,col)){
    return towerManager -> getObstacleAsVector(row,col);
  }

  shared_ptr<TowerInterface> tower = towerManager -> getTowerPlaced(row,col);

  string towerID = tower -> getType();

  return towerManager -> getUpgradesForTower(towerID);
}

/*
 * Attempt a purchase of a tower at a particular location
 * @param row: the row of the tile
 * @param col: the col of the tile
 * @param towerTypeID: the string identifier of the tower
 * @return bool: whether they were successful or not
 */
bool GameLogic::attemptPurchaseTower(int row, int col, string towerTypeID){
  //if we canbuy a tower of this type than create one
  if(canBuy(towerTypeID)){
    createATower(row, col, towerTypeID);
    return true;
  }
  //return false in case we want the buy tower screen to make an indication of failure
  else{
    return false;
  }
}

/*
 * @param row: the row of the target
 * @param col: the col of the target
 * @return whether the user can buy the obstacle/tower at the space selected
 */
bool GameLogic::canBuy(int row, int col){
  bool isExit = (boardManager -> isExit(row,col));
  //check if this is not the exit
  if(isExit){
    return false;
  }

  bool isPath = (boardManager -> isPath(row,col));
  //check if this is not on a path
  if(isPath){
    return false;
  }
  //return whether the obstacle/tower at this position is too expensive
  bool tooExpensive = towerManager -> getTowerPrice(row,col) <= player -> getBalance();

  return tooExpensive;
}

/*
 * @param towerType: the tower type to be created
 * @return whether the user can buy the obstacle/tower at the space selected
 */
bool GameLogic::canBuy(string towerType){
  //return whether the obstacle/tower at this position is too expensive
  bool tooExpensive = towerManager -> getTowerPrice(towerType) <= player -> getBalance();
  return tooExpensive;
}

/*
 * make a tower creation event
 * @param row: the row of the target
 * @param col: the col of the target
 * @param towerType: the type of the tower to be created
 */
void GameLogic::createATower(int row, int col, string towerType){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  int combinedRowCol = row*(boardManager -> getXDim()) + col;

  shared_ptr<EventInterface> tcEvent = make_shared<TowerCreationEvent>(combinedRowCol, towerType, nowInNano);

  this -> eventManager -> queueEvent(tcEvent);
}

/*
 * Sell tower at this position and create a removeTower event
 * @param row: row index of tower
 * @param col: the col index of tower
 */
void GameLogic::removeATower(int row, int col){

}

/*```
 * Return the current GameState
 */
State GameLogic::getGameState(){
  return gameState -> getState();
}

/*
 * Handle any cleanup required for shutting down the game
 */
void GameLogic::shutDown(){

}

/*
 * Get the grid showing the floor
 */
const vector<vector<int>>& GameLogic::getFloor(){
  return boardManager -> getFloor();
}

/*
 * Get the grid showing anything placed above the floor (i.e. obstacles and towers)
 */
const vector<vector<int>>& GameLogic::getAboveFloor(){
  return boardManager -> getAboveFloor();
}

/*
 * Get the grid showing the distance from any cell to the exit
 */
const vector<vector<int>>& GameLogic::getDistances(){
  return boardManager -> getDistances();
}
