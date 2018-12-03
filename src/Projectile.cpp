//
// Created by jeremy on 10/20/18.
//

#include "Projectile.hpp"

Projectile::Projectile(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader) : ActorInterface(){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> isProjectile = true;
  this -> isAlly = true;
}

/*
 * Initliaze the texture for the sprite to be the first texture of the textures vector
 */
void Projectile::initSprite(){
  (this->sprite).setTexture(textures -> at(current_sprite));
}


void Projectile::setToCenter(){
  sf::FloatRect boundsOfSprite = sprite.getLocalBounds();
  sprite.setOrigin(boundsOfSprite.left + (boundsOfSprite.width)/2.0,
  boundsOfSprite.top + (boundsOfSprite.height)/2.0);
}

int Projectile::getArmorPenetration() const {
  return armorPenetration;
}

int Projectile::getDamage() const {
  return damage;
}

void Projectile::move(float delta){
  float newX = xVector /(1/speed) *delta + x;
  float newY = yVector / (1/speed) *delta + y;

  //we check to see if the projectile has overshot the target
  if(xVector > 0 ){
    if(newX > xTarget - e){
      newX = xTarget;
    }
  }
  else{
    if(newX < xTarget + e){
      newX = xTarget;
    }
  }

  if(yVector > 0){
    if(newY > yTarget - e){
      newY = yTarget;
    }
  }
  else{
    if(newY < yTarget + e){
      newY = yTarget;
    }
  }

  x = newX;
  y = newY;

  //update the body
  body -> SetTransform(b2Vec2(x,y), body->GetAngle());
}

void Projectile::setVector(float x, float y){
  this -> xVector = x;
  this -> yVector = y;
}

void Projectile::setVectorScale(float xScale, float yScale){
  this -> xVectorScale = xScale;
  this -> yVectorScale = yScale;
}

void Projectile::setTargetPos(float xPos, float yPos){
  this -> xTarget = xPos;
  this -> yTarget = yPos;
}

void Projectile::setProjectileID(int ID){
  this -> projectileID = ID;
}

void Projectile::update(float delta){
  //check if the projectile has hit its target
  if(hasHitTarget()){
    //deal with it being destroyed
    handleTargetHit();
  }
  //otherwise move it closer
  else{
    move(delta);
  }
}

bool Projectile::hasHitTarget(){
  if(this -> xTarget - e <= this -> x && this -> xTarget + e >= this -> x){
    if(this -> yTarget - e <= this -> y && this -> yTarget + e >= this -> y){
      return true;
    }
  }
  return false;
}

void Projectile::handleTargetHit(){
  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();

  //make event
  shared_ptr<EventInterface> projectileHit = make_shared<ProjectileExplosionEvent>(this -> getID(), nowInNano);

  this -> eventManager -> queueEvent(projectileHit);
}

void Projectile::setFixtures(){
  b2CircleShape circleShape;
  circleShape.m_p.Set(0,0);
  float scale = max(xScale, yScale);
  circleShape.m_radius = radius * scale;

  b2FixtureDef circleFixtureDef;
  circleFixtureDef.shape = &circleShape; //this is a pointer to the shape above
  fixture = body->CreateFixture(&circleFixtureDef); //add a fixture to the body

}
