#pragma once
#include "Screen.hpp"
#include "Switcher.hpp"
#include "SelectionManager.hpp"
#include "UserInputManager.hpp"
#include "Button.hpp"
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
  //back button
  unique_ptr<Button> backButton;
  shared_ptr<Switcher>  school;
  shared_ptr<Switcher>  population;
  shared_ptr<Switcher>  obstacles;
  shared_ptr<Switcher>  meal;
  shared_ptr<Switcher>  startMoney;
  shared_ptr<Switcher>  cafeteriaSize;

public:
  OptionsMenuScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,int windowX, int windowY, int numItems);
  void initDrawingMaterials();
  void initText();
  void initBackButton();
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();
  void draw(sf::RenderWindow &window);
  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
  void optionSelected();
  void registerDelegates();
  void deregisterDelegates();
  int getSelectedItem() {return selectedItem;}
};
