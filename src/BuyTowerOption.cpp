#include "BuyTowerOption.hpp"


BuyTowerOption::BuyTowerOption(shared_ptr<TextLoader> textLoader, float xPos, float yPos,
  string fontPath, shared_ptr<TowerInterface> towerToShow){
  this -> textLoader = textLoader;
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> fontPath = fontPath;
  this -> towerToShow = towerToShow;
}


/*
 * Draw the option to the screen
 * @param window: the screen to draw on
 */
void BuyTowerOption::draw(sf::RenderWindow& window){

}


/*
 * Whether the button to buy/sell has been clicked
 */
bool BuyTowerOption::isClicked(float xPos, float yPos){
  return buyOrSell -> isSelected(xPos, yPos);
}
