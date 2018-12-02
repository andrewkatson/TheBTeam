#include "CollisionCallback.hpp"


void CollisionCallback::BeginContact(b2Contact* contact){
  void* bodyUserDataA = contact -> GetFixtureA()-> GetBody() -> GetUserData();
  void* bodyUserDataB = contact -> GetFixtureB() -> GetBody() -> GetUserData();
  if (bodyUserDataA){
    //check if Fixture A is a tower or an actor, if true for one of them you startContact with the B fixture
    TowerInterface* towerTestA = static_cast<TowerInterface*>( bodyUserDataA );
    cout << "IS tower A? " <<  towerTestA -> isTower << endl;
    cout << "AND ITS ID A! " << towerTestA -> typeID << endl;
    if (towerTestA -> isTower == true){
      static_cast<TowerInterface*>( bodyUserDataA ) -> startContact(bodyUserDataB);
      cout << "In Begin Contact TOWER Interface bodyUserDataA START Contact with bodyUserDataB"<<'\n'<<endl;
    }
    else if (towerTestA -> isActor == true){
      static_cast<ActorInterface*>( bodyUserDataA ) -> startContact(bodyUserDataB);
      cout << "In Begin Contact ACTOR Interface bodyUserDataA START Contact with bodyUserDataB"<<'\n'<<endl;
    }
  }
  //check if Fixture B is a tower or an actor, if true for one of them you startContact with the A fixture
  if (bodyUserDataB ){
    TowerInterface*  towerTestB = static_cast<TowerInterface*>( bodyUserDataB );
    cout << "IS tower B? " <<  towerTestB -> isTower << endl;
    cout << "AND ITS ID B! " << towerTestB -> typeID << endl;
    if (towerTestB -> isTower == true){
      static_cast<TowerInterface*>( bodyUserDataB ) -> startContact(bodyUserDataA);
      cout << "In Begin Contact TOWER Interface bodyUserDataB START Contact with bodyUserDataA"<<'\n'<<endl;
    }
    else if (towerTestB -> isActor == true){
      static_cast<ActorInterface*>( bodyUserDataB ) -> startContact(bodyUserDataA);
      cout << "In Begin Contact ACTOR Interface bodyUserDataB START Contact with bodyUserDataA"<<'\n'<<endl;
    }
  }
}

void CollisionCallback::EndContact(b2Contact* contact){
  void* bodyUserDataA = contact -> GetFixtureA()-> GetBody() -> GetUserData();
  void* bodyUserDataB = contact -> GetFixtureB() -> GetBody() -> GetUserData();
  if (bodyUserDataA){
    //check if Fixture A is a tower or an actor, if true for one of them you end contact with the B fixture
    TowerInterface* testTowerA = static_cast<TowerInterface*>(bodyUserDataA) ;
    if (testTowerA -> isTower){
      static_cast<TowerInterface*>( bodyUserDataA ) -> endContact(bodyUserDataB);
      cout << "In Begin Contact TOWER Interface bodyUserDataA END Contact with bodyUserDataB"<<'\n'<<endl;
    }
    else if (testTowerA -> isActor){
      static_cast<ActorInterface*>( bodyUserDataA ) -> endContact(bodyUserDataB);
      cout << "In Begin Contact ACTOR Interface bodyUserDataA END Contact with bodyUserDataB"<<'\n'<<endl;
    }
  }
  if (bodyUserDataB ){
    //check if Fixture B is a tower or an actor, if true for one of them you end contact with the A fixture
    TowerInterface* testTowerB= static_cast<TowerInterface*>( bodyUserDataB );
    if (testTowerB -> isTower){
      static_cast<TowerInterface*>( bodyUserDataB ) -> endContact(bodyUserDataA);
      cout << "In Begin Contact TOWER Interface bodyUserDataB END Contact with bodyUserDataA"<<'\n'<<endl;
    }
    else if (testTowerB -> isActor){
      static_cast<ActorInterface*>( bodyUserDataB ) -> endContact(bodyUserDataA);
      cout << "In Begin Contact ACTOR Interface bodyUserDataB END Contact with bodyUserDataA"<<'\n'<<endl;
    }
  }
}
