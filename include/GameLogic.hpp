#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "BoardManager.hpp"

class GameLogic{
private:
  unique_ptr<BoardManager> boardManager;

public:
  GameLogic();

  void updateGameLogic(float deltaS);
};

#endif
