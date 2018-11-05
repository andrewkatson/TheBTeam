#pragma once

#include "Screen.hpp"
#include "GameLogic.hpp"

class PlayingScreen : public Screen {
private:
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //logic of the game. handles mechanics
  //use to access frequently required data (i.e. towers, obstacles, board, units)
  shared_ptr<GameLogic> gameLogic;

  //testing variable TODO remove when finished rendering
  bool somethingChanged;

public:
  PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader,shared_ptr<GameLogic> gameLogic,int windowX, int windowY);

  void registerDelegates();

  void handleTowerCreation(const EventInterface& event);
  void handleTowerRemove(const EventInterface& event);
  void draw(sf::RenderWindow& window);
  template <class T>
  void printVector(const vector<vector<T>> &v);
};
