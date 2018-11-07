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
#include "../include/Events/TowerCreationEvent.hpp"
#include "../include/Events/TowerRemoveEvent.hpp"

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
  virtual void draw(sf::RenderWindow &window)=0;
  virtual void registerDelegates()=0;
  virtual void deregisterDelegates()=0;

};
