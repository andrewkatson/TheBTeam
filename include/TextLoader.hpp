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
#include <assert.h>
#include "tinyxml2.h"
#include <vector>

using std::string;
using std::unordered_map;
using std::stringstream;
using std::cout;
using std::endl;
using std::vector;

class TextLoader {

public:

  TextLoader();
  std::string getString(const std::string id);
  std::string getTypeID(const std::string id);
  int getInteger(const std::string id);
  double getDouble(const std::string id);

  unordered_map<string, string>& getAllTypeIDS();
  vector<string> getAllHints();

private:
  unordered_map<string, string> strings;
  unordered_map<string, string> typeids;
  unordered_map<string, int> ints;
  unordered_map<string, double> doubles;
  vector<string> hints;

  void loadStrings();
  void loadTypeIDS();
  void loadInts();
  void loadDoubles();
  void loadHints();
};


#endif //CSCI437_TEXTLOADER_HPP
