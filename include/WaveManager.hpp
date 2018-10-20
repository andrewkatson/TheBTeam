/*
  WaveManager.hpp

  Purpose: Handle production and deployment of waves within a single class.
  
  @author Jeremy Elkayam
 */
#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

using namespace std;

#include <memory>
#include <queue>
#include "ActorInterface.hpp"

class WaveManager{

private:
  queue<shared_ptr<ActorInterface>> enemies;
  queue<queue<shared_ptr<ActorInterface>>> waves;
  
public:
  queue<shared_ptr<ActorInterface>> getNextWave(){return waves.front();}

  queue<queue<shared_ptr<ActorInterface>>> getWaves(){return waves;}

  void startNextWave();

  void spawnNextUnit();

  void endCurrentWave();

  void update(float deltaS);
};

#endif
