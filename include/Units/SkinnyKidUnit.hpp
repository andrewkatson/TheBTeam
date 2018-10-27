//
// Created by jeremy on 10/26/18.
//

#ifndef CSCI437_SKINNYKIDUNIT_HPP
#define CSCI437_SKINNYKIDUNIT_HPP

#include "MeleeUnit.hpp"

class SkinnyKidUnit : public MeleeUnit {
public:
  SkinnyKidUnit(int hitpoint, int damage, int armor, int speed, int armorPenetration);
};


#endif //CSCI437_SKINNYKIDUNIT_HPP
