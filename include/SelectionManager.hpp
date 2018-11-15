#pragma once

#include "SFML/Graphics.hpp"
#include "Screen.hpp"
#include "Switcher.hpp"
#include <string>
#include <iostream>

using std::cout;
using std::unique_ptr;

class SelectionManager{
private:
  Switcher school;
  Switcher population;
  Switcher obstacles;
  Switcher waves;
  Switcher startMoney;
  Switcher cafetriaSize;
  Switcher pathLength;
public:
  void selectOtherSwitcher();

  void chooseNextOption();

  void draw();
};
