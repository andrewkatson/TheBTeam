#pragma once
/*
 * Used to draw a header across the top of the screen
 * displaying basic statistics about the player
 */
 #include "GameLogic.hpp"
 #include "Button.hpp"
class PlayingScreenHeader{
private:
  struct HeaderValue{
    int value;
    string valueLabel;
  };
  //the main font of the game
  sf::Font mainFont;
  //text object used to write with
  sf::Text text;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;
  //the button to allow us to buy a tower
  unique_ptr<Button> buyTower;
  //the button to allow us to sell a tower
  unique_ptr<Button> sellTower;
  //all the buttons in the header (not pressable)
  vector<Button> headerVariables;
  //the vector of strings that will be drawn to the screen
  //and their value
  vector<HeaderValue> allStrings;
  //the current row selected
  int rowSelected;
  //the current col selected
  int colSelected;
  //whether the header is visible or not
  bool visible;
  //the size in the y direction of the header
  float ySize;
  //the size of the window
  int windowX;
  int windowY;
public:

  PlayingScreenHeader(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic);

  void initDrawingMaterials();
  void initBuyTowerButton();
  void initSellTowerButton();
  void initHitpointsButton();
  void initBalanceButton();
  void initLevelButton();
  void initWaveButton();

  float getMaximumY();

  void registerDelegates();
  void deregisterDelegates();

  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);

  void flipVisibility();
  float getTrueXTileSize();
  float getTrueYTileSize();
  float getXOffSet();
  float getYOffSet();

  void setSelectedTile(int row, int col);

  void draw(sf::RenderWindow& window);
  void drawBuyTowerButton(sf::RenderWindow& window);
  void drawSellTowerButton(sf::RenderWindow& window);
  void drawHeaderButtons(sf::RenderWindow& window);
};
