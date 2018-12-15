/*
 * The visual circle drawn around a tower that will show icons for what can be upgraded
 * as well as how much it will cost
 * @author Andrew Katson
 */

#pragma once

#include "GameLogic.hpp"
#include "EventManager.hpp"
#include "TextLoader.hpp"
#include "Button.hpp"
#include "Events/MousePressEvent.hpp"
#include <memory>
#include <functional>
#include <chrono>
#include <math.h>

using std::shared_ptr;
using std::unique_ptr;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;
using namespace std::placeholders;
class UpgradeCircle{
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;


  //the mouse object
  sf::Mouse mouse;
  //circle shape used to draw all buttons on
  sf::CircleShape circleToDraw;

  //holds all the button ids for melee towers
  vector<string> meleeTowerButtonIDS;
  //holds all the button ids for the range towers
  vector<string> rangeTowerButtonIDS;
  //holds all the melee tower upgrade icon paths
  vector<string> meleeTowerButtonIconPaths;
  //holds all the range tower upgrade icon paths
  vector<string> rangeTowerButtonIconPaths;

  //the button that displays the price of an upgrade
  unique_ptr<Button> upgradePriceButton;

  //all buttons used for the melee towers
  vector<shared_ptr<Button>> meleeTowerUpgradeButtons;
  //all buttons used for the range towers
  vector<shared_ptr<Button>> rangeTowerUpgradeButtons;

  //whether we are displaying this or not
  bool isDisplayed;

  //size of render window
  int windowX;
  int windowY;

  //row and col selected
  int rowSelected;
  int colSelected;

  //string that serves as the base for upgrade price button
  string upgradePriceBaseString;
  //the string for the addition to the base before the price is added (i.e. "Armor Penetration" when we say "Upgrade Armor Penetration 6")
  string upgradePriceAdditionString;
public:

  UpgradeCircle(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,
    shared_ptr<GameLogic> gameLogic, int windowX, int windowY);

  ~UpgradeCircle();

  void registerDelegates();
  void deregisterDelegates();

  void handleMousePress(const EventInterface& event);

  string checkMeleeTowerUpgradeButtons(float mouseX, float mouseY);
  string checkRangeTowerUpgradeButtons(float mouseX, float mouseY);

  void initButtonIDs();
  void initButtonIDsMeleeTower();
  void initButtonIDsRangeTower();

  void initButtonIcons();
  void initButtonIconPathsMeleeTower();
  void initButtonIconPathsRangeTower();


  void initDrawingMaterials();

  void initTowerUpgradeButtons();
  void initMeleeTowerUpgradeButtons();
  void initRangeTowerUpgradeButtons();
  void initUpgradePriceButton();
  void initCircleToDraw();

  void draw(sf::RenderWindow& window);
  void checkMousePosAndDisplayUpgrade(shared_ptr<TowerInterface> tower,sf::RenderWindow& window);
  void checkMousePosAndDisplayMeleeUpgrade(shared_ptr<TowerInterface> tower,sf::RenderWindow& window);
  void checkMousePosAndDisplayRangeUpgrade(shared_ptr<TowerInterface> tower,sf::RenderWindow& window);
  void drawMeleeTowerButtons(shared_ptr<TowerInterface> tower, sf::RenderWindow& window);
  void drawRangeTowerButtons(shared_ptr<TowerInterface> tower, sf::RenderWindow& window);
  void drawUpgradePriceButton(sf::RenderWindow& window);
  void drawCircleToDraw(sf::RenderWindow& window);

  bool isCurrentlyVisible(){return isDisplayed;}


  void handleLevelChanged(const EventInterface& event);
};
