#pragma once

#include <string>
#include "EventDataInterface.hpp"

class BalanceChangeEventData : public EventDataInterface{
public:
  int balanceChange;
  float timeStamp;

  BalanceChangeEventData(int balanceChange, float timeStamp);
};
