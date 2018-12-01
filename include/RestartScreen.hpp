#pragma once

#include "Screen.hpp"

class RestartScreen : public Screen {
private:
    enum class Choices {Restart=0, Quit=1};
    int selectedItem;
    int numItems;
    vector<sf::Text> screen;
    sf::Text text;
    sf::Font font;
    sf::Texture picture;
    //event manager (used to register, deregister from events, and create them)
    shared_ptr<EventManager> eventManager;
    //Store the textLoader to make requests for strings and constants
     shared_ptr<TextLoader> textLoader;
public:
  RestartScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY);
  void initText();
  void moveUp();
  void moveDown();
  void draw(sf::RenderWindow& window);
  void handleKeyPress(const EventInterface& event);
  void registerDelegates();
  void deregisterDelegates();
};
