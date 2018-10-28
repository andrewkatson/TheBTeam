/*
  RangeTower.hpp

  Purpose: A defensive tower that fires missiles at enemy npc actors

  @author Andrew Katson
 */

 #ifndef RANGETOWER_H
 #define RANGETOWER_H
#include "TowerInterface.hpp"
#include "Projectile.hpp"
#include "TextLoader.hpp"
#include <memory>

using std::shared_ptr;
class RangeTower : public TowerInterface{
protected:
//the specific type of tower this rangetower is
shared_ptr<RangeTower> currentTower;
//the specfic type of projectile shot by this tower
shared_ptr<Projectile> currentProjectile;
//Store the textLoader to make requests for strings and constants
shared_ptr<TextLoader> textLoader;
//the rate that this tower can fire projectiles at
int rateOfFire;
public:
  RangeTower();
  RangeTower(shared_ptr<RangeTower> startingTower);

  virtual void upgrade();

  /*
   * set the currentProjectile to be the projectile object of the type of the tower
   * this projectile will be fired from
   */
  virtual void setProjectile();

  /*
   * @return the price of the tower
   */
  int getPrice();

};

 #endif