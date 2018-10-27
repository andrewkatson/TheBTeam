/*
  GameLogic.cpp

  Purpose: Handle all logical processes for Food Fight.

  @author Andrew Katson, Jeremy Elkayam
 */
#include "GameLogic.hpp"

//Constructor.
GameLogic::GameLogic(shared_ptr<TextLoader> textLoader){
  this -> textLoader = textLoader;
  this -> eventManager = make_shared<EventManager>(EventManager());
  this -> boardManager = unique_ptr<BoardManager>(new BoardManager(eventManager, textLoader));
  this -> gameState = unique_ptr<GameState>(new GameState(eventManager));
  this -> towerManager = unique_ptr<TowerManager>(new TowerManager(eventManager, textLoader, boardManager -> getYDim(), boardManager -> getXDim()));
  this -> player = unique_ptr<Player>(new Player(eventManager));
  this -> soundManager = unique_ptr<SoundManager>(new SoundManager(eventManager));
  this -> waveManager = unique_ptr<WaveManager>(new WaveManager(eventManager, textLoader));
  this -> projectileManager = unique_ptr<ProjectileManager>(new ProjectileManager(eventManager));
  this -> registerDelegates();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void GameLogic::registerDelegates(){
  //bind our delegate function for key presses
  EventManager::EventDelegate delegate = std::bind(&GameLogic::handleKeyPress, this, _1);

  //make an event and get its type
  KeyPressEvent event = KeyPressEvent();
  EventType type = event.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(delegate, textLoader -> getString(string("IDS_GLD1")),type);
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

//return a reference to the event manager
shared_ptr<EventManager> GameLogic::getEventManager(){
  return this -> eventManager;
}

/*
 * Handle any cleanup required for shutting down the game
 */
void GameLogic::shutDown(){

}
