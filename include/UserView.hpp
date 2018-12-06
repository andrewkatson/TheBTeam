#ifndef USERVIEW_H
#define USERVIEW_H
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include "EventManager.hpp"
#include "UserInputManager.hpp"
#include "Button.hpp"
#include "Screen.hpp"
#include "MainMenuScreen.hpp"
#include "OptionsMenuScreen.hpp"
#include "RestartScreen.hpp"
#include "BuyTowerScreen.hpp"
#include "PlayingScreen.hpp"
#include "LoadingScreen.hpp"
#include "PlayingScreenHeader.hpp"
#include "GameLogic.hpp"

#define textNormal = 255, 255, 255
#define textHighlight = 255, 200, 10
#define windowX 800
#define windowY 600

using std::shared_ptr;
using std::unique_ptr;
//allows you to use _1 and _2 etc... for binding
class UserView{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //receives user input through keys or mouse
  unique_ptr<UserInputManager> userInputManager;
  //logic of the game. handles mechanics
  shared_ptr<GameLogic> gameLogic;
  //the vector of screens
  vector<shared_ptr<Screen>> screens;
  //index of the current screen
  State screen;
  bool shutDownGame;

  sf::Font font;
  sf::Text title;
  int check;

public:
  UserView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader,
    shared_ptr<GameLogic> gameLogic);

  ~UserView();

  void registerDelegates();
  void deregisterDelegates();

  void registerEvents();

  void initText();
  void initScreens();

  void updateState();

  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
  void handleStateChange(const EventInterface& event);

  void updateUserView(float deltaS, sf::RenderWindow &game);

  void shutDown(sf::RenderWindow &game);

  shared_ptr<PlayingScreenHeader> getHeader(){ return std::static_pointer_cast<PlayingScreen>(screens[2])->getHeader();};
};

#endif
