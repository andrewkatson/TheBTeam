/*
  TowerManager.hpp

  Purpose: Manage the defensive tower units on the map

  @author Andrew Katson
 */

#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H
#include "TowerInterface.hpp"
#include "TextLoader.hpp"
#include "TextureLoader.hpp"
#include "Towers/CheesePizza.hpp"
#include "Towers/CrinkleFry.hpp"
#include "Towers/DeepDish.hpp"
#include "Towers/EnergyDrink.hpp"
#include "Towers/Gravy.hpp"
#include "Towers/MeatLovers.hpp"
#include "Towers/MiniMMS.hpp"
#include "Towers/NormalFry.hpp"
#include "Towers/NormalMMS.hpp"
#include "Towers/PeanutButterMMS.hpp"
#include "Towers/PeanutMMS.hpp"
#include "Towers/PepperoniPizza.hpp"
#include "Towers/Slushie.hpp"
#include "Towers/Soda.hpp"
#include "Towers/SpicyFry.hpp"
#include "Towers/WaffleFry.hpp"
#include "Towers/NotATower.hpp"
#include "Obstacles/CafeteriaTable.hpp"
#include "Obstacles/TrashCan.hpp"
#include "EventManager.hpp"
#include "Events/TowerCreationEvent.hpp"
#include "Events/TowerRemoveEvent.hpp"
#include <Box2D/Box2D.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <assert.h>
#include <random>

using namespace std::placeholders;

using std::vector;
using std::unordered_map;
using std::dynamic_pointer_cast;
using std::cerr;
class TowerManager{
//Store the textLoader to make requests for strings and constants
shared_ptr<TextLoader> textLoader;
//event manager (used to register, deregister from events, and create them)
shared_ptr<EventManager> eventManager;
//Store the textureLoader to get the textures for this tower and pass to
//any dependent units or projectiles
shared_ptr<TextureLoader> textureLoader;

//map of every tower that can be used to copy a tower type once
//it is created
unordered_map<string, shared_ptr<TowerInterface>> allTowerTypes;

//All possible upgrades for each type of tower (basic towers all share the "IDS_NT" key)
//which indicates that a tile with nothing can be any base type
unordered_map<string, vector<shared_ptr<TowerInterface>>> allTowerUpgrades;

//Towers placed on the board (and obstacles)
//the integer key is the row*collength + colindex of the tower on the map
unordered_map<int, shared_ptr<TowerInterface>> towersPlaced;

//xdim of map (cols)
int xDim;
//ydim of map(rows)
int yDim;

//x dimension in pixels of a grid space
int xGrid;
//y dimension in pixels of a grid space
int yGrid;
//handles all collisions
shared_ptr<b2World> world;

//random number generator (seeded in the constructor)
std::mt19937 mt;

//int pair (used to assocaite a row and col)
typedef pair<int,int> intPair;

public:
  TowerManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<TextureLoader> textureLoader, shared_ptr<b2World> world);
  ~TowerManager();

  void setDimensions(int xDim, int yDim);
  void setGridDimensions(int xGrid, int yGrid);

  int getTowerPrice(int row, int col);
  int getTowerPrice(string towerTypeID);
  int getUpgradePrice(int row, int col);

  unordered_map<string, vector<shared_ptr<TowerInterface>>>& getAllTowersToChoose();
  shared_ptr<TowerInterface> getGenericTower(string towerTypeID);

  vector<shared_ptr<TowerInterface>>& getUpgradesForTower(string towerTypeID);

  unordered_map<int, shared_ptr<TowerInterface>>& getTowersPlaced();

  shared_ptr<TowerInterface> getTowerPlaced(int combinedRowCol);
  shared_ptr<TowerInterface> getTowerPlaced(int row, int col);

  vector<shared_ptr<TowerInterface>>& getObstacleAsVector(int row, int col);
  shared_ptr<TowerInterface> getObstacle(int row, int col);

  void handleTowerCreation(const EventInterface& event);
  void handleTowerRemove(const EventInterface& event);

  void addObstacles(unordered_map<int, intPair>& allObstaclesToPlace);

  void upgradeTower(string upgradeButtonID, int row, int col);

private:
  void registerDelegates();
  void deregisterDelegates();

  void populateTowersToChoose();
  void populateObstacles();
  void populateTowerUpgrades();
  void populateTowerUpgradesLvl1(int maxMeleeUnits);
  void populateTowerUpgradesLvl2(int maxMeleeUnits);
  void populateTowerUpgradesLvl3(int maxMeleeUnits);

  void addTower(string type, int combinedRowCol);
  void addTower(string type, int row, int col);

  void modifyToIncludeUpgrades(shared_ptr<TowerInterface> towerToUpgrade, shared_ptr<TowerInterface> tower);

  shared_ptr<TowerInterface> copyOfTowerType(string type, int row, int col);

  void removeTower(int combinedRowCol);
  void removeTower(int row, int col);

  void upgradeMeleeTower(string upgradeButtonID, shared_ptr<TowerInterface> towerToUpgrade);
  void upgradeRangeTower(string upgradeButtonID, shared_ptr<TowerInterface> towerToUpgrade);
};
#endif
