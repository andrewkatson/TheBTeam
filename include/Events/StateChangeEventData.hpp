#pragma once

#include <string>
#include "EventDataInterface.hpp"
#include "GameState.hpp"

using std::string;
class StateChangeEventData : public EventDataInterface{
public:
  State state;
  float timeStamp;
  //used when the next state needs to know what the current row, col selected is
  int row;
  int col;
  //true if we are buying (buy/upgrade tower or buy an obstacle)
  //false when we are selling a tower 
  bool buy;

  StateChangeEventData(State state, float timeStamp);
  StateChangeEventData(State state, int row, int col, bool buy, float timeStamp);
};
