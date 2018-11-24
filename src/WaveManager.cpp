/*
  WaveManager.cpp

  Purpose: Handle production and deployment of waves within a single class.

  @author Jeremy Elkayam
 */

#include <deque>
#include <functional>
#include "Events/ActorDestroyedEvent.hpp"
#include "WaveManager.hpp"


WaveManager::WaveManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<TextureLoader> textureLoader){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> textureLoader = textureLoader;
  this -> currentWaveNumber = 0;
  this -> setUpPossibleEnemies();
}


void WaveManager::setUpPossibleEnemies(){
  shared_ptr<MeleeUnit> skinnyKid = make_shared<SkinnyKidUnit>(textLoader, eventManager, textureLoader);

  shared_ptr<MeleeUnit> averageKid = make_shared<AverageKidUnit>(textLoader, eventManager, textureLoader);

  shared_ptr<MeleeUnit> fatKid = make_shared<FatKidUnit>(textLoader, eventManager, textureLoader);

  enemies.push_back(skinnyKid);
  enemies.push_back(averageKid);
  enemies.push_back(fatKid);
}

void WaveManager::setupWaves(int difficulty){

  currentWaveNumber = 0;

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

  buildDistanceEntryMap(entryPositions,distances);

  distancesFromEntryPositions=getNormalizedDistanceMap(distancesFromEntryPositions);

  double range=(--distancesFromEntryPositions.end())->first;

  std::normal_distribution<double> spawn_location_rng(0+currentWaveNumber*(range/numWaves),range/3);

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

    double spawn_distance;
    do{
      spawn_distance=spawn_location_rng(rnd_gen);
    }while(0<spawn_distance && spawn_distance<range);
    //a shitty solution... let's try and figure out something else

    int roundedKey;

    //iterate through every key in the map
    for(auto iterator=(distancesFromEntryPositions.begin());iterator!=distancesFromEntryPositions.end();iterator++){
      //current and next keys in the map
      double current=iterator->first;
      double next=(++iterator)->first;
      iterator--;

      //if we're between the current and next keys, we need to figure out which one we're closer to. then we round
      if(current < spawn_distance && spawn_distance < next){
        double average=(current+next)/2;
        //if closer to current, round to it. else round to next
        spawn_distance<average ? roundedKey=current : roundedKey=next;
        //we're done with this loop since we found the right key so just break out of it
        break;
      }
      roundedKey=iterator->first;
    }

    //now that we have our distance key, we can get all of the entry positions with that distance
    vector<intPair> chosenEntrances=distancesFromEntryPositions[roundedKey];

    //pick a random intPair from the vector
    uniform_int_distribution<int> entrance_chooser_rng(0,chosenEntrances.size());
    intPair entryPoint=chosenEntrances[entrance_chooser_rng(rnd_gen)];

    //set the intPair to the enemy's starting point on the board grid
    enemy->setRow(entryPoint.first);
    enemy->setCol(entryPoint.second);

    result.push(enemy);
  }
  return result;
}


//handle events
void WaveManager::delegateMethod(const EventInterface& event){

}

void WaveManager::startNextWave() {
  currentWaveNumber++;
  //TODO - body
}


void WaveManager::endCurrentWave() {
    //TODO - code to stop the wave
    numWaves--;
}

void WaveManager::spawnNextUnit() {
    shared_ptr<MeleeUnit> next_unit = currentWave.front();
    //TODO - spawn the unit
    currentWave.pop();

    //add the unit to the vector of currently spawned units
    //use the ID
    spawnedCurrentWave[next_unit->getID()]=next_unit;
}

void WaveManager::update(float deltaS) {
    //TODO - implement
}

void WaveManager::setDistances(vector<vector<int>>& dists) {
  distances=dists;
}

void WaveManager::setEntryPoints(vector<int>& entries) {
  entryPositions=entries;
}

void WaveManager::buildDistanceEntryMap(vector<int>& entrypoints, vector<vector<int>>& distances) {

  /*
   * for every entrance point in the map
   * get its distance
   * if it's not a key, add it as a key
   * make a new intpair with row and col
   * push_back the intpair to the end of the vector that the distance points to
   */

  for(int z=0;z<entrypoints.size();z+=2){


    intPair rowcol;
    int col=entrypoints[z];
    int row=entrypoints[z+1];//remember, it's stored here as "col, row, col, row"
    int distance=distances[row][col];

    rowcol.first=row;
    rowcol.second=col;

    //works regardless of whether or not the key exists because it instantiates the key
    //and the vector
    distancesFromEntryPositions[distance].push_back(rowcol);
  }
}

map<int,vector<WaveManager::intPair>> WaveManager::getNormalizedDistanceMap(map<int,vector<intPair>>& distancesFromEntryPositions){
  map<int,vector<intPair>> result;

  int min=distancesFromEntryPositions.begin()->first;

  int max=(--distancesFromEntryPositions.end())->first;

  for( auto it = distancesFromEntryPositions.begin(); it != distancesFromEntryPositions.end(); it++ )
  {
    int oldkey=it->first;
    int newkey=max-(it->first);

    result[newkey]=it->second;
  }
  return result;
}


queue<shared_ptr<MeleeUnit>> WaveManager::getNextWave() {return currentWave;}

unordered_map<long long,shared_ptr<MeleeUnit>>& WaveManager::getSpawnedEnemyUnits(){return spawnedCurrentWave;}

void WaveManager::registerDelegates() {
  //bind our delegate function for mouse presses
  EventManager::EventDelegate actorDestroyedDelegate = std::bind(&WaveManager::handleActorDestroyed, this, _1);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorDestroyedDelegate, textLoader -> getString(string("IDS_WaveManager_ActorDestroyed")),actorDestroyedEventType);
}

void WaveManager::deregisterDelegates() {

}


void WaveManager::handleActorDestroyed(const EventInterface& event) {

}