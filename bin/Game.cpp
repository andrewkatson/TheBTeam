//Main file for Food Fight

#include "Game.hpp"

int main(){

  //make a Game
  auto foodFight = unique_ptr<Game>(new Game());

  //make the text loader
  foodFight -> setUpTextLoader();

  //start game clock
  sf::Clock gameClock;

  // create main window
  sf::RenderWindow game(sf::VideoMode(800,600,32),
    foodFight -> textLoader -> getString("IDS_GAMETITLE"), sf::Style::Close);

  foodFight -> initGame(game);

  // start main loop
  while(game.isOpen())
  {
    sf::Time timeDelta = gameClock.restart();
    float deltaS = timeDelta.asSeconds();
    foodFight -> updateGame(deltaS, game);

  }
}

Game::Game(){}

void Game::setUpTextLoader(){
  //initialize the Text Loader(for xml files)
  this -> textLoader = make_shared<TextLoader>(TextLoader());
}

void Game::initGame(sf::RenderWindow  &game){
  // clear screen and fill with black
  game.clear(sf::Color::Black);

  // display
  game.display();

  //get the size of the render window
  sf::Vector2u windowSize = game.getSize();

  //dimensions of the window
  unsigned int windowXSize = windowSize.x;
  unsigned int windowYSize = windowSize.y;

  speedScale=1;

  //world -> SetContactListener(&collisionCallbackInstance);

  //initlaize the texture loader
  this -> textureLoader = make_shared<TextureLoader>(textLoader);
  //initialize the Game Logic
  this -> gameLogic = make_shared<GameLogic>(textLoader, windowXSize, windowYSize, textureLoader);
  //get the event manager from the game logic so it can be passed to the user View
  //and comp view
  eventManager= this -> gameLogic -> getEventManager();
  //initialize the User View
  this -> userView = unique_ptr<UserView>(new UserView(eventManager, textLoader, gameLogic));
  //initialize the Computer View
  this -> compView = unique_ptr<CompView>(new CompView(eventManager, textLoader, gameLogic, userView->getHeader()));
  //initalize the Computer View for the ai that is allied to the player
  this -> allyCompView = unique_ptr<AllyCompView>(new AllyCompView(eventManager, textLoader, gameLogic, userView->getHeader()));

  this -> registerDelegates();
}


void Game::updateGame(float deltaS,sf::RenderWindow &game){
  deltaS*=speedScale;
  //cout << "elapsed: " << deltaS << endl;

  this -> gameLogic -> updateGameLogic(deltaS);
  this -> userView -> updateUserView(deltaS, game);
  this -> compView -> updateCompView(deltaS);
  this -> allyCompView -> updateAllyCompView(deltaS);


}

void Game::registerDelegates() {
  //bind our delegate function for speed changes
  EventManager::EventDelegate speedChangeDelegate= std::bind(&Game::handleSpeedChange, this, _1);

  //make an event and get its type
  SpeedChangeEvent speedChangeEvent = SpeedChangeEvent();
  EventType speedChangeEventType = speedChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(speedChangeDelegate, textLoader -> getString(string("IDS_Game_SpeedChange")),speedChangeEventType);

  //bind our delegate function map generation
  EventManager::EventDelegate mapGeneratedEventDelegate = std::bind(&Game::handleMapGeneration, this, _1);

  //make an event and get its type
  MapGeneratedEvent mapGeneratedEvent = MapGeneratedEvent();
  EventType mapGeneratedEventType = mapGeneratedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(mapGeneratedEventDelegate, textLoader -> getString(string("IDS_Game_Map_Generated_Delegate")),mapGeneratedEventType);

  //bind our delegate function for level changes
  EventManager::EventDelegate levelChangeEventDelegate= std::bind(&Game::handleLevelChange, this, _1);

  //make an event and get its type
  LevelChangeEvent levelChangeEvent = LevelChangeEvent();
  EventType levelChangeEventType = levelChangeEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(levelChangeEventDelegate, textLoader -> getString(string("IDS_Game_Level_Change_Delegate")),levelChangeEventType);

  //bind our delegate function for game restarts
  EventManager::EventDelegate restartGameEventDelegate= std::bind(&Game::handleRestartGame, this, _1);

  //make an event and get its type
  RestartGameEvent restartGameEvent = RestartGameEvent();
  EventType restartGameEventType = restartGameEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(restartGameEventDelegate, textLoader -> getString(string("IDS_Game_Restarted_Delegate")),restartGameEventType);

}

void Game::deregisterDelegates() {

}

void Game::handleSpeedChange(const EventInterface &event) {


  const SpeedChangeEvent* scEvent = static_cast<const SpeedChangeEvent*>(&event);

  SpeedChangeEventData* scEventData = static_cast<SpeedChangeEventData*>((scEvent -> data).get());

  speedScale=scEventData->newSpeedScale;
}

void Game::handleMapGeneration(const EventInterface &event){

}

/*
 * Handle Levels (avoids race conditions)
 */
void Game::handleLevelChange(const EventInterface &event){
  gameLogic->handleLevelChangeEvent(event);
  userView->handleLevelChangeEvent(event);
}

/*
 * Handle Restarts (avoids race conditions)
 */
void Game::handleRestartGame(const EventInterface &event){
  gameLogic->handleRestartGameEvent(event);
  userView->handleRestartGameEvent(event);
}
