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
    //index 0 = School, 1 = population, 2 = obstacles, 3 = waves, 4 = startMoney, 5 = cafeteriaSize
    std::vector<int> selections;
  Switcher school;
  Switcher population;
  Switcher obstacles;
  Switcher waves;
  Switcher startMoney;
  Switcher cafetriaSize;

public:
  void selectOtherSwitcher();

  void chooseNextOption();

  void draw();
};
