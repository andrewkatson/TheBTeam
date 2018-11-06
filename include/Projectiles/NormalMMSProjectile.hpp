#pragma once
#include "Projectile.hpp"
class NormalMMSProjectile : public Projectile{
public:
  NormalMMSProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager);
  void move(float delta){Projectile::move(delta);}
  void update(float delta){Projectile::update(delta);}
};
