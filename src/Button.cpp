#include "Button.hpp"

Button::Button(){

}

Button::Button(int windowX, int windowY, int order, string message,shared_ptr<TextLoader> textLoader){

  (this -> text).setString(message);
  (this -> numChars) = message.length();
  (this -> rect).setFillColor(sf::Color::Transparent);
  //TODO remove outline
  (this -> rect).setOutlineColor(sf::Color::Yellow);
  (this -> rect).setOutlineThickness(1);
  this -> isVisible= true;

  (this -> text).setCharacterSize(this -> windowX / 40);
  this -> setWindowSize(windowX, windowY);
  this -> scaleButton();
}
Button::Button(int windowX, int windowY, Position position, string message,shared_ptr<TextLoader> textLoader){
    this -> setWindowSize(windowX, windowY);
    (this -> text).setString(message);
    (this -> numChars) = message.length();
    (this -> text).setCharacterSize(this -> windowX / 40);
    (this -> rect).setFillColor(sf::Color::Transparent);
    //TODO remove outline
    (this -> rect).setOutlineColor(sf::Color::Yellow);
    (this -> rect).setOutlineThickness(1);
    this -> isVisible= true;
    this -> setButtonPosition(position);
}

Button::Button(int windowX, int windowY, float xPos, float yPos, string message,shared_ptr<TextLoader> textLoader){
  this -> setWindowSize(windowX, windowY);
  (this -> text).setString(message);
  (this -> numChars) = message.length();
  (this -> text).setCharacterSize(this -> windowX / 40);
  (this -> rect).setFillColor(sf::Color::Transparent);
  //TODO remove outline
  (this -> rect).setOutlineColor(sf::Color::Yellow);
  (this -> rect).setOutlineThickness(1);
  this -> isVisible= true;
  this -> order = 0;
  this -> scaleButton(xPos, yPos);
}

void Button::setWindowSize(int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
}

/*
 * Take the passed string and set the position to a predetermined place on the board
 *@param position: the string identifier for the position
 */
void Button::setButtonPosition(Position position){

  int xPos;
  int yPos;

  unsigned int characterSize = (this->text).getCharacterSize();
  int distanceFromXAxis = characterSize;
  int distanceFromYAxis = numChars * characterSize;
  if(position == TOPRIGHT){
    xPos = windowX - distanceFromYAxis;
    yPos = 0 + distanceFromXAxis;
  }
  else if(position == BOTTOMRIGHT){
    xPos = windowX - distanceFromYAxis;
    yPos = windowY - distanceFromXAxis;
  }
  else if(position == TOPLEFT){
    xPos = 0 + distanceFromYAxis;
    yPos = 0 + distanceFromXAxis;
  }
  else if(position == BOTTOMLEFT){
    xPos = 0 + distanceFromYAxis;
    yPos = windowY - distanceFromXAxis;
  }
  else if(position == CENTER){
    xPos = (windowX - distanceFromYAxis)/2;
    yPos = (windowY - distanceFromXAxis)/2;
  }
  scaleButton(xPos, yPos);
}

void Button::scaleButton(){
  unsigned int textSize = (this ->text).getCharacterSize();

  (this -> text).setPosition((this -> windowX / 3) * 2,
            (this ->  windowY - (textSize) * 3) * order);
  int xDim = (textSize) * this -> numChars;
  int yDim = (textSize) * 2.5;

  (this -> rect).setPosition((this -> windowX / 3) * 2 - 25,
            (this ->  windowY - (textSize) * 3 - 12) * order);
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));

}

void Button::scaleButton(float xPos, float yPos){

  unsigned int textSize = (this ->text).getCharacterSize();

  (this -> text).setPosition(xPos,
            (yPos));
  int xDim = (textSize) * this -> numChars;
  int yDim = (textSize) * 2.5;

  (this -> rect).setPosition(xPos - 25,
            (yPos - 12));
  (this -> rect).setSize(sf::Vector2f(xDim, yDim));
}

bool Button::isSelected(int mousePressX, int mousePressY){
  //if the button is not visible always return false
  if(!isVisible){
    return false;
  }
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

/*
 * @return bool: whether the button is visible
 */
bool Button::isCurrentlyVisible(){
  return isVisible;
}

/*
 * Change the button from its current visibility status
 */
void Button::flipVisibility(){
  isVisible = isVisible == true ? false : true;
}

/*
 * Set the fill color
 */
void Button::setFillColor(int redComponent, int blueComponent, int greenComponent, int alpha){
  sf::Color color (redComponent, blueComponent, greenComponent, alpha);
  (this -> rect).setFillColor(color);
}

/*
 * Set the outline color
 */
void Button::setOutlineColor(int redComponent, int blueComponent, int greenComponent, int alpha){
  sf::Color color (redComponent, blueComponent, greenComponent, alpha);
  (this -> rect).setOutlineColor(color);
}

/*
 * Set the thickness for the outline
 */
void Button::setOutlineThickness(float thickness){
  (this->rect).setOutlineThickness(thickness);
}

/*
 * Set the button text color
 */
void Button::setTextFillColor(int redComponent, int blueComponent, int greenComponent, int alpha){
  sf::Color color (redComponent, blueComponent, greenComponent, alpha);
  (this -> text).setFillColor(color);
}

/*
 * Set the outline text
 */
void Button::setTextOutlineColor(int redComponent, int blueComponent, int greenComponent, int alpha){
  sf::Color color (redComponent, blueComponent, greenComponent, alpha);
  (this -> text).setOutlineColor(color);
}

/*
 * Set the thickness for the outline of the text
 */
void Button::setTextOutlineThickness(float thickness){
  (this->text).setOutlineThickness(thickness);
}

/*
 * Set the size of the text
 */
void Button::setTextSize(int textSize){
  (this->text).setCharacterSize(textSize);
}
