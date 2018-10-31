#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include "TextLoader.hpp"
#include "EventManager.hpp"
#include "../include/Events/KeyPressEvent.hpp"
#include "../include/Events/MousePressEvent.hpp"

using std::cout;
using std::string;
using std::shared_ptr;
using namespace std::placeholders;
class Screen{
protected:
  int windowX;
  int windowY;
public:
  Screen();

  virtual void draw(sf::RenderWindow &window)=0;

};
