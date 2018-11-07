#pragma once

#include "Screen.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;
class MainMenuScreen : public Screen{
private:
  int selectedItem;
  int numItems;
  vector<sf::Text> screen;
  sf::Font font;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
public:
  MainMenuScreen(shared_ptr<EventManager> eventManager,int windowX, int windowY, int numItems,shared_ptr<TextLoader> textLoader);
  void initText();
  void draw(sf::RenderWindow& window);
  void moveUp();
  void moveDown();
  void registerEvents();
  void registerDelegates();
  void deregisterDelegates();
  void handleKeyPress(const EventInterface& event);
  void anyFunction();

};
