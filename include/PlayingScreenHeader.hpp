#pragma once
/*
 * Used to draw a header across the top of the screen
 * displaying basic statistics about the player
 */
 #include "GameLogic.hpp"
 #include "Button.hpp"
 #include "Events/LoseHitpointsEvent.hpp"
 #include "Events/WaveChangeEvent.hpp"
 #include "Events/LevelChangeEvent.hpp"
 #include "Events/BalanceChangeEvent.hpp"
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
  vector<shared_ptr<Button>> headerVariables;
  //all the values for each button
  vector<int> headerVariableValues;
  //the vector of strings that will be drawn to the screen
  //and their value
  vector<shared_ptr<HeaderValue>> allStrings;
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
  //true when a button is made visible or invisible (will cause an auto recalculation of the header size)
  bool recaculateHeader;
  //a counter for the number of times the header has been recalculated (used to synch with screen)
  int timesHeaderRecalculated;
  //block clicks
  bool blockClicks;
public:

  PlayingScreenHeader(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic);
  ~PlayingScreenHeader();


  void initDrawingMaterials();
  void initBuyTowerButton();
  void initSellTowerButton();
  void initHitpointsButton();
  void initBalanceButton();
  void initLevelButton();
  void initWaveButton();

  void resetButtons();
  void resetHitpointButton();
  void resetBalanceButton();
  void resetLevelButton();
  void resetWaveButton();

  float getMaximumY();
  //return the wave number as stored in the header variable
  int getWaveNumber(){return headerVariableValues.at(3);}

  void registerDelegates();
  void registerPersistentDelegates();
  void deregisterPersistentDelegates();
  void deregisterDelegates();

  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
  void handleLoseHitpoints(const EventInterface& event);
  void handleBalanceChange(const EventInterface& event);
  void handleLevelChange(const EventInterface& event);
  void handleWaveChange(const EventInterface& event);
  void handleRestartGame(const EventInterface& event);

  void softReset();

  void flipVisibility();
  float getTrueXTileSize();
  float getTrueYTileSize();
  float getXOffSet();
  float getYOffSet();
  bool headerRecalculated();
  int getHeaderRecalculatedTimes(){return timesHeaderRecalculated;}

  void setSelectedTile(int row, int col);

  void draw(sf::RenderWindow& window);
  void drawBuyTowerButton(sf::RenderWindow& window);
  void drawSellTowerButton(sf::RenderWindow& window);
  void drawHeaderButtons(sf::RenderWindow& window);

  /*
   * flip whether clicks are going to be checked for
   */
  void flipClickCheck(){blockClicks = blockClicks==true ? false : true;}
   /*
    * whether clicks are being checked for
    */
  bool clicksCheckedFor(){return !blockClicks;}

  template <class T>
  void printVector(const vector<vector<T>> &v);
};
