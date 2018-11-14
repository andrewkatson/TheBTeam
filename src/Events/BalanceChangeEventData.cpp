#include "Events/BalanceChangeEventData.hpp"

BalanceChangeEventData::BalanceChangeEventData(int balanceChange, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> balanceChange = balanceChange;
}
