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
    float deltaS = timeDelta.asSeconds() * 2000;

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

  //initlaize the texture loader
  this -> textureLoader = make_shared<TextureLoader>(textLoader);
  //initialize the Game Logic
  this -> gameLogic = make_shared<GameLogic>(textLoader, windowXSize, windowYSize, textureLoader);
  //get the event manager from the game logic so it can be passed to the user View
  //and comp view
  shared_ptr<EventManager> eventManager = this -> gameLogic -> getEventManager();
  //initialize the User View
  this -> userView = unique_ptr<UserView>(new UserView(eventManager, textLoader, gameLogic));
  //initialize the Computer View
  this -> compView = unique_ptr<CompView>(new CompView(eventManager, textLoader, gameLogic, userView->getHeader()));
  //initalize the Computer View for the ai that is allied to the player
  this -> allyCompView = unique_ptr<AllyCompView>(new AllyCompView(eventManager, textLoader, gameLogic, userView->getHeader()));
}


void Game::updateGame(float deltaS,sf::RenderWindow &game){
  this -> gameLogic -> updateGameLogic(deltaS);
  this -> userView -> updateUserView( deltaS, game);
  this -> compView -> updateCompView(deltaS);

}
