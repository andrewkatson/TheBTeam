#pragma once
/*
 * Loads in the vector of options for each selectable option in the OptionsMEnuScreen similar
 * to how the texture laoder goes about it.
 *
 */
#include "SFML/Graphics.hpp"
#include<string>
#include<vector>
#include<iostream>
#include "TextLoader.hpp"

using std::to_string;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::vector;
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
