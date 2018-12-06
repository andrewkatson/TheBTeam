#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "EventDataInterface.hpp"

using std::string;
using std::vector;

class MapGeneratedEventData : public EventDataInterface{
public:
  float timeStamp;
  vector<vector<int>>dists;
  vector<int> entrances;
  vector<vector<std::unordered_set<int>>> combinedPaths;

  MapGeneratedEventData(float timeStamp,const vector<vector<int>>& dists,const vector<int>& entrances, vector<vector<std::unordered_set<int>>>combinedPaths);

};
