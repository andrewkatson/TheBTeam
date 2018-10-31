#pragma once

#include "Screen.hpp"

class BuyTowerScreen : public Screen {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
public:
  BuyTowerScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY);

  void draw(sf::RenderWindow& window);
};
