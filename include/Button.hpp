#ifndef BUTTON_H
#define BUTTON_H
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>

using std::cout;
using std::string;
class Button{
private:
  sf::Text text;
  sf::RectangleShape rect;
  int windowX;
  int windowY;
  int numChars;
public:
  Button(int windowX, int windowY, string str);


  void setWindowSize(int windowX, int windowY);

  void scaleButton();

  bool isSelected(int mousePressX, int mousePressY);

  sf::RectangleShape & getButtonRect();

  sf::Text & getButtonText();

};

#endif
