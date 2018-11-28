#ifndef BUTTON_H
#define BUTTON_H
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <assert.h>
#include "TextLoader.hpp"
#include "TextureLoader.hpp"

using std::cout;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
enum Position {TOPRIGHT, BOTTOMRIGHT, TOPLEFT, BOTTOMLEFT, CENTER};
class Button{
private:
  sf::Text text;
  sf::RectangleShape rect;
  sf::CircleShape circle;
  //to load the font when drawing the box
  string fontPath;
  int windowX;
  int windowY;
  //the number of characters in the message for this button
  int order;
  int numChars;
  bool isVisible;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Store the textureLoader to make requests for textures
  shared_ptr<TextureLoader> textureLoader;
  //texture path for the texture of the button
  string texturepath;
  //texture used if the button has a texture instead of a color
  sf::Texture texture;
  //whether the button uses the circle or the rectangle shape
  bool isCircle;
  //whether the button is "clicked" meaning that it has been clicked
  //the button must still be visible but could be unclicked and invisible
  bool isClicked;
  //if we are using a certain scale that does not depend on an item of text we use these values
  float xScale = 1.0;
  float yScale = 1.0;

public:
  Button();
  Button(int windowX, int windowY, int order, string message,shared_ptr<TextLoader> textLoader, string fontpath, bool isCircle=false);
  Button(int windowX, int windowY, Position position, string message,shared_ptr<TextLoader> textLoader, string fontpath, bool isCircle=false);
  Button(int windowX, int windowY, float xPos, float yPos, string message,shared_ptr<TextLoader> textLoader, string fontpath, bool isCircle=false);
  Button(int windowX, int windowY, float xPos, float yPos, shared_ptr<TextLoader> textLoader, string texturepath, bool isCircle=false);

  void setWindowSize(int windowX, int windowY);

  void setButtonPosition(Position position);
  void setButtonPosition(float xPos, float yPos);

  void scaleButton();

  void scaleButton(float xPos, float yPos);

  void setButtonScale(float xScale, float yScale);

  void initTexture();

  void clickButton();

  bool isSelected(int mousePressX, int mousePressY);
  bool isButtonClicked();

  bool isCurrentlyVisible();

  void flipVisibility();

  void setString(string newString);
  void setFont(string fontPath);

  void setFillColor(int redComponent, int blueComponent, int greenComponent, int alpha=255);
  void setOutlineColor(int redComponent, int blueComponent, int greenComponent, int alpha=255);
  void setOutlineThickness(float thickness);
  void setTextFillColor(int redComponent, int blueComponent, int greenComponent, int alpha=255);
  void setTextOutlineColor(int redComponent, int blueComponent, int greenComponent, int alpha=255);
  void setTextOutlineThickness(float thickness);
  void setTextSize(int textSize);

  sf::RectangleShape & getButtonRect();

  sf::Text & getButtonText();

  sf::CircleShape& getButtonCircle();

  void setCircleRadius(float radius);
  void setOrigin(float originX, float originY);

  void draw(sf::RenderWindow& window);

};

#endif
