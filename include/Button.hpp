#ifndef BUTTON_H
#define BUTTON_H
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <memory>
#include "TextLoader.hpp"

using std::cout;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
enum Position {TOPRIGHT, BOTTOMRIGHT, TOPLEFT, BOTTOMLEFT, CENTER};
class Button{
private:
  sf::Text text;
  sf::RectangleShape rect;
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
public:
  Button();
  Button(int windowX, int windowY, int order, string message,shared_ptr<TextLoader> textLoader, string fontpath);
  Button(int windowX, int windowY, Position position, string message,shared_ptr<TextLoader> textLoader, string fontpath);
  Button(int windowX, int windowY, float xPos, float yPos, string message,shared_ptr<TextLoader> textLoader, string fontpath);

  void setWindowSize(int windowX, int windowY);

  void setButtonPosition(Position position);

  void scaleButton();

  void scaleButton(float xPos, float yPos);

  bool isSelected(int mousePressX, int mousePressY);

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

};

#endif
