#pragma once

#include "SFML/Window.hpp"
#include "Screen.hpp"
#include "GameLogic.hpp"
#include "Button.hpp"
#include "PlayingScreenHeader.hpp"
#include "UpgradeCircle.hpp"
#include <random>
#include <tuple>

using std::tuple;
using std::make_tuple;
using std::get;

typedef pair<int,int> intPair;
class PlayingScreen : public Screen {
private:
  sf::Mouse mouse;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;
  //encapsulates the header on the top of the screen with information on the player
  shared_ptr<PlayingScreenHeader> playingScreenHeader;
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
  //an integer to synch with the header recalculations
  //if it is different than the value in playing screen header than we know
  //the header has been changed recently
  int headerRecalculated;
  //a special circular button that is used by the melee towers to reset their rally points
  unique_ptr<Button> rallyPointChange;
  //true if there's a wave happening. false otherwise
  bool waveGoingOn;

  //the upgrade system visuals
  unique_ptr<UpgradeCircle> upgradeCircle;

  sf::CircleShape radius;
  sf::RectangleShape tile;


public:
  PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,
    shared_ptr<GameLogic> gameLogic, int windowX, int windowY);
  ~PlayingScreen();
  void registerDelegates();
  void registerPersistentDelegates();
  void deregisterPersistentDelegates();
  void deregisterDelegates();
  void initDrawingMaterials();
  void initRallyPointButton();
  void initUpgradeCircle();
  void initColorShifts();
  void initColorShiftsForFloor();
  void initColorShiftsForPath();

  void handleMapGenerated(const EventInterface& event);
  void handleTowerCreation(const EventInterface& event);
  void handleTowerRemove(const EventInterface& event);
  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
  bool clickWithinRange(float mouseX, float mouseY, shared_ptr<TowerInterface> tower);
  bool clickedOnAPath(float mouseX, float mouseY);
  bool firstTimeClickOnRallyFlag(shared_ptr<TowerInterface> tower);
  void handleStateChange(const EventInterface& event);
  void handleWaveChange(const EventInterface& event);

  void draw(sf::RenderWindow& window);
  void drawFloorMap(sf::RenderWindow& window);
  void drawFloorPath(sf::RenderWindow& window, int row, int col, float yTileSize,
    float xTileSize, int pathValue, sf::RectangleShape& floorRect);
  void drawFloorTile(sf::RenderWindow& window, int row, int col, float yTileSize,
     float xTileSize, int tileValue, sf::RectangleShape& floorRect);
  void drawFloorExit(sf::RenderWindow& window, int row, int col, float yTileSize,
     float xTileSize, sf::RectangleShape& floorRect);
  void drawTowersAndObstacles(sf::RenderWindow& window);
  void drawTowerUnits(shared_ptr<TowerInterface> tower, sf::RenderWindow& window);
  void drawTowerRadius(shared_ptr<TowerInterface> tower, sf::RenderWindow& window, float xScale, float yScale, sf::Color color);
  void drawEnemyUnits(sf::RenderWindow& window);
  void drawProjectiles(sf::RenderWindow& window);

  bool wasHeaderRecalculated();

  template <class T>
  void printVector(const vector<vector<T>> &v);

  shared_ptr<PlayingScreenHeader> getHeader(){return playingScreenHeader;};

  bool isFlagButtonClicked(){return rallyPointChange->isButtonClicked();}
};
