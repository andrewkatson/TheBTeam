#pragma once

/*
 * Detects all collisions and alerts the respective colliding parties
 * @author Andrew Katson
 */

#include "EventManager.hpp"
#include "TextLoader.hpp"
#include "WaveManager.hpp"
#include "ProjectileManager.hpp"
#include "TowerInterface.hpp"
#include "Events/TowerCreationEvent.hpp"
#include "Events/TowerRemoveEvent.hpp"
#include "Events/ActorCreatedEvent.hpp"
#include "Events/ActorDestroyedEvent.hpp"

class CollisionManager{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Store the Event Manger for the game that receives and distributes irregular
  //game events
  shared_ptr<EventManager> eventManager;
  //Store the waves of ai enemies to be spawned and handle where/when each wave starts
  shared_ptr<WaveManager> waveManager;
  //Store the projectiles that can be fired by the defensive towers and handle their
  //creation, path, and destruction
  shared_ptr<ProjectileManager> projectileManager;

  //all towers keyed by a row, col pair they belong in (uses their radius to determine where)
  unordered_map<int, unordered_map<long long, shared_ptr<TowerInterface>>> towersPlaced;
  //all projectiles keyed by their id (so they can be grabbed when they explode quickly
  unordered_map<long long, shared_ptr<ActorInterface>> projectilesFired;
  //all allied units keyed by a row, col they belong in
  unordered_map<int, unordered_map<long long, shared_ptr<ActorInterface>>> alliedUnits;
  //all enemy units keyed by a row, col they belong in
  unordered_map<int, unordered_map<long long, shared_ptr<ActorInterface>>> enemyUnits;

  //the size of tiles in x dimension
  float xTileSize;
  //the size of tiles in y dimension
  float yTileSize;
  //the number of rows
  int rows;
  //the number of cols
  int cols;

public:

  CollisionManager(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager,
    shared_ptr<WaveManager> waveManager,
    shared_ptr<ProjectileManager> projectileManager);

  ~CollisionManager();

  void setGridDimensions(float x, float y);
  void setDimensions(int rows, int cols);

  void registerDelegates();

  void deregisterDelegates();

  void handleTowerCreation(const EventInterface& event);
  void handleTowerRemove(const EventInterface& event);
  void handleActorCreated(const EventInterface& event);
  void handleActorDestroyed(const EventInterface& event);

  void addNewTower(shared_ptr<TowerInterface> tower);
  void removeOldTower(shared_ptr<TowerInterface> tower);

  void checkForCollisions();
  void updateAllUnitPositions();
  void updateAllAllyUnitPositions();
  void updateAllEnemyUnitPositions();

  bool inMap(int row, int col);
  bool inMap(float x, float y);

};
