#pragma once
#include "Screen.hpp"
#include <vector>

using std::vector;

class OptionsMenuScreen : public Screen {
private:
  int numItems;
  int selectedItem;
  vector<sf::Text> screen;
  sf::Font font;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  int check;

public:
  OptionsMenuScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY, int numItems, sf::Font font);
  void initText();
  void moveUp();
  void moveDown();
  void moveRight();
  void draw(sf::RenderWindow &window);
  void handleKeyPress(const EventInterface& event);
  void registerDelegates();
  void deregisterDelegates();
  int getSelectedItem() {return selectedItem;}
};
