#pragma once

#include "Screen.hpp"

class BuyTowerScreen : public Screen {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //used to load font
  sf::Font font;
  //first index is the title
  vector<sf::Text> texts;
public:
  BuyTowerScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY);
  void initText();

  void draw(sf::RenderWindow& window);
  void registerDelegates();
  void deregisterDelegates();
  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
};
