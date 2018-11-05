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

//int pair (used to assocaite a row and col)
typedef pair<int,int> intPair;
//the specfic type of projectile shot by this tower
shared_ptr<Projectile> currentProjectile;
//Store the textLoader to make requests for strings and constants
shared_ptr<TextLoader> textLoader;
//the rate that this tower can fire projectiles at
int rateOfFire;
public:
  RangeTower();
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

  string getType(){return towerTypeID;}
  void setPos(intPair pos){row = pos.first; col=pos.second;}
  void setPos(int row, int col) {this->row=row; this->col=col;}

  void setUpUnits(){}
};

 #endif
