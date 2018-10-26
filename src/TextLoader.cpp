//
// Created by jeremy on 10/26/18.
//

#include "TextLoader.hpp"


std::string TextLoader::getText(const char* id){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../values/strings.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("strings");

  //TODO - is there a better way to do this than iteration?

  for(tinyxml2::XMLElement* node = root->FirstChildElement("string"); node != NULL; node= node->NextSiblingElement("wave_manager")) {
    if (node->Attribute("id", id)) {
      return node->Attribute("value");
    }
  }

  return "String not found";
}
