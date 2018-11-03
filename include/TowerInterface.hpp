/*
  TowerInterface.hpp

  Purpose: A template to be implemented by the tower classes

  @author Andrew Katson
 */

#ifndef TOWERINTERFACE_H
#define TOWERINTERFACE_H
#include <string>
#include <memory>
#include <utility>
#include "TextLoader.hpp"

using std::string;
using std::make_shared;
using std::shared_ptr;
using std::pair;
class TowerInterface{
protected:
  //the tower type identifier that allows for its next upgrade to be pulled
  string towerTypeID;
  //the price of the tower (cost to remove in the case of an obstacle)
  int price;
  //the row in the grid this tower is located at
  int row;
  //the col in the grid this tower is located at
  int col;
  //the x coordinate on the map that the tower is located at (center of the tile on the grid it is at)
  int xCoordinate;
  //the y coordinate on the map that the tower is located at (center of the tile on the grid it is at)
  int yCoordinate;
  //the radius for the tower (if range then it is where it can fire, if melee it is where it can place a rally point)
  int radius;
public:
  virtual void upgrade()=0;
  virtual int getPrice()=0;
  virtual string getType()=0;

};

#endif
