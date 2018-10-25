//Main file for Food Fight

#include "Game.hpp"


int main(){
  //make a Game
  auto foodFight = unique_ptr<Game>(new Game());
;
  //start game clock
  sf::Clock gameClock;

  // create main window
  sf::RenderWindow game(sf::VideoMode(800,600,32), "Food Fight", sf::Style::Close);

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

void Game::initGame(sf::RenderWindow  &game){
  // clear screen and fill with black
  game.clear(sf::Color::Black);

  // display
  game.display();

  //get the size of the render window
  sf::Vector2u windowSize = game.getSize();

  //dimensions of the window
  unsigned int windowX = windowSize.x;
  unsigned int windowY = windowSize.y;

  //initialize the Game Logic
  this -> gameLogic = make_shared<GameLogic>(GameLogic());
  //get the event manager from the game logic so it can be passed to the user View
  //and comp view
  shared_ptr<EventManager> eventManager = this -> gameLogic -> getEventManager();
  //initialize the User View
  this -> userView = unique_ptr<UserView>(new UserView(eventManager, game));
  //initlaize the Computer View
  this -> compView = unique_ptr<CompView>(new CompView(eventManager));
}


void Game::updateGame(float deltaS,sf::RenderWindow &game){

  this -> gameLogic -> updateGameLogic(deltaS);
  this -> userView -> updateUserView( deltaS, game);
  this -> compView -> updateCompView(deltaS);

}
