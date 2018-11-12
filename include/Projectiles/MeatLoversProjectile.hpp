#pragma once
#include "Projectile.hpp"
class MeatLoversProjectile : public Projectile{
public:
  MeatLoversProjectile(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);
  void move(float delta){Projectile::move(delta);}
  void update(float delta){Projectile::update(delta);}
};
