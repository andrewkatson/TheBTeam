//
// Created by jeremy on 10/26/18.
//

#ifndef CSCI437_FATKIDUNIT_HPP
#define CSCI437_FATKIDUNIT_HPP

#include "MeleeUnit.hpp"

class FatKidUnit : public MeleeUnit {

private:

public:

  FatKidUnit(shared_ptr<TextLoader> textLoader, shared_ptr<EventManager> eventManager, shared_ptr<TextureLoader> textureLoader);
  void move(float delta, float xmult, float ymult){MeleeUnit::move(delta, xmult, ymult);}
  void update(float delta){MeleeUnit::update(delta);}
};


#endif //CSCI437_FATKIDUNIT_HPP
