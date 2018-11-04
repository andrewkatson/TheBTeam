/*
  TowerManager.hpp

  Purpose: Manage the defensive tower units on the map

  @author Andrew Katson
 */

#ifndef TOWERMANAGER_H
#define TOWERMANAGER_H
#include "TowerInterface.hpp"
#include "TextLoader.hpp"
#include "../include/Towers/CheesePizza.hpp"
#include "../include/Towers/CrinkleFry.hpp"
#include "../include/Towers/DeepDish.hpp"
#include "../include/Towers/EnergyDrink.hpp"
#include "../include/Towers/Gravy.hpp"
#include "../include/Towers/MeatLovers.hpp"
#include "../include/Towers/MiniMMS.hpp"
#include "../include/Towers/NormalFry.hpp"
#include "../include/Towers/NormalMMS.hpp"
#include "../include/Towers/PeanutButterMMS.hpp"
#include "../include/Towers/PeanutMMS.hpp"
#include "../include/Towers/PepperoniPizza.hpp"
#include "../include/Towers/Slushie.hpp"
#include "../include/Towers/Soda.hpp"
#include "../include/Towers/SpicyFry.hpp"
#include "../include/Towers/WaffleFry.hpp"
#include "../include/Towers/NotATower.hpp"
#include "../include/Obstacles/CafeteriaTable.hpp"
#include "../include/Obstacles/TrashCan.hpp"
#include "EventManager.hpp"
#include "../include/Events/TowerCreationEvent.hpp"
#include "../include/Events/TowerRemoveEvent.hpp"
#include <vector>
#include <unordered_map>
#include <functional>
#include <assert.h>

using namespace std::placeholders;

using std::vector;
using std::unordered_map;
using std::dynamic_pointer_cast;
class TowerManager{
//Store the textLoader to make requests for strings and constants
shared_ptr<TextLoader> textLoader;
//event manager (used to register, deregister from events, and create them)
shared_ptr<EventManager> eventManager;

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
//int pair (used to assocaite a row and col)
typedef pair<int,int> intPair;

public:
  TowerManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);

  void setDimensions(int xDim, int yDim);

  int getTowerPrice(int row, int col);
  int getTowerPrice(string towerTypeID);

  unordered_map<string, vector<shared_ptr<TowerInterface>>>& getAllTowersToChoose();
  vector<shared_ptr<TowerInterface>>& getUpgradesForTower(string towerTypeID);

  unordered_map<int, shared_ptr<TowerInterface>>& getTowersPlaced();

  shared_ptr<TowerInterface> getTowerPlaced(int combinedRowCol);
  shared_ptr<TowerInterface> getTowerPlaced(int row, int col);

  vector<shared_ptr<TowerInterface>>& getObstacleAsVector(int row, int col);
  shared_ptr<TowerInterface> getObstacle(int row, int col);

  void handleTowerCreation(const EventInterface& event);
  void handleTowerRemove(const EventInterface& event);

  void addObstacles(unordered_map<int, intPair>& allObstaclesToPlace);
private:
  void registerDelegates();

  void populateTowersToChoose();
  void populateObstacles();
  void populateTowerUpgrades();
  void populateTowerUpgradesLvl1(int maxMeleeUnits);
  void populateTowerUpgradesLvl2(int maxMeleeUnits);
  void populateTowerUpgradesLvl3(int maxMeleeUnits);

  void addTower(string type, int combinedRowCol);
  void addTower(string type, int row, int col);

  shared_ptr<TowerInterface> copyOfTowerType(string type);
  void removeTower(int combinedRowCol);
  void removeTower(int row, int col);

  void upgradeTower(int combinedRowCol);
  void upgradeTower(int row, int col);
};
#endif
