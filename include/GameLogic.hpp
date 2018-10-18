#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "BoardManager.hpp"
#include "GameState.hpp"

class GameLogic{
private:
  unique_ptr<BoardManager> boardManager;
  unique_ptr<GameState> state;

public:
  GameLogic();
  
  void updateGameLogic(float deltaS);
};

#endif
