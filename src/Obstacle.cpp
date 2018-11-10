#include "Obstacle.hpp"


Obstacle::Obstacle(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> isMelee = false;
}

/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void Obstacle::initSprite(){
  (this->sprite).setTexture(textures -> at(0));
}

void Obstacle::upgrade(){

}

void Obstacle::update(float delta){

}
