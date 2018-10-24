#include "Button.hpp"

Button::Button(int windowX, int windowY, int order, string str){
  (this -> text).setString(str);
  (this -> numChars) = str.length();
  (this -> rect).setFillColor(sf::Color::Transparent);
  //TODO remove outline
  (this -> rect).setOutlineColor(sf::Color::Yellow);
  (this -> rect).setOutlineThickness(1);
  this -> setWindowSize(windowX, windowY);
}

void Button::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> scaleButton();
}

void Button::scaleButton(){

  (this -> text).setPosition((this -> windowX / 3) * 2,
            (this ->  windowY - (this -> windowY / 40) * 3) * order);

  (this -> text).setCharacterSize(this -> windowX / 40);
  int xDim = (this -> windowX / 40) * this -> numChars;
  int yDim = (this -> windowX / 40) * 2.5;

  (this -> rect).setPosition((this -> windowX / 3) * 2 - 15,
            (this ->  windowY - (this -> windowY / 40) * 3 - 12) * order);
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));

}

bool Button::isSelected(int mousePressX, int mousePressY){
  sf::Vector2f rectPos = (this -> rect).getPosition();
  sf::Vector2f rectDim = (this -> rect).getSize();

  int xPos = rectPos.x;
  int yPos = rectPos.y;
  int xDim = rectDim.x;
  int yDim = rectDim.y;

  if(xPos <= mousePressX && xPos <= xPos + xDim){
    if(yPos <= mousePressY && yPos <= yPos + yDim){
      return true;
    }
  }
  return false;
}

sf::RectangleShape & Button::getButtonRect(){
  return this -> rect;
}
sf::Text & Button::getButtonText(){
  return this -> text;
}
