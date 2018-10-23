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
#include "EventManager.hpp"

class GameLogic{
private:
  //Store the game's instance of the BoardManager class that the game logic
  //needs for generation and playing of game boards.
  unique_ptr<BoardManager> boardManager;
  //Store the instance of the GameState class that the logic needs to remember
  //and modify the game's current state.
  unique_ptr<GameState> gameState;
  //Store the instance of the TowerManager class that the logic needs to
  //interact with the defensive towers
  unique_ptr<TowerManager> towerManager;
  //Store the Event Manger for the game that receives and distributes irregular
  //game events
  shared_ptr<EventManager> eventManager;

public:
  /*
    Constructor. Initialize game, setting up instance variables.
   */
  GameLogic();

  /*
    Called once every game loop. Updates the game's happenings according to the
    time since the last loop.

    @param deltaS The amount of time in seconds since the last loop began
                  execution.
   */
  void updateGameLogic(float deltaS);
};

#endif
