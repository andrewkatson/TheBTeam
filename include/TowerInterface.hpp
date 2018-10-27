/*
  TowerInterface.hpp

  Purpose: A template to be implemented by the tower classes

  @author Andrew Katson
 */

#ifndef TOWERINTERFACE_H
#define TOWERINTERFACE_H
#include <string>
#include <memory>

using std::string;
using std::make_shared;
class TowerInterface{
protected:
  //the tower type identifier that allows for its next upgrade to be pulled
  string towerTypeID;
public:
  virtual void upgrade()=0;

};

#endif
