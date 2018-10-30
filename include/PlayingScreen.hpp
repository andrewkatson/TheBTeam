#pragma once

#include "Screen.hpp"

class PlayingScreen : public Screen {
private:

public:
  PlayingScreen(int windowX, int windowY);


  void draw(sf::RenderWindow& window);
};
