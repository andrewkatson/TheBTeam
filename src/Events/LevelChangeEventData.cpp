#include "Events/LevelChangeEventData.hpp"

LevelChangeEventData::LevelChangeEventData(int level, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> level = level;
}
