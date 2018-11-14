#pragma once
#include "MeleeUnit.hpp"

class SpicyFryUnit : public MeleeUnit {

private:

public:

  SpicyFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);
  void move(float delta,int xmult, int ymult){MeleeUnit::move(delta,xmult,ymult);}
  void update(float delta){MeleeUnit::update(delta);}
};
