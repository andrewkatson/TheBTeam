//
// Created by jeremy on 10/26/18.
//

#include "TextLoader.hpp"

TextLoader::TextLoader(){
  //doc.LoadFile( "../values/strings.xml" );
  //fill the strings map
  loadStrings();
  loadTypeIDS();

  //doc.LoadFile( "../values/constants.xml" );
  //fill the constants map
  loadInts();
  loadDoubles();
}

/*
 * Load in the strings by the id
 */
void TextLoader::loadStrings(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../resources/values/strings.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("strings");

  for(tinyxml2::XMLElement* node = root->FirstChildElement("string"); node != NULL; node= node->NextSiblingElement("string")) {
    string s(node->Attribute("id"));
    strings.insert({s, node -> Attribute("value")});

  }
}

/*
 * Load in the class typeids by their id
 */
void TextLoader::loadTypeIDS(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../resources/values/strings.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("typeids");

  for(tinyxml2::XMLElement* node = root->FirstChildElement("typeid"); node != NULL; node= node->NextSiblingElement("typeid")) {
    string s(node->Attribute("id"));
    typeids.insert({s, node -> Attribute("value")});
  }
}

/*
 * Load in the constants by the id
 */
void TextLoader::loadInts(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../resources/values/constants.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("constants")->FirstChildElement("ints");
  int intValue;

  for(tinyxml2::XMLElement* node = root->FirstChildElement("constant"); node != NULL; node= node->NextSiblingElement("constant")) {
    string s(node->Attribute("id"));
    stringstream strValue;
    //converting the string value from xml to an int
    strValue << node -> Attribute("value");
    strValue >> intValue;
    ints.insert({s, intValue});

  }
}

/*
 * Load in the double constants by the id
 */
void TextLoader::loadDoubles(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../resources/values/constants.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("constants")->FirstChildElement("floats");

  double doubleValue;

  for(tinyxml2::XMLElement* node = root->FirstChildElement("constant"); node != NULL; node= node->NextSiblingElement("constant")) {
    string s(node->Attribute("id"));
    stringstream strValue;
    //converting the string value from xml to an double
    strValue << node -> Attribute("value");
    strValue >> doubleValue;

    doubles.insert({s, doubleValue});

  }
}

std::string TextLoader::getString(const std::string id){
  if(strings.find(id) != strings.end()){
    return strings.at(id);
  }
  return "String not found";
}

std::string TextLoader::getTypeID(const std::string id){
  if(typeids.find(id) != typeids.end()){
    return typeids.at(id);
  }
  return "TypeID not found";
}

int TextLoader::getInteger(const std::string id){
  if(ints.find(id) != ints.end()){
    return ints.at(id);
  }
  return -1;
}


double TextLoader::getDouble(const std::string id){
  if(doubles.find(id) != doubles.end()){
    return doubles.at(id);
  }
  return -1.0;
}

/*
 * @return a reference to the unordered_map with all the typeids in it
 */
unordered_map<string, string>& TextLoader::getAllTypeIDS(){
  return typeids;
}
