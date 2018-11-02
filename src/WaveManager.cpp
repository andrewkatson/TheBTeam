/*
  WaveManager.cpp

  Purpose: Handle production and deployment of waves within a single class.

  @author Jeremy Elkayam
 */

#include <deque>
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
  //lunch money
  int skinnyKidLM = textLoader -> getConstant(string("IDS_SK_LM"));

  //constants for the average kid
  int averageKidHP = textLoader -> getConstant(string("IDS_AK_HP"));
  int averageKidDM = textLoader -> getConstant(string("IDS_AK_DM"));
  int averageKidAM = textLoader -> getConstant(string("IDS_AK_AM"));
  int averageKidSP = textLoader -> getConstant(string("IDS_AK_SP"));
  int averageKidAP = textLoader -> getConstant(string("IDS_AK_AP"));
  int averageKidAR = textLoader -> getConstant(string("IDS_AK_AR"));
  int averageKidLM = textLoader -> getConstant(string("IDS_AK_LM"));

  //constants for the fat kid
  int fatKidHP = textLoader -> getConstant(string("IDS_FK_HP"));
  int fatKidDM = textLoader -> getConstant(string("IDS_FK_DM"));
  int fatKidAM = textLoader -> getConstant(string("IDS_FK_AM"));
  int fatKidSP = textLoader -> getConstant(string("IDS_FK_SP"));
  int fatKidAP = textLoader -> getConstant(string("IDS_FK_AP"));
  int fatKidAR = textLoader -> getConstant(string("IDS_FK_AR"));
  int fatKidLM = textLoader -> getConstant(string("IDS_FK_LM"));

  shared_ptr<MeleeUnit> skinnyKid = make_shared<SkinnyKidUnit>(
    skinnyKidHP, skinnyKidDM, skinnyKidAM, skinnyKidSP, skinnyKidAP, skinnyKidAR, skinnyKidLM);

  shared_ptr<MeleeUnit> averageKid = make_shared<AverageKidUnit>(
    averageKidHP, averageKidDM, averageKidAM, averageKidSP, averageKidAP, averageKidAR, averageKidLM);

  shared_ptr<MeleeUnit> fatKid = make_shared<FatKidUnit>(
    fatKidHP, fatKidDM, fatKidAM, fatKidSP, fatKidAP, fatKidAR, fatKidLM);

  enemies.push_back(skinnyKid);
  enemies.push_back(averageKid);
  enemies.push_back(fatKid);
}

void WaveManager::setupWaves(int difficulty){

  std::mt19937 rnd_gen (rd ());

  //average number of waves is the difficulty times the level, e.g. difficulty 3 on level 10: 30 waves

  double avg=difficulty*level;

  std::normal_distribution<double> num_waves_rng(avg,avg*.4)

  unsigned long num_waves=round(num_waves_rng(rnd_gen));

  if(num_waves<0) num_waves=1; //on the off-chance that we generated a negative or 0 value, round that shit

  numWaves=num_waves;

  //waves = queue<queue<shared_ptr<ActorInterface>>>(std::deque<deque<shared_ptr<ActorInterface>>>(num_waves,NULL));

  //TODO - initialize the queue of waves to have num_waves amount of empty waves

}


queue<shared_ptr<MeleeUnit>> WaveManager::makeWave(int difficulty, int waveNumber) {

  queue<shared_ptr<MeleeUnit>>result;

  std::exponential_distribution<int> wave_weight_rng (difficulty*waveNumber*level*3);

  std::mt19937 rnd_gen (rd ());

  //average 15, standard deviation 5
  std::normal_distribution<double> enemy_type_rng(15,5);

  //At minimum, stats will be scaled down by 20%
  double min_scale=-.2;

  //At maximum, stats will be scaled up by 20% for difficulty 1, 40% for 2, etc.
  double max_scale=.2*difficulty;

  std::uniform_real_distribution<double> percent_perturbation_rng(min_scale,max_scale);

  unsigned int total_wave_weight=wave_weight_rng(rnd_gen);//TODO - once you figure out how to declare wave weight rng, this should be generated by it

  for(int weight=0;weight<total_wave_weight;){
    int randnum=enemy_type_rng(rnd_gen);
    MeleeUnit enemy;
    if(randnum<10){//TODO - figure out how to ACTUALLY downcast this
      enemy = static_cast<MeleeUnit>(*enemies[0].get());//add a skinny kid
      weight+=
    }else if(randnum>=10 && randnum<20){
      enemy = static_cast<MeleeUnit>(*enemies[1].get());//add a normal kid
      weight+=
    }else if(randnum>=20){
      enemy = static_cast<MeleeUnit>(*enemies[2].get());//add a fat kid
      weight+=
    }

    //Randomize this stuff to be +/- 20% of the default

    enemy.setHitpoints(enemy.getHitpoints()+enemy.getHitpoints()*std::lround(percent_perturbation_rng(rnd_gen)));

    enemy.setLunchMoney(enemy.getLunchMoney()+enemy.getLunchMoney()*std::lround(percent_perturbation_rng(rnd_gen)));

    enemy.setDamage(enemy.getDamage()+enemy.getDamage()*std::lround(percent_perturbation_rng(rnd_gen)));
  }
}

/*
//handle events
void WaveManager::delegateMethod(const EventInterface& event){

}*/

void WaveManager::startNextWave() {
  queue<shared_ptr<MeleeUnit>> next_wave = waves.front();
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


queue <shared_ptr<MeleeUnit>> WaveManager::getNextWave() {return waves.front();}

queue <queue<shared_ptr < MeleeUnit>>>WaveManager::getWaves() {return waves;}
