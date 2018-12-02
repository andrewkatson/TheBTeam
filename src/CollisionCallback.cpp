#include "CollisionCallback.hpp"


void CollisionCallback::BeginContact(b2Contact* contact){
  cout << "Collision Callback Called" << endl;
  void* bodyUserDataA = contact -> GetFixtureA()-> GetBody() -> GetUserData();
  void* bodyUserDataB = contact -> GetFixtureB() -> GetBody() -> GetUserData();
  if (bodyUserDataA){
    //check if Fixture A is a tower or an actor, if true for one of them you startContact with the B fixture
    if (static_cast<TowerInterface*>( bodyUserDataA )){
      static_cast<TowerInterface*>( bodyUserDataA ) -> startContact(bodyUserDataB);
    }
    else if (static_cast<ActorInterface*>( bodyUserDataA )){
      cout << bodyUserDataA << endl;
      static_cast<ActorInterface*>( bodyUserDataA ) -> startContact(bodyUserDataB);
      cout << "In Begin Contact Actor Interface bodyUserDataA start Contact with bodyUserDataB"<<endl;
    }
  }
  //check if Fixture B is a tower or an actor, if true for one of them you startContact with the A fixture
  if (bodyUserDataB ){
    if (static_cast<TowerInterface*>( bodyUserDataB )){
      static_cast<TowerInterface*>( bodyUserDataB ) -> startContact(bodyUserDataA);
    }
    else if (static_cast<ActorInterface*>( bodyUserDataB)){
      static_cast<ActorInterface*>( bodyUserDataB ) -> startContact(bodyUserDataA);
      cout << "In Begin Contact Actor Interface bodyUserDataB start Contact with bodyUserDataA"<<endl;
    }
  }
}

void CollisionCallback::EndContact(b2Contact* contact){
  void* bodyUserDataA = contact -> GetFixtureA()-> GetBody() -> GetUserData();
  void* bodyUserDataB = contact -> GetFixtureB() -> GetBody() -> GetUserData();
  if (bodyUserDataA){
    //check if Fixture A is a tower or an actor, if true for one of them you end contact with the B fixture
    if (static_cast<TowerInterface*>( bodyUserDataA )){
      static_cast<TowerInterface*>( bodyUserDataA ) -> endContact(bodyUserDataB);
    }
    else if (static_cast<ActorInterface*>( bodyUserDataA )){
      static_cast<ActorInterface*>( bodyUserDataA ) -> endContact(bodyUserDataB);
      cout << "In Begin Contact Actor Interface bodyUserDataA END Contact with bodyUserDataB"<<endl;
    }
  }
  if (bodyUserDataB ){
    //check if Fixture B is a tower or an actor, if true for one of them you end contact with the A fixture
    if (static_cast<TowerInterface*>( bodyUserDataB )){
      static_cast<TowerInterface*>( bodyUserDataB ) -> endContact(bodyUserDataA);
    }
    else if (static_cast<ActorInterface*>( bodyUserDataB)){
      static_cast<ActorInterface*>( bodyUserDataB ) -> endContact(bodyUserDataA);
      cout << "In Begin Contact Actor Interface bodyUserDataA END Contact with bodyUserDataB"<<endl;
    }
  }
}
