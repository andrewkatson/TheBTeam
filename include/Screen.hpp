#pragma once

#include "SFML/Graphics.hpp"
#inlcude<string>
#include<iostream>
#include <memory>
#include <functional>

using std::out;
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
  int getSelectedItem() {return selectedItem:}
}
