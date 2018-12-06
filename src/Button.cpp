#include "Button.hpp"

Button::Button(){

}

Button::Button(int windowX, int windowY, int order, string message,
  shared_ptr<TextLoader> textLoader, string fontpath, bool isCircle, string buttonID){
  this -> textLoader = textLoader;
  this -> fontPath = fontpath;
  (this -> text).setString(message);
  (this -> numChars) = message.length();
  (this -> rect).setFillColor(sf::Color::Transparent);
  //TODO remove outline
  (this -> rect).setOutlineColor(sf::Color::Yellow);
  (this -> rect).setOutlineThickness(1);
  this -> isVisible= true;
  this -> isClicked = false;
  this -> isCircle = isCircle;
  this -> buttonID = buttonID;
  (this -> text).setCharacterSize(this -> windowX / 40);
  this -> setWindowSize(windowX, windowY);
  this -> scaleButton();
}
Button::Button(int windowX, int windowY, Position position, string message,
  shared_ptr<TextLoader> textLoader, string fontpath, bool isCircle, string buttonID){
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
    this -> isClicked = false;
    this -> isCircle = isCircle;
    this -> buttonID = buttonID;
    this -> setButtonPosition(position);
}

Button::Button(int windowX, int windowY, float xPos, float yPos, string message,
  shared_ptr<TextLoader> textLoader, string fontpath, bool isCircle, string buttonID){
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
  this -> isClicked = false;
  this -> order = 0;
  this -> isCircle = isCircle;
  this -> buttonID = buttonID;
  this -> xPos = xPos;
  this -> yPos = yPos;
  this -> scaleButton(xPos, yPos);
}

Button::Button(int windowX, int windowY, float xPos, float yPos, shared_ptr<TextLoader> textLoader,
   string texturepath, bool isCircle, string buttonID){
  this -> textLoader = textLoader;
  this -> texturepath = texturepath;
  this -> setWindowSize(windowX, windowY);
  this -> isVisible= true;
  this -> isClicked = false;
  this -> order = 0;
  this -> isCircle = isCircle;
  this -> initTexture();
  this -> numChars = 0;
  this -> buttonID = buttonID;
  this -> xPos = xPos;
  this -> yPos = yPos;
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
    xPos = windowX - boundingBoxXDim - padding;
    yPos = windowY - boundingBoxYDim - padding;
  }
  else if(position == CENTER){
    xPos = (windowX - distanceFromYAxis)/2;
    yPos = (windowY - distanceFromXAxis)/2;
  }
  this -> xPos = xPos;
  this -> yPos = yPos;
  scaleButton(xPos, yPos);
}

/*
 * Set the x and y coordinates of the position
 * @param xPos: the new x coordinate
 * @param yPos: the new y coordinate
 */
void Button::setButtonPosition(float xPos, float yPos){
  if(isCircle){
    circle.setPosition(sf::Vector2f(xPos, yPos));
  }
  else{
    rect.setPosition(sf::Vector2f(xPos, yPos));
  }
  //if there is text then we need to scale the button
  if(numChars){
    text.setPosition(sf::Vector2f(xPos, yPos));
    scaleButton(xPos, yPos);
  }
  this -> xPos = xPos;
  this -> yPos = yPos;
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
  this -> xPos = xPos;
  this -> yPos = yPos;
}

/*
 * Set the scale of the button (different from scaleButton which assumes there is text to scale around)
 */
void Button::setButtonScale(float xScale, float yScale){
  assert(!numChars);
  this -> xScale = xScale;
  this -> yScale = yScale;
  //we do no check for text because this button assumes no text
  if(isCircle){
    circle.setScale(xScale, yScale);
  }
  else{
    rect.setScale(xScale, yScale);
  }
}

/*
 * Loads in the texture if there is one
 */
void Button::initTexture(){
  if(!texture.loadFromFile(texturepath)){
    assert(true == false);
  }
  if(isCircle){
    circle.setTexture(&texture);
  }
  else{
    rect.setTexture(&texture);
  }
}

bool Button::isSelected(int mousePressX, int mousePressY){
  //if the button is not visible always return false
  if(!isVisible){
    return false;
  }


  sf::Vector2f pos;
  sf::Vector2f dim;
  float xDim;
  float yDim;

  if(isCircle){
    pos = (this -> circle).getPosition();
    float radius = (this -> circle).getRadius();
    xDim = radius *xScale;
    yDim = radius *yScale;
  }
  else{
    pos = (this -> rect).getPosition();
    dim = (this -> rect).getSize();
    xDim = dim.x *xScale;
    yDim = dim.y *yScale;
  }

  float xPos = pos.x;
  float yPos = pos.y;

  //need to check differently if we are dealing with a circle (i.e. in all directions since the positon is a center not the top left corner)
  if(isCircle){
    if(xPos - xDim <= mousePressX && mousePressX <= xPos + xDim){
      if(yPos - yDim <= mousePressY && mousePressY <= yPos + yDim){
        return true;
      }
    }
  }
  else{
    if(xPos <= mousePressX && mousePressX <= xPos + xDim){
      if(yPos <= mousePressY && mousePressY <= yPos + yDim){
        return true;
      }
    }
  }

  return false;
}

/*
 * Set the button's clicked status to the opposite of what it currently is
 */
void Button::clickButton(){
  isClicked = isClicked == true ? false : true;
}

/*
 * @return true if the button is clicked on (as in it was just clicked)
 */
bool Button::isButtonClicked(){
  return isClicked;
}

sf::RectangleShape & Button::getButtonRect(){
  return this -> rect;
}
sf::Text & Button::getButtonText(){
  return this -> text;
}
sf::CircleShape& Button::getButtonCircle(){
  return this -> circle;
}

/*
 * Set the radius of the circle
 */
void Button::setCircleRadius(float radius){
  circle.setRadius(radius);
}

/*
 * Set the shape
 */
void Button::setOrigin(float originX, float originY){
  if(isCircle){
    circle.setOrigin(originX, originY);
  }
  else{
    rect.setOrigin(originX, originY);
  }
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
  if(!isVisible){
    isClicked = false;
  }
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

  if(isCircle){
    (this->circle).setFillColor(color);
  }
  else{
    (this -> rect).setFillColor(color);
  }
}

/*
 * Set the outline color
 */
void Button::setOutlineColor(int redComponent, int blueComponent, int greenComponent, int alpha){
  sf::Color color (redComponent, blueComponent, greenComponent, alpha);
  if(isCircle){
    (this->circle).setOutlineColor(color);
  }
  else{
    (this -> rect).setOutlineColor(color);
  }
}

/*
 * Set the thickness for the outline
 */
void Button::setOutlineThickness(float thickness){
  if(isCircle){
    (this->circle).setOutlineThickness(thickness);
  }
  else{
    (this->rect).setOutlineThickness(thickness);
  }
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

/*
 * draw the button onto the window
 */
void Button::draw(sf::RenderWindow& window){

  //draw the circle shape if this is a circle
  if(isCircle){
    window.draw(circle);
  }
  else{
    window.draw(rect);
  }
  string textString = text.getString();

  //draw the text if it has a message
  //has issues and may not show the text sometimes
  if(textString.length()){
    sf::Font mainFont;
    if(!mainFont.loadFromFile(fontPath)){
      //cout << "No font!" << endl;
    }
    else{
    //  //cout << "loaded font!" << endl;
    }

    (this->text).setFont(mainFont);
    window.draw(this -> text);
  }
}

/*
 * Whether this button has been mirrored over the x or y axis
 */
bool Button::isMirrored(){
  return isMirroredX() || isMirroredY();
}

bool Button::isMirroredX(){
  return mirroredAcrossX;
}

bool Button::isMirroredY(){
  return mirroredAcrossY;
}

void Button::mirrorOverX(int windowX){
  float dimensionInX;
  if(isCircle){
    dimensionInX = circle.getRadius();
  }
  else{
    dimensionInX = rect.getSize().x;
  }
  //how we mirror depends on which side of the middle of the window we are on
  if(windowX / 2 > xPos){
    this -> xPos = windowX - this->xPos - dimensionInX;
  }
  else{
    this -> xPos = windowX - this->xPos - dimensionInX;
  }
  mirroredAcrossX = !mirroredAcrossX;
  scaleButton(xPos, yPos);
}

void Button::mirrorOverY(int windowY){
  float dimensionInY;
  if(isCircle){
    dimensionInY = circle.getRadius();
  }
  else{
    dimensionInY = rect.getSize().y;
  }
  //how we mirror depends on which side of the middle of the window we are on
  if(windowY / 2 > yPos){
    this -> yPos = windowY - this->yPos - dimensionInY;
  }
  else{
    this -> yPos = windowY - this->yPos - dimensionInY;
  }

  mirroredAcrossY = !mirroredAcrossY;
  scaleButton(xPos, yPos);
}
