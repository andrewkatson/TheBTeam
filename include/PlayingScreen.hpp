#pragma once

#include "Screen.hpp"
#include "GameLogic.hpp"
#include "Button.hpp"

class PlayingScreen : public Screen {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;
  //rectangle shape used for drawing on the map
  sf::RectangleShape floorRect;
  //the button to allow us to buy a tower
  Button buyTower;
  //the main font of the game
  sf::Font mainFont;
  //text object used to write with
  sf::Text text;

  //testing variable TODO remove when finished rendering
  bool somethingChanged;

public:
  PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,shared_ptr<GameLogic> gameLogic,int windowX, int windowY);

  void registerDelegates();
  void deregisterDelegates();
  void initDrawingMaterials();
  void initBuyTowerButton();

  void handleTowerCreation(const EventInterface& event);
  void handleTowerRemove(const EventInterface& event);
  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);

  void draw(sf::RenderWindow& window);
  void drawBuyTowerButton(sf::RenderWindow& window);
  void drawFloorMap(sf::RenderWindow& window);
  void drawFloorPath(sf::RenderWindow& window, int row, int col, int yTileSize, int xTileSize, int pathValue);
  void drawFloorTile(sf::RenderWindow& window, int row, int col, int yTileSize, int xTileSize, int tileValue);
  void drawFloorExit(sf::RenderWindow& window, int row, int col, int yTileSize, int xTileSize);

  template <class T>
  void printVector(const vector<vector<T>> &v);
};
