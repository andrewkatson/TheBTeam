//
// Created by jeremy on 10/20/18.
//

#ifndef CSCI437_PROJECTILE_HPP
#define CSCI437_PROJECTILE_HPP

#include "ActorInterface.hpp"

class Projectile : public ActorInterface {

public:

  float armorPenetration;

  int damage;

  int affectedArea;

private:

  float getArmorPenetration() const;

  int getDamage() const;

  void move(float deltaS);

};


#endif //CSCI437_PROJECTILE_HPP
