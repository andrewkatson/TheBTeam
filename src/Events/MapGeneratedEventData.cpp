#include "Events/MapGeneratedEventData.hpp"

MapGeneratedEventData::MapGeneratedEventData(float timeStamp,const vector<vector<int>>& dists, const vector<int>& entrances){
  this -> timeStamp = timeStamp;
  this -> dists = dists;
  this -> entrances = entrances;
}
