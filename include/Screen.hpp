#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::string;

class Screen{
protected:
  int windowX;
  int windowY;
public:
  Screen();

  virtual void draw(sf::RenderWindow &window)=0;

};
