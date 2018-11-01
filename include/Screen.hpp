#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <chrono>
#include "TextLoader.hpp"
#include "EventManager.hpp"
#include "GameState.hpp"
#include "GameLogic.hpp"
#include "../include/Events/KeyPressEvent.hpp"
#include "../include/Events/MousePressEvent.hpp"
#include "../include/Events/StateChangeEvent.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
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
