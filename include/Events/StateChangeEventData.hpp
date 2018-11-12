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

  StateChangeEventData(State state, float timeStamp);
  StateChangeEventData(State state, int row, int col, float timeStamp);
};
