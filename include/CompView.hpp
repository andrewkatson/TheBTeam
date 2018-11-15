#ifndef COMPVIEW_H
#define COMPVIEW_H
#include "EventManager.hpp"
#include "TextLoader.hpp"
#include "GameLogic.hpp"
#include "PlayingScreenHeader.hpp"
class CompView{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //logic of the game. handles mechanics
  shared_ptr<GameLogic> gameLogic;
  //Store the wave manager to get the current wave and information about the enemies being controlled.
  shared_ptr<WaveManager> waveManager;

  shared_ptr<PlayingScreenHeader> playingScreenHeader;

  bool coordsInsideTile(int row, int col,double x, double y);


public:
  CompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,shared_ptr<PlayingScreenHeader> playingScreenHeader);

  void updateCompView(float deltaS);

  void attackEnemies();

  void moveUnits(float deltaS);
  void delegateEvents();

};

#endif
