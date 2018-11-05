#pragma once

#include "Obstacle.hpp"

class TrashCan : public Obstacle{
public:
    TrashCan(shared_ptr<TextLoader> textLoader, string towerTypeID);
    void setProjectile(){}
    void setUpUnits(){}
};
