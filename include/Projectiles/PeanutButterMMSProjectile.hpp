#pragma once
#include "Projectile.hpp"
class PeanutButterMMSProjectile : public Projectile{
public:
  PeanutButterMMSProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);
  void move(float delta){Projectile::move(delta);}
  void update(float delta){Projectile::update(delta);}
};
