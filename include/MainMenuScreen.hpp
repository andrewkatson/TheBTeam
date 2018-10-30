#pragma once

#include "Screen.hpp"
#include <vector>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;
class MainMenuScreen : public Screen{
private:
  int selectedItem;
  int numItems;
  vector<sf::Text> screen;
  sf::Font font;
public:
  MainMenuScreen(int windowX, int windowY, int numItems, sf::Font font);

  void draw(sf::RenderWindow& window);
  void moveUp();
  void moveDown();
};
