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
#include "EventManager.hpp"
#include "../include/Events/TowerCreationEvent.hpp"
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std::placeholders;

using std::vector;
using std::unordered_map;

class TowerManager{
//Store the textLoader to make requests for strings and constants
shared_ptr<TextLoader> textLoader;
//event manager (used to register, deregister from events, and create them)
shared_ptr<EventManager> eventManager;

//All possible towers that can be purchased
vector<shared_ptr<TowerInterface>> towersToChoose;

//All possible upgrades for each type of tower
unordered_map<string, vector<shared_ptr<TowerInterface>>> possibleUpgrades;

//Towers placed on the board
//the integer key is the row*collength + colindex of the tower on the map
unordered_map<int, shared_ptr<TowerInterface>> towersPlaced;

//xdim of map (cols)
int xDim;

//ydim of map(rows)
int yDim;

public:
  TowerManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, int yDim ,int xDim);

  int getTowerPrice(int row, int col);

  vector<shared_ptr<TowerInterface>>& getTowersToChoose();

  unordered_map<int, shared_ptr<TowerInterface>>& getTowersPlaced();

  shared_ptr<TowerInterface> getTowerPlaced(int combinedRowCol);
  shared_ptr<TowerInterface> getTowerPlaced(int row, int col);

private:
  void populateTowersToChoose();
  void populateTowerUpgrades();
  void populateTowerUpgradesLvl1(int maxMeleeUnits);
  void populateTowerUpgradesLvl2(int maxMeleeUnits);


  void addTower(int type, int combinedRowCol);
  void addTower(int type, int row, int col);

  void removeTower(int combinedRowCol);
  void removeTower(int row, int col);

  void upgradeTower(int combinedRowCol);
  void upgradeTower(int row, int col);
};
#endif
