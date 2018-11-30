#pragma once

#include <string>
#include <vector>
#include "EventDataInterface.hpp"

using std::string;
using std::vector;

class MapGeneratedEventData : public EventDataInterface{
public:
  float timeStamp;
  vector<vector<int>>dists;
  vector<int> entrances;

  MapGeneratedEventData(float timeStamp,const vector<vector<int>>& dists,const vector<int>& entrances);
};
