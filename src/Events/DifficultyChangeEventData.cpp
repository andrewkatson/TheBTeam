//
// Created by jeremyelkayam on 11/28/18.
//

#include "Events/DifficultyChangeEventData.hpp"

DifficultyChangeEventData::DifficultyChangeEventData(int difficulty, float timeStamp){
  this -> timeStamp = timeStamp;
  this -> difficulty = difficulty;
}
