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
#include <map>
#include "EventManager.hpp"
#include "ActorInterface.hpp"
#include "TextLoader.hpp"
#include "Units/AverageKidUnit.hpp"
#include "Units/SkinnyKidUnit.hpp"
#include "Units/FatKidUnit.hpp"

class WaveManager{

private:
  //int pair (used to assocaite a row and col)
  typedef pair<int,int> intPair;

  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textureLoader to get the textures for this tower and pass to
  //any dependent units or projectiles
  shared_ptr<TextureLoader> textureLoader;

  //Vector storing every enemy type that can be spawned.
  vector<shared_ptr<MeleeUnit>> enemies;

  /*
   * A queue storing every enemy in the current wave.
   */
  queue<shared_ptr<MeleeUnit>> currentWave;

  /*
   * A map storing the enemy units from the current wave that have been spawned
   * key: the unique id of the unit [its memory address]
   */
  unordered_map<int,shared_ptr<MeleeUnit>> spawnedCurrentWave;

  //The current level the user is at in the game.
  //TODO - pull this from gamelogic
  int level;

  //The number of waves in the current level.
  unsigned int numWaves;

  unsigned int currentWaveNumber;

  //A random device to pull from
  std::random_device rd;

  //A 2D vector storing the distances from exit for each square in the board
  vector<vector<int>> distances;

  //A vector storing the coordinates of each entry point in the board's path
  vector<int> entryPositions;

  map<int,vector<intPair>>distancesFromEntryPositions;

  /*
   *
   * @return a wave filled with enemies according to the specifications in the class (level, wave number)
   */
  queue<shared_ptr<MeleeUnit>> makeWave(int difficulty, int waveNumber);

  /*
   * Create and return a vector listing the distance from exit for every entry point in the entrypoints
   * vector.
   */
  void buildDistanceEntryMap(vector<int>& entrypoints, vector<vector<int>>& distances);

  /*
   * Normalize the distances in z based on their distance from the maximum distance value.
   * E.g. for a vector { 3, 6, 2, 4, 1 }; the maximum is 5, therefore the vector would be
   * converted to { 3, 0, 4, 2, 5 }.
   */
  map<int,vector<intPair>> getNormalizedDistanceMap(map<int,vector<intPair>>& distancesFromEntryPositions);

public:
  /*
   * Constructor for the WaveManager class. Sets up enemies that can be spawned
   * as well as waves to be spawned.
   */
  WaveManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<TextureLoader> textureLoader);

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

  void delegateMethod(const EventInterface& event);

  /*
   * Set the distance from exit for each path space on the current board. Should be set
   * with data pulled from BoardManager.
   *
   * SHOULD BE CALLED WHENEVER A NEW BOARD IS GENERATED.
   */
  void setDistances(vector<vector<int>>& dists);

  /*
   * Set the entry points of the current board's path. Again, this needs to be set using
   * BoardManager data.
   *
   * SHOULD BE CALLED WHENEVER A NEW BOARD IS GENERATED.
   */
  void setEntryPoints(vector<int>& entries);

  /*
   * @return the enemies that have been spawned in the current wave
   */
  unordered_map<int,shared_ptr<MeleeUnit>>& getSpawnedEnemyUnits();
};

#endif
