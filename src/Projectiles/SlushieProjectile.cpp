#include "../include/Projectiles/SlushieProjectile.hpp"

SlushieProjectile::SlushieProjectile(int hitpoint, int damage, int armor, int speed, int armorPenetration, int areaOfEffect){
  this -> hitpoints = hitpoint;
  this -> damage = damage;
  this -> armor = armor;
  this -> speed = speed;
  this -> armorPenetration = armorPenetration;
  this -> areaOfEffect = areaOfEffect;
}
