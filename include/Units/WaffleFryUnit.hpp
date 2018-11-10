#pragma once
#include "MeleeUnit.hpp"

class WaffleFryUnit : public MeleeUnit {

private:

public:

  WaffleFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);
  void move(float delta){MeleeUnit::move(delta);}
  void update(float delta){MeleeUnit::update(delta);}
};
