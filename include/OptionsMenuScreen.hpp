#pragma once
#include "Screen.hpp"
#include <vector>

using std::vector;

class OptionsMenu : public Screen {
private:
  int numItems;
  int selectedItem;
  vector<sf::Text> screen;
  sf::Font font;
public:

  OptionsMenu(int windowX, int windowY, int numItems, sf::Font font);

  void moveUp();
  void moveDown();
  void draw(sf::RenderWindow &window);
  int getSelectedItem() {return selectedItem;}
};
