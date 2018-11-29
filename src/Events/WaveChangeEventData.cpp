#include "Events/WaveChangeEventData.hpp"

WaveChangeEventData::WaveChangeEventData(int waveNum, float timeStamp,bool waveStart){
  this -> timeStamp = timeStamp;
  this -> waveNum = waveNum;
  this -> waveStart = waveStart;

}
