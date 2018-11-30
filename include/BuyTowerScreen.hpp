#pragma once

#include "Screen.hpp"
#include "BuyTowerOption.hpp"
#include "Button.hpp"

class BuyTowerScreen : public Screen {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;
  //back button
  unique_ptr<Button> backButton;
  //used to load font
  sf::Font font;
  //first index is the title
  vector<sf::Text> texts;
  //the current string for the title
  string currentTitle;
  //int row clicked on
  int row;
  //int col clicked on
  int col;
  //whether we are buying or selling (only applies when there is a tower)
  bool areBuying;
  //all the tiles of options to show on the screen
  vector<shared_ptr<BuyTowerOption>> options;

public:
  BuyTowerScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,int windowX, int windowY);
  void initDrawingMaterials();
  void initText();
  void initBackButton();

  void draw(sf::RenderWindow& window);
  void drawTitle(sf::RenderWindow& window);
  void registerDelegates();
  void registerPersistentDelegates();
  void deregisterDelegates();
  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
  void handleStateChange(const EventInterface& event);

  void changeTitleString(string newTitle);

  void setTextToNewTile();

  void populateOptionsVector();
  void identifyDifferentialsInStatistics(vector<int>& meleeTowerMaxStats, vector<int>& rangeTowerMaxStats,
     vector<shared_ptr<TowerInterface>> towerOptions);
};
