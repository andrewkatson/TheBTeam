#include "AllyCompView.hpp"

AllyCompView::AllyCompView(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic,shared_ptr<PlayingScreenHeader> playingScreenHeader){
  this -> textLoader = textLoader;
  this -> eventManager = eventManager;
  this -> gameLogic = gameLogic;
  this -> waveManager = gameLogic->getWaveManager();
  this -> playingScreenHeader = playingScreenHeader;
}

void AllyCompView::updateAllyCompView(float deltaS){
  if(gameLogic->getGameState()==State::Playing){
    updateProjectiles(deltaS);
  }
}
/*
 * Call the update methods for all the projectiles which will move them closer to their target
 * if they hit
 */
void AllyCompView::updateProjectiles(float deltaS){
  unordered_map<long long, shared_ptr<ActorInterface>> allProjectiles = gameLogic -> getFiredProjectiles();

  for(auto it : allProjectiles){

    shared_ptr<ActorInterface> projectile = it.second;

    Projectile* convertedProjeectile = dynamic_cast<Projectile*>(projectile.get());

    convertedProjeectile -> update(deltaS);
  }
}

void AllyCompView::moveAllyUnits(float deltaS){

}
