#pragma once

#include "SFML/Graphics.hpp"
#include<string>
#include<iostream>

using std::cout;
using std::string;
class Switcher{
private:
  int id;
  std::vector<int> v;
  int len;

public:
  void changeSelected();
  void getSelected();
  void getID();
  void draw();
};
