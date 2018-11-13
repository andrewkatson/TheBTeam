#include "Button.hpp"

Button::Button(){

}

Button::Button(int windowX, int windowY, int order, string message,shared_ptr<TextLoader> textLoader, string fontpath){
  this -> textLoader = textLoader;
  this -> fontPath = fontpath;
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
Button::Button(int windowX, int windowY, Position position, string message,shared_ptr<TextLoader> textLoader, string fontpath){
    this -> textLoader = textLoader;
    this -> fontPath = fontpath;
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

Button::Button(int windowX, int windowY, float xPos, float yPos, string message,shared_ptr<TextLoader> textLoader, string fontpath){
  this -> textLoader = textLoader;
  this -> fontPath = fontpath;
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
  sf::Font font;
  //we use this to get a proper scaling of the button
  if(font.loadFromFile(fontPath)){
    text.setFont(font);
  }

  //get the bounding box for this text
  sf::FloatRect boundingBox = (this->text).getGlobalBounds();
  //the xPosition of bounding box
  float boundingBoxXPos = boundingBox.left;
  //the yPosition of bounding box
  float boundingBoxYPos = boundingBox.top;
  //the width of the bounding box
  float boundingBoxXDim = boundingBox.width;
  //the height of the bounding box
  float boundingBoxYDim = boundingBox.height;

  //the padding used for each side of the bounding box dimensions
  //that we will use for the rectagle surrounding the button
  int padding = textLoader -> getInteger(string("IDS_Button_Position_Padding"));

  int xPos;
  int yPos;

  int distanceFromXAxis = padding;
  int distanceFromYAxis = padding + boundingBoxXDim;
  if(position == TOPRIGHT){
    xPos = windowX - distanceFromYAxis;
    yPos = 0 + distanceFromXAxis;
  }
  else if(position == BOTTOMRIGHT){
    xPos = windowX - distanceFromYAxis;
    yPos = windowY - distanceFromXAxis;
  }
  else if(position == TOPLEFT){
    xPos = 0 + padding * 2;
    yPos = 0 + distanceFromXAxis + padding/2;
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
  sf::Font font;
  //we use this to get a proper scaling of the button
  if(font.loadFromFile(fontPath)){
    text.setFont(font);
  }

  unsigned int textSize = (this ->text).getCharacterSize();

  (this -> text).setPosition((this -> windowX / 3) * 2,
            (this ->  windowY - (textSize) * 3) * order);

  //get the bounding box for this text
  sf::FloatRect boundingBox = (this->text).getGlobalBounds();
  //the xPosition of bounding box
  float boundingBoxXPos = boundingBox.left;
  //the yPosition of bounding box
  float boundingBoxYPos = boundingBox.top;
  //the width of the bounding box
  float boundingBoxXDim = boundingBox.width;
  //the height of the bounding box
  float boundingBoxYDim = boundingBox.height;
  //the padding used for each position of the bounding box dimensions
  //that we will use for the rectagle surrounding the button
  int padding = textLoader -> getInteger(string("IDS_Button_Position_Padding"));
  //the padding used for the dimensions of the rectangle
  int boundingpadding = textLoader -> getInteger(string("IDS_Button_Size_Padding"));

  (this -> rect).setPosition((int)(boundingBoxXPos)-padding, ((int)(boundingBoxYPos)-padding)* order);
  (this -> rect).setSize(sf::Vector2f((int)(boundingBoxXDim)+boundingpadding,(int)(boundingBoxYDim)+boundingpadding ));

}

void Button::scaleButton(float xPos, float yPos){
  sf::Font font;
  //we use this to get a proper scaling of the button
  if(font.loadFromFile(fontPath)){
    text.setFont(font);
  }

  unsigned int textSize = (this ->text).getCharacterSize();

  (this -> text).setPosition(xPos,
            (yPos));

  //get the bounding box for this text
  sf::FloatRect boundingBox = (this->text).getGlobalBounds();
  //the xPosition of bounding box
  float boundingBoxXPos = boundingBox.left;
  //the yPosition of bounding box
  float boundingBoxYPos = boundingBox.top;
  //the width of the bounding box
  float boundingBoxXDim = boundingBox.width;
  //the height of the bounding box
  float boundingBoxYDim = boundingBox.height;

  //the padding used for each position of the bounding box dimensions
  //that we will use for the rectagle surrounding the button
  int padding = textLoader -> getInteger(string("IDS_Button_Position_Padding"));
  //the padding used for the dimensions of the rectangle
  int boundingpadding = textLoader -> getInteger(string("IDS_Button_Size_Padding"));

  (this -> rect).setPosition((int)(boundingBoxXPos)-padding, ((int)(boundingBoxYPos)-padding));
  (this -> rect).setSize(sf::Vector2f((int)(boundingBoxXDim)+boundingpadding,(int)(boundingBoxYDim)+boundingpadding ));

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

  if(xPos <= mousePressX && mousePressX <= xPos + xDim){
    if(yPos <= mousePressY && mousePressY <= yPos + yDim){
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
 * Set a new string for the button
 */
void Button::setString(string newString){
  (this->text).setString(newString);
  this->numChars = newString.length();
}

/*
 * Set the font for the current text
 */
void Button::setFont(string fontPath){
  this ->  fontPath = fontPath;
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
