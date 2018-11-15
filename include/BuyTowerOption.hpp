#pragma once
#include <memory>
#include "Button.hpp"
#include "TowerInterface.hpp"
#include <assert.h>
/*
 * Container class to hold a  pictoral representation of a tower and
 * the cost underneath it. As well as a button to allow a buy/sell
 * @author Andrew Katson
 */

using std::unique_ptr;
class  BuyTowerOption{
private:
  //rectangle to hold the texture representing the tower
  sf::RectangleShape towerPictureRect;
  //rectangle used to outline the option and the choice
  sf::RectangleShape backgroundRect;
  //holds the texture for this tower
  sf::Texture towerTexture;
  //the button with the price of the tower
  unique_ptr<Button> buyOrSell;
  //buttons to store the primary statistics of the tower
  //used in the event we are buying a tower
  vector<shared_ptr<Button>> statisticsButtons;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //used to load in fonts
  sf::Font mainFont;
  //used to draw text
  sf::Text text;
  //the x position on the screen
  float xPos;
  //the y position on the screen
  float yPos;
  //the x size of the option tile
  float xSize;
  //the y size of the option tile
  float ySize;
  //the path for the font for the button
  string fontPath;
  //whether we show the statistics or not
  bool showStats;
  //the window size in the x dimension
  int windowX;
  //the window size in the y dimension
  int windowY;
  //whether we are buying or not
  bool areBuying;
  //the tower we are going to represent here
  shared_ptr<TowerInterface> towerToShow;

public:

  BuyTowerOption(shared_ptr<TextLoader> textLoader, float xPos, float yPos,
    float xSize, float ySize, string fontPath, shared_ptr<TowerInterface> towerToShow,
    bool showStats, int windowX, int windowY, bool areBuying);

  void initDrawingMaterials();
  void initPictureRectangle();
  void initChooseButton();
  void initStatisticsButtons();
  void initBackgroundRectangle();

  void draw(sf::RenderWindow& window);
  void drawPurchaseButton(sf::RenderWindow& window);
  void drawStatisticsButtons(sf::RenderWindow& window);

  bool isClicked(float xPos, float yPos);

  void indicateStatDifferential(int indexOfStat, int differential);
  void realignStatButtons();
};
