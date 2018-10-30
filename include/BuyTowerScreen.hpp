#pragma once

#include "Screen.hpp"

class BuyTowerScreen : public Screen {
public:
  BuyTowerScreen(int windowX, int windowY);

  void draw(sf::RenderWindow& window);
};
