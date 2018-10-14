#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include "MapFactory.hpp"

class GameLogic{
private:
  unique_ptr<MapFactory> mapFactory;

public:
  GameLogic();

  void updateGameLogic(float deltaS);
};

#endif
