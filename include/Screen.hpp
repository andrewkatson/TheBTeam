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
#include "Events/KeyPressEvent.hpp"
#include "Events/MousePressEvent.hpp"
#include "Events/StateChangeEvent.hpp"
#include "Events/TowerCreationEvent.hpp"
#include "Events/TowerRemoveEvent.hpp"
#include "Events/MapGeneratedEvent.hpp"
#include "Events/OptionSelectedEvent.hpp"
#include "Events/RestartGameEvent.hpp"

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
