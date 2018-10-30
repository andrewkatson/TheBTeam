#pragma once

#include "Screen.hpp"

class RestartScreen : public Screen {
public:
  RestartScreen(int windowX, int windowY);

  void draw(sf::RenderWindow& window);
};
