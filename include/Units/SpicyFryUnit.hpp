#pragma once
#include "MeleeUnit.hpp"

class SpicyFryUnit : public MeleeUnit {

private:

public:

  SpicyFryUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager);

  void move(float delta){MeleeUnit::move(delta);}
  void update(float delta){MeleeUnit::update(delta);}
};
