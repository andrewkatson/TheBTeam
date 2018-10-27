/*
  WaveManager.cpp

  Purpose: Handle production and deployment of waves within a single class.

  @author Jeremy Elkayam
 */
#include "WaveManager.hpp"


WaveManager::WaveManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> setUpPossibleEnemies();
}


void WaveManager::setUpPossibleEnemies(){
  //constants for the skinny kid
  //health
  int skinnyKidHP = textLoader -> getConstant(string("IDS_SK_HP"));
  //damage
  int skinnyKidDM = textLoader -> getConstant(string("IDS_SK_DM"));
  //armor
  int skinnyKidAM = textLoader -> getConstant(string("IDS_SK_AM"));
  //speed
  int skinnyKidSP = textLoader -> getConstant(string("IDS_SK_SP"));
  //armor  penetration
  int skinnyKidAP = textLoader -> getConstant(string("IDS_SK_AP"));
  //attack radius
  int skinnyKidAR = textLoader -> getConstant(string("IDS_SK_AR"));

  //constants for the average kid
  int averageKidHP = textLoader -> getConstant(string("IDS_AK_HP"));
  int averageKidDM = textLoader -> getConstant(string("IDS_AK_DM"));
  int averageKidAM = textLoader -> getConstant(string("IDS_AK_AM"));
  int averageKidSP = textLoader -> getConstant(string("IDS_AK_SP"));
  int averageKidAP = textLoader -> getConstant(string("IDS_AK_AP"));
  int averageKidAR = textLoader -> getConstant(string("IDS_AK_AR"));

  //constants for the fat kid
  int fatKidHP = textLoader -> getConstant(string("IDS_FK_HP"));
  int fatKidDM = textLoader -> getConstant(string("IDS_FK_DM"));
  int fatKidAM = textLoader -> getConstant(string("IDS_FK_AM"));
  int fatKidSP = textLoader -> getConstant(string("IDS_FK_SP"));
  int fatKidAP = textLoader -> getConstant(string("IDS_FK_AP"));
  int fatKidAR = textLoader -> getConstant(string("IDS_FK_AR"));

  shared_ptr<ActorInterface> skinnyKid = make_shared<SkinnyKidUnit>(SkinnyKidUnit(skinnyKidHP, skinnyKidDM, skinnyKidAM, skinnyKidSP, skinnyKidAP, skinnyKidAR));
  shared_ptr<ActorInterface> averageKid = make_shared<AverageKidUnit>(AverageKidUnit(averageKidHP, averageKidDM, averageKidAM, averageKidSP, averageKidAP, averageKidAR));
  shared_ptr<ActorInterface> fatKid = make_shared<FatKidUnit>(FatKidUnit(fatKidHP, fatKidDM, fatKidAM, fatKidSP, fatKidAP, fatKidAR));

  enemies.push_back(skinnyKid);
  enemies.push_back(averageKid);
  enemies.push_back(fatKid);
}

//handle events
void WaveManager::delegateMethod(const EventInterface& event){}

void WaveManager::startNextWave() {
    queue<shared_ptr<ActorInterface>> next_wave = waves.front();
    //TODO - code for spawning waves
}

void WaveManager::endCurrentWave() {
    //TODO - code to stop the wave
    waves.pop();
}

void WaveManager::spawnNextUnit() {
    shared_ptr<ActorInterface> next_unit = enemies.front();
    //TODO - spawn the unit
}

void WaveManager::update(float deltaS) {
    //TODO - implement
}


queue <shared_ptr<ActorInterface>> WaveManager::getNextWave() {return waves.front();}

queue <queue<shared_ptr < ActorInterface>>>WaveManager::getWaves() {return waves;}
