#pragma once

#include "Screen.hpp"
#include "GameLogic.hpp"
#include "Button.hpp"
#include "PlayingScreenHeader.hpp"
#include <random>
#include <tuple>

using std::tuple;
using std::make_tuple;
using std::get;
class PlayingScreen : public Screen {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;
  //encapsulates the header on the top of the screen with information on the player
  unique_ptr<PlayingScreenHeader> playingScreenHeader;
  //the main font of the game
  sf::Font mainFont;
  //text object used to write with
  sf::Text text;
  //random number generator (seeded in the constructor)
  std::mt19937 mt;
  //a tuple for rgb int values
  typedef tuple<int,int,int> rgb;
  //a 2d grid of tuples (r,g,b) shift values so that all the colors will not be exactly their
  //exact color on file (used for the floor)
  vector<vector<rgb>> floorColorShifts;
  //a 2d grid of tuples (r,g,b) shift values so that all the colors will not be exactly their exact
  //color on file (used for the paths)
  vector<vector<rgb>> pathColorShifts;
  //cannot initialize the colors until we have a map made
  //so we use this bool to set the color shift vector once
  bool haveSetColorShift;
  //the current row selected
  int rowSelected;
  //the current col selected
  int colSelected;


  //testing variable TODO remove when finished rendering
  bool somethingChanged;

public:
  PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,shared_ptr<GameLogic> gameLogic, int windowX, int windowY);

  void registerDelegates();
  void deregisterDelegates();
  void initDrawingMaterials();
  void initBuyTowerButton();
  void initColorShifts();
  void initColorShiftsForFloor();
  void initColorShiftsForPath();

  void handleMapGenerated(const EventInterface& event);
  void handleTowerCreation(const EventInterface& event);
  void handleTowerRemove(const EventInterface& event);
  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);

  void draw(sf::RenderWindow& window);
  void drawFloorMap(sf::RenderWindow& window);
  void drawFloorPath(sf::RenderWindow& window, int row, int col, int yTileSize,
    int xTileSize, int pathValue, sf::RectangleShape& floorRect);
  void drawFloorTile(sf::RenderWindow& window, int row, int col, int yTileSize,
     int xTileSize, int tileValue, sf::RectangleShape& floorRect);
  void drawFloorExit(sf::RenderWindow& window, int row, int col, int yTileSize,
     int xTileSize, sf::RectangleShape& floorRect);
  void drawTowersAndObstacles(sf::RenderWindow& window);
  void drawTowerUnits(shared_ptr<TowerInterface> meleeTower, sf::RenderWindow& window);
  void drawEnemyUnits(sf::RenderWindow& window);
  void drawBuyTowerButton(sf::RenderWindow& window);


  template <class T>
  void printVector(const vector<vector<T>> &v);
};
