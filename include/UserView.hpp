#ifndef USERVIEW_H
#define USERVIEW_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include "EventManager.hpp"
#include "UserInputManager.hpp"
#include "Button.hpp"
#include "GameLogic.hpp"


#define textNormal = 255, 255, 255
#define textHighlight = 255, 200, 10
#define windowX 800
#define windowY 600

using std::shared_ptr;
using std::unique_ptr;
//allows you to use _1 and _2 etc... for binding
using namespace std::placeholders;
class UserView{
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //receives user input through keys or mouse
  unique_ptr<UserInputManager> userInputManager;
  //the render window that the game is drawn on
  sf::RenderWindow *game;

  sf::Font font;
  sf::Text title;


  unique_ptr<Button> playButton,optionButton,exitButton,backButton;
public:
  UserView(shared_ptr<EventManager> eventManager, sf::RenderWindow &game);

  ~UserView();

  void registerDelegates();

  void handleKeyPress(const EventInterface& event);

  void updateUserView(float deltaS, sf::RenderWindow &game);

  void shutDown();
};

#endif
