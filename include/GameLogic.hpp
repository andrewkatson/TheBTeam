/*
  GameLogic.hpp

  Purpose: Handle all logical processes for Food Fight.

  @author Andrew Katson, Jeremy Elkayam
 */

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "BoardManager.hpp"
#include "GameState.hpp"
#include "TowerManager.hpp"
#include "Player.hpp"
#include "SoundManager.hpp"
#include "WaveManager.hpp"
#include "ProjectileManager.hpp"
#include "EventManager.hpp"
#include "Events/KeyPressEvent.hpp"
#include "Events/MousePressEvent.hpp"
#include "Events/StateChangeEvent.hpp"
#include "Events/MapGeneratedEvent.hpp"
#include "Events/ProjectileExplosionEvent.hpp"
#include "Events/ActorDestroyedEvent.hpp"
#include "EventType.hpp"
#include "Projectile.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using std::addressof;
class GameLogic{
private:
  //int pair (used to assocaite a row and col)
  typedef pair<int,int> intPair;
  //x dimension of the render window
  int windowX;
  //y dimension of the render window
  int windowY;
  //x dimension in pixels of a grid space
  float gridX;
  //y dimension in pixels of a grid space
  float gridY;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //Store the game's instance of the BoardManager class that the game logic
  //needs for generation and playing of game boards.
  unique_ptr<BoardManager> boardManager;
  //Store the instance of the GameState class that the logic needs to remember
  //and modify the game's current state.
  unique_ptr<GameState> gameState;
  //Store the instance of the TowerManager class that the logic needs to
  //interact with the defensive towers
  unique_ptr<TowerManager> towerManager;
  //Store the human player's statistics
  unique_ptr<Player> player;
  //Store any sounds/music used by the game and play/stop when necessary
  unique_ptr<SoundManager> soundManager;
  //Store the waves of ai enemies to be spawned and handle where/when each wave starts
  shared_ptr<WaveManager> waveManager;
  //Store the projectiles that can be fired by the defensive towers and handle their
  //creation, path, and destruction
  unique_ptr<ProjectileManager> projectileManager;
  //Store the Event Manger for the game that receives and distributes irregular
  //game events
  shared_ptr<EventManager> eventManager;
  //Store the textureLoader to get the textures for this tower and pass to
  //any dependent units or projectiles
  shared_ptr<TextureLoader> textureLoader;

  shared_ptr<b2World> world;

  int test;
  long long fryID;
  long long fryID1;



public:
  /*
    Constructor. Initialize game, setting up instance variables.
   */
  GameLogic(shared_ptr<TextLoader> textLoader, int windowX, int windowY, shared_ptr<TextureLoader> textureLoader,shared_ptr<b2World> world);
  ~GameLogic();



  void registerEvents();
  void registerDelegates();
  void deregisterDelegates();

  void handleKeyPress(const EventInterface& event);
  void handleMousePress(const EventInterface& event);
  void handleStateChange(const EventInterface& event);
  void handleProjectileExplosion(const EventInterface& event);
  /*
    Called once every game loop. Updates the game's happenings according to the
    time since the last loop.

    @param deltaS The amount of time in seconds since the last loop began
                  execution.
   */
  void updateGameLogic(float deltaS);

  void makeNewMap();
  void placeObstacles();

  shared_ptr<EventManager> getEventManager();

  vector<shared_ptr<TowerInterface>>& allUpgradesForTower(int row, int col);
  void modifyToIncludeUpgrades(vector<shared_ptr<TowerInterface>>& towerUpgrades, shared_ptr<TowerInterface> tower);

  bool attemptPurchaseTower(int row, int col, string towerTypeID);
  bool attemptSellTower(int row, int col);

  bool canBuy(int row, int col);
  bool canBuy(string towerType);
  void createATower(int row, int col, string towerType);
  void createATowerMoney(string towerType);
  void removeATower(int row, int col);
  void removeATowerMoney(int row, int col);
  void removeAObstacleMoney(int row, int col);

  int getUpgradePrice(int row, int col);

  State getGameState();

  void shutDown();

  const vector<vector<int>>& getFloor();
  const vector<vector<int>>& getAboveFloor();
  const vector<vector<int>>& getDistances();

  bool isTower(int row, int col);
  bool isObstacle(int row, int col);
  bool isEmptySpace(int row, int col);
  bool isExit(int row, int col);
  bool isPath(int row, int col);

  const float getTileXSize();
  const float getTileYSize();
  const int getRows();
  const int getCols();
  const int getWindowY();
  const int getWindowX();

  Player& getPlayer();

  const MapChoices& getMapCustomizationChoices();

  const shared_ptr<TowerInterface> getTowerPlaced(int row, int col);
  const unordered_map<int, shared_ptr<TowerInterface>>& getTowersPlaced();
  const unordered_map<long long,shared_ptr<MeleeUnit>>& getSpawnedEnemyUnits();
  unordered_map<long long, shared_ptr<ActorInterface>>& getFiredProjectiles();
  shared_ptr<WaveManager> getWaveManager(){return waveManager;};

};

#endif
