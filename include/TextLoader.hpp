//
// Created by jeremy on 10/26/18.
//

#ifndef CSCI437_TEXTLOADER_HPP
#define CSCI437_TEXTLOADER_HPP

#include <string>
#include <unordered_map>
#include <sstream>
#include <memory>
#include <iostream>
#include "tinyxml2.h"

using std::string;
using std::unordered_map;
using std::stringstream;
using std::cout;
using std::endl;

class TextLoader {

public:

  TextLoader();
  std::string getString(const std::string id);
  int getInteger(const std::string id);

private:
  unordered_map<string, string> strings;
  unordered_map<string, int> constants;

  void loadStrings();
  void loadConstants();
};


#endif //CSCI437_TEXTLOADER_HPP
