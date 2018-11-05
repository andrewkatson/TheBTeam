#pragma once

#include "Projectile.hpp"
class SlushieProjectile : public Projectile{
public:
  SlushieProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager);
  void move(float delta){Projectile::move(delta);}
  void update(float delta){Projectile::update(delta);}
};
