//
// Created by jeremy on 10/26/18.
//

#include "TextLoader.hpp"

TextLoader::TextLoader(){
  //doc.LoadFile( "../values/strings.xml" );
  //fill the strings map
  loadStrings();

  //doc.LoadFile( "../values/constants.xml" );
  //fill the constants map
  loadConstants();
}

/*
 * Load in the strings by the id
 */
void TextLoader::loadStrings(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../values/strings.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("strings");

  for(tinyxml2::XMLElement* node = root->FirstChildElement("string"); node != NULL; node= node->NextSiblingElement("string")) {
    string s(node->Attribute("id"));
    strings.insert({s, node -> Attribute("value")});

  }
}

/*
 * Load in the constants by the id
 */
void TextLoader::loadConstants(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../values/constants.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("constants");

  int intValue;

  for(tinyxml2::XMLElement* node = root->FirstChildElement("constant"); node != NULL; node= node->NextSiblingElement("constant")) {
    string s(node->Attribute("id"));
    stringstream strValue;
    //converting the string value from xml to an int
    strValue << node -> Attribute("value");
    strValue >> intValue;
    constants.insert({s, intValue});
    intValue = 0;
  }
}

std::string TextLoader::getString(const std::string id){
  if(strings.find(id) != strings.end()){
    return strings.at(id);
  }
  return "String not found";
}

int TextLoader::getConstant(const std::string id){
  if(constants.find(id) != constants.end()){
    return constants.at(id);
  }
  return -1;
}
