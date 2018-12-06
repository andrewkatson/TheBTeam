#include "Events/MapGeneratedEventData.hpp"

MapGeneratedEventData::MapGeneratedEventData(float timeStamp,const vector<vector<int>>& dists, const vector<int>& entrances, vector<vector<std::unordered_set<int>>>combinedPaths){
  this -> timeStamp = timeStamp;
  this -> dists = dists;
  this -> entrances = entrances;
  this -> combinedPaths = combinedPaths;
}
