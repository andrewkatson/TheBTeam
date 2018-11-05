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
  shared_ptr<MeleeUnit> skinnyKid = make_shared<SkinnyKidUnit>(textLoader, eventManager);

  shared_ptr<MeleeUnit> averageKid = make_shared<AverageKidUnit>(textLoader, eventManager);

  shared_ptr<MeleeUnit> fatKid = make_shared<FatKidUnit>(textLoader, eventManager);

  enemies.push_back(skinnyKid);
  enemies.push_back(averageKid);
  enemies.push_back(fatKid);
}

void WaveManager::setupWaves(int difficulty){

  std::mt19937 rnd_gen (rd ());

  //average number of waves is the difficulty times the level, e.g. difficulty 3 on level 10: 30 waves

  double avg=difficulty*level;

  std::normal_distribution<double> num_waves_rng(avg,avg*.4);

  unsigned int num_waves = round(num_waves_rng(rnd_gen));

  if(num_waves<0) num_waves=1; //on the off-chance that we generated a negative or 0 value, round that shit

  numWaves=num_waves;

}


queue<shared_ptr<MeleeUnit>> WaveManager::makeWave(int difficulty, int waveNumber) {

  queue<shared_ptr<MeleeUnit>>result;

  double avg=difficulty*waveNumber*level*textLoader->getDouble("IDS_WAVE_WEIGHT_AVG_SCALAR");

  std::normal_distribution<double> wave_weight_rng (avg,avg*.4);

  std::mt19937 rnd_gen (rd ());

  //average 15, standard deviation 5
  std::normal_distribution<double> enemy_type_rng(15,5);

  //At minimum, stats will be scaled down by 20%
  double min_scale=textLoader->getDouble("IDS_STAT_MIN_SCALAR");

  //At maximum, stats will be scaled up by 20% for difficulty 1, 40% for 2, etc.
  double max_scale=textLoader->getDouble("IDS_STAT_MAX_SCALAR")*difficulty;

  std::uniform_real_distribution<double> percent_perturbation_rng(min_scale,max_scale);

  double total_wave_weight=wave_weight_rng(rnd_gen);

  for(double weight=0;weight<total_wave_weight;){
    double randnum=enemy_type_rng(rnd_gen);
    shared_ptr<MeleeUnit> enemy;
    if(randnum<10){
      enemy = std::static_pointer_cast<MeleeUnit>(enemies[0]);//add a skinny kid
      weight+=textLoader->getDouble("IDS_SKINNY_WEIGHT");
    }else if(randnum>=10 && randnum<20){
      enemy = static_pointer_cast<MeleeUnit>(enemies[1]);//add a normal kid
      weight+=textLoader->getDouble("IDS_AVERAGE_WEIGHT");
    }else if(randnum>=20){
      enemy = static_pointer_cast<MeleeUnit>(enemies[2]);//add a fat kid
      weight+=textLoader->getDouble("IDS_FAT_WEIGHT");
    }
    //Randomize this stuff to be +/- 20% of the default

    enemy->setHitpoints(enemy->getHitpoints()+enemy->getHitpoints()*percent_perturbation_rng(rnd_gen));

    enemy->setLunchMoney(enemy->getLunchMoney()+enemy->getLunchMoney()*percent_perturbation_rng(rnd_gen));

    enemy->setDamage(enemy->getDamage()+enemy->getDamage()*percent_perturbation_rng(rnd_gen));

    //TODO - give the enemy a spawn location

    result.push(enemy);
  }
  return result;
}


//handle events
void WaveManager::delegateMethod(const EventInterface& event){

}

void WaveManager::startNextWave() {
  //TODO - body
}


void WaveManager::endCurrentWave() {
    //TODO - code to stop the wave
    numWaves--;
}

void WaveManager::spawnNextUnit() {
    shared_ptr<ActorInterface> next_unit = currentWave.front();
    //TODO - spawn the unit
    currentWave.pop();
}

void WaveManager::update(float deltaS) {
    //TODO - implement
}


queue <shared_ptr<MeleeUnit>> WaveManager::getNextWave() {return currentWave;}
