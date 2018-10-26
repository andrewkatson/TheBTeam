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
#include "../include/Events/KeyPressEvent.hpp"
#include "EventType.hpp"
#include <functional>

using namespace std::placeholders;
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
  //Store the human player's statistics
  unique_ptr<Player> player;
  //Store any sounds/music used by the game and play/stop when necessary
  unique_ptr<SoundManager> soundManager;
  //Store the waves of ai enemies to be spawned and handle where/when each wave starts
  unique_ptr<WaveManager> waveManager;
  //Store the projectiles that can be fired by the defensive towers and handle their
  //creation, path, and destruction
  unique_ptr<ProjectileManager> projectileManager;
  //Store the Event Manger for the game that receives and distributes irregular
  //game events
  shared_ptr<EventManager> eventManager;

public:
  /*
    Constructor. Initialize game, setting up instance variables.
   */
  GameLogic();

  void registerDelegates();

  void handleKeyPress(const EventInterface& event);

  /*
    Called once every game loop. Updates the game's happenings according to the
    time since the last loop.

    @param deltaS The amount of time in seconds since the last loop began
                  execution.
   */
  void updateGameLogic(float deltaS);

  shared_ptr<EventManager> getEventManager();

  void shutDown();
};

#endif
