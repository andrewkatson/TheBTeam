#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::string;

class Screen{
private:
  int windowX;
  int windowY;
  int numItems;
  int selectedItem;
public:
  Screen(int windowX, int windowY, int numItems);
  void moveUp();
  void moveDown();
  void delegateEvents();
  void draw(sf::RenderWindow &window);
  int getSelectedItem() {return selectedItem;}
};
