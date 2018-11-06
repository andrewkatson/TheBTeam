#pragma once
#include "Projectile.hpp"
class SodaProjectile : public Projectile{
public:
  SodaProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager);
  void move(float delta){Projectile::move(delta);}
  void update(float delta){Projectile::update(delta);}
};
