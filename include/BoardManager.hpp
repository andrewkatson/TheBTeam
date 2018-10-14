#ifndef BOARDMANAGER_H
#define BOARDMANAGER_H
#include "MapFactory.hpp"

class BoardManager{
private:
    unique_ptr<MapFactory> mapFactory;
public:
  BoardManager();
};
#endif
