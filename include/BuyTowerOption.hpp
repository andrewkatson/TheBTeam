#pragma once
#include <memory>
#include "Button.hpp"
#include "TowerInterface.hpp"
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
  //holds the texture for this tower
  sf::Texture towerTexture;
  //the button with the price of the tower
  unique_ptr<Button> buyOrSell;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //the x position on the screen
  float xPos;
  //the y position on the screen
  float yPos;
  //the path for the font for the button
  string fontPath;
  //the tower we are going to represent here
  shared_ptr<TowerInterface> towerToShow;

public:

  BuyTowerOption(shared_ptr<TextLoader> textLoader, float xPos, float yPos,
    string fontPath, shared_ptr<TowerInterface> towerToShow);


  void draw(sf::RenderWindow& window);

  bool isClicked(float xPos, float yPos);
};
