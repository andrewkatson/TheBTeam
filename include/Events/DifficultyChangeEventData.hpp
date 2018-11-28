//
// Created by jeremyelkayam on 11/28/18.
//

#ifndef CSCI437_DIFFICULTYCHANGEEVENTDATA_HPP
#define CSCI437_DIFFICULTYCHANGEEVENTDATA_HPP

#include "EventDataInterface.hpp"

class DifficultyChangeEventData : public EventDataInterface {
public:
  int difficulty;
  float timeStamp;
  DifficultyChangeEventData(int difficulty, float timeStamp);
};


#endif //CSCI437_DIFFICULTYCHANGEEVENTDATA_HPP
