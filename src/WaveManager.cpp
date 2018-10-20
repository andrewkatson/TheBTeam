/*
  WaveManager.cpp

  Purpose: Handle production and deployment of waves within a single class.
  
  @author Jeremy Elkayam
 */
#include "WaveManager.hpp"

void WaveManager::startNextWave() {
    queue<shared_ptr<ActorInterface>> next_wave = waves.front();
    //TODO - code for spawning waves
}

void WaveManager::endCurrentWave() {
    //TODO - code to stop the wave
    waves.pop();
}

void WaveManager::spawnNextUnit() {
    shared_ptr<ActorInterface> next_unit = enemies.front();
    //TODO - spawn the unit
}

void WaveManager::update(float deltaS) {
    //TODO - implement
}