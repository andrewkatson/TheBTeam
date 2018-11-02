/*
 * WaveManager.hpp
 *
 * Purpose: Handle production and deployment of waves within a single class.
 *
 * @author Jeremy Elkayam
 */
#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

using namespace std;

#include <memory>
#include <queue>
#include <random>
#include "EventManager.hpp"
#include "ActorInterface.hpp"
#include "TextLoader.hpp"
#include "../include/Units/AverageKidUnit.hpp"
#include "../include/Units/SkinnyKidUnit.hpp"
#include "../include/Units/FatKidUnit.hpp"

class WaveManager{

private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;

  //Vector storing every enemy type that can be spawned.
  vector<shared_ptr<MeleeUnit>> enemies;

  /*
   * A queue storing all the waves to be generated by the manager.
   * Each wave is represented by a queue storing the enemies to be generated
   * within the wave.
   */
  queue<queue<shared_ptr<MeleeUnit>>> waves;

  //The current level the user is at in the game.
  //TODO - pull this from gamelogic
  int level;

  //The number of waves in the current level.
  int numWaves;

  //A random device to pull from
  std::random_device rd;

  /*
   *
   * @return a wave filled with enemies according to the specifications in the class (level)
   */
  queue<shared_ptr<MeleeUnit>> makeWave(int difficulty, int waveNumber);

public:
  /*
   * Constructor for the WaveManager class. Sets up enemies that can be spawned
   * as well as waves to be spawned.
   */
  WaveManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);

  /*
   * Setup the possible enemies that can spawn
   */
  void setUpPossibleEnemies();

  /*
   * Return the next wave in waves.
   *
   * @return the wave at the front of the wave queue.
   */
  queue<shared_ptr<MeleeUnit>> getNextWave();


  /*
   * Return the queue storing all waves
   *
   * @return a queue with all of the waves to be spawned by the WaveManager
   */
  queue<queue<shared_ptr<MeleeUnit>>> getWaves();

  /*
   * Begin spawning enemies in the top wave of the queue.
   */
  void startNextWave();

  /*
   * Spawn the next enemy in the top wave of the wave queue.
   */
  void spawnNextUnit();

  /*
   * Stop spawning enemies in the wave and remove it from the queue.
   */
  void endCurrentWave();

  /*
   * Called once every game loop.  Update all aspects of the manager
   * [does WaveManager need to update its actors or does something else do that?]
   */
  void update(float deltaS);

  /*
   * Populate the wave vector with a number of waves according to level.
   */
  void setupWaves(int difficulty);
};

#endif
