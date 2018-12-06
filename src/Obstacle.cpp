#include "Obstacle.hpp"


Obstacle::Obstacle(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader) : TowerInterface(){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> isTower = false;
  this -> isMelee = false;
  this -> radiusVisible = false;
  this -> radius = 0;
  this -> level = -1;

}

/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void Obstacle::initSprite(){
  (this->sprite).setTexture(textures -> at(0));
  currentTexture =0;
}

void Obstacle::upgrade(){

}

void Obstacle::update(float delta){

}
