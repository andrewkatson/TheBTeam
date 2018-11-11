#pragma once

#include "Screen.hpp"

class BuyTowerScreen : public Screen {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;
  //used to load font
  sf::Font font;
  //first index is the title
  vector<sf::Text> texts;
  //the current string for the title
  string currentTitle;
public:
  BuyTowerScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,int windowX, int windowY);
  void initText();
  void changeTitleString(string newTitle);

  void draw(sf::RenderWindow& window);
  void registerDelegates();
  void deregisterDelegates();
  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
};
