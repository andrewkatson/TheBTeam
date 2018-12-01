/*
  WaveManager.cpp

  Purpose: Handle production and deployment of waves within a single class.

  @author Jeremy Elkayam
 */

#include "WaveManager.hpp"


WaveManager::WaveManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader, shared_ptr<TextureLoader> textureLoader, int windowX, int windowY,int level,int startingDifficulty, shared_ptr<b2World> world){
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> textureLoader = textureLoader;
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> level = level;
  this -> difficulty = startingDifficulty;
  this -> currentWaveNumber = 1;
  this -> timeElapsed = 0;
  //this -> setUpPossibleEnemies();
  this -> setupWaves();
  this -> registerDelegates();
  this -> world = world;
}

WaveManager::~WaveManager(){
  this -> deregisterDelegates();
}

void WaveManager::registerEvents(){
  WaveChangeEvent wce = WaveChangeEvent();
  EventType wceType = wce.getEventType();

  this -> eventManager -> registerEvent(wceType);
}

void WaveManager::registerDelegates() {
  EventManager::EventDelegate actorDestroyedDelegate = std::bind(&WaveManager::handleActorDestroyed, this, _1);

  //make an event and get its type
  ActorDestroyedEvent actorDestroyedEvent = ActorDestroyedEvent();
  const EventType actorDestroyedEventType = actorDestroyedEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(actorDestroyedDelegate, textLoader -> getString(string("IDS_WaveManager_ActorDestroyed")),actorDestroyedEventType);

  EventManager::EventDelegate mapGenDelegate = std::bind(&WaveManager::handleMapGenerated, this, _1);
  MapGeneratedEvent mapGenEvent = MapGeneratedEvent();
  const EventType mapGenEventType = mapGenEvent.getEventType();
  this -> eventManager -> registerDelegate(mapGenDelegate, textLoader -> getString(string("IDS_WaveManager_MapGenerated")),mapGenEventType);

  EventManager::EventDelegate levelChangeDelegate = std::bind(&WaveManager::handleLevelChanged, this, _1);
  LevelChangeEvent levelChangeEvent = LevelChangeEvent();
  const EventType levelChangeEventType = levelChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(levelChangeDelegate, textLoader -> getString(string("IDS_WaveManager_LevelChange")),levelChangeEventType);

  EventManager::EventDelegate difficultyChangeDelegate = std::bind(&WaveManager::handleDiffChanged, this, _1);
  DifficultyChangeEvent difficultyChangeEvent = DifficultyChangeEvent();
  const EventType difficultyChangeEventType = difficultyChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(levelChangeDelegate, textLoader -> getString(string("IDS_WaveManager_DifficultyChange")),difficultyChangeEventType);

  EventManager::EventDelegate waveChangeDelegate = std::bind(&WaveManager::handleWaveChange, this, _1);
  WaveChangeEvent waveChangeEvent = WaveChangeEvent();
  const EventType waveChangeEventType = waveChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(waveChangeDelegate, textLoader -> getString(string("IDS_WaveManager_WaveChange")),waveChangeEventType);
}

void WaveManager::deregisterDelegates() {

}

/*
void WaveManager::setUpPossibleEnemies(){
  shared_ptr<MeleeUnit> skinnyKid = make_shared<SkinnyKidUnit>(textLoader, eventManager, textureLoader);
  skinnyKid -> setWorld(world);

  shared_ptr<MeleeUnit> averageKid = make_shared<AverageKidUnit>(textLoader, eventManager, textureLoader);
  averageKid -> setWorld(world);

  shared_ptr<MeleeUnit> fatKid = make_shared<FatKidUnit>(textLoader, eventManager, textureLoader);
  fatkid -> setWorld(world);

  enemies.push_back(skinnyKid);
  enemies.push_back(averageKid);
  enemies.push_back(fatKid);
}
*/

void WaveManager::setupWaves(){

  printf("difficulty: %d\nlevel: %d\n",difficulty,level);

  currentWaveNumber = 1;

  std::mt19937 rnd_gen (rd ());

  //average number of waves is the difficulty times the level, e.g. difficulty 3 on level 10: 30 waves

  double avg=difficulty*level;

  std::normal_distribution<double> num_waves_rng(avg,avg*.4);

  unsigned int num_waves = round(num_waves_rng(rnd_gen));

  if(num_waves<=0) num_waves=1; //on the off-chance that we generated a negative or 0 value, round that shit

  numWaves=num_waves;

  printf("picked our waves: %d waves\n",numWaves);
}


void WaveManager::createNextWave() {
  assert(!distances.empty() && "Distances must be initialized AND UPDATED EVERY TIME THE MAP CHANGES.");
  assert(!entryPositions.empty());
  assert(currentWave.empty() && "don't create a new wave if there's still enemies left in the one you already have...");

  double avg = difficulty * currentWaveNumber * level * textLoader->getDouble("IDS_WAVE_WEIGHT_AVG_SCALAR");

  std::normal_distribution<double> wave_weight_rng(avg, avg * .4);

  std::mt19937 rnd_gen(rd());

  //average 15, standard deviation 5
  std::normal_distribution<double> enemy_type_rng(15, 5);

  //At minimum, stats will be scaled down by 20%
  double min_scale = textLoader->getDouble("IDS_STAT_MIN_SCALAR");

  //At maximum, stats will be scaled up by 20% for difficulty 1, 40% for 2, etc.
  double max_scale = textLoader->getDouble("IDS_STAT_MAX_SCALAR") * difficulty;

  std::uniform_real_distribution<double> percent_perturbation_rng(min_scale, max_scale);

  buildDistanceEntryMap(entryPositions, distances);
/*
  for (auto it = distancesFromEntryPositions.begin();it != distancesFromEntryPositions.end(); it++){
    printf("distances. key = %d\nvalues: ",it->first);
    for(int z=0;z<it->second.size();z++){
      printf("{ %d , %d }",it->second[z].first,it->second[z].second);
    }
    printf("\n");
  }
*/

  distancesFromEntryPositions=getNormalizedDistanceMap(distancesFromEntryPositions);
  //printf("***** NORMALIZE ***** \n");
/*
  for (auto it = distancesFromEntryPositions.begin();it != distancesFromEntryPositions.end(); it++){
    printf("distances. key = %d\nvalues: ",it->first);
    for(int z=0;z<it->second.size();z++){
      printf("{ %d , %d }",it->second[z].first,it->second[z].second);
    }
    printf("\n");
  }
  */
  double range=(--distancesFromEntryPositions.end())->first;

  std::normal_distribution<double> spawn_location_rng(0+currentWaveNumber*(range/numWaves),range/3);

  double total_wave_weight=wave_weight_rng(rnd_gen);

  for(double weight=0;weight<total_wave_weight;){
    double randnum=enemy_type_rng(rnd_gen);
    shared_ptr<MeleeUnit> enemy;
    if(randnum<10){
      enemy = make_shared<SkinnyKidUnit>(textLoader,eventManager,textureLoader);
      weight+=textLoader->getDouble("IDS_SKINNY_WEIGHT");
    }else if(randnum>=10 && randnum<20){
      enemy = make_shared<AverageKidUnit>(textLoader,eventManager,textureLoader);
      //enemy = static_pointer_cast<MeleeUnit>(enemies[1]);//add a normal kid
      weight+=textLoader->getDouble("IDS_AVERAGE_WEIGHT");
    }else if(randnum>=20){
      enemy = make_shared<FatKidUnit>(textLoader,eventManager,textureLoader);
      //enemy = static_pointer_cast<MeleeUnit>(enemies[2]);//add a fat kid
      weight+=textLoader->getDouble("IDS_FAT_WEIGHT");
    }
    //Randomize this stuff to be +/- 20% of the default

    enemy->setHitpoints(enemy->getHitpoints()+enemy->getHitpoints()*percent_perturbation_rng(rnd_gen));

    enemy->setLunchMoney(enemy->getLunchMoney()+enemy->getLunchMoney()*percent_perturbation_rng(rnd_gen));

    enemy->setDamage(enemy->getDamage()+enemy->getDamage()*percent_perturbation_rng(rnd_gen));

    enemy -> setWorld(world);

    double spawn_distance;
    do{
      spawn_distance=spawn_location_rng(rnd_gen);
    }while(0<spawn_distance && spawn_distance<range);
    //a shitty solution... let's try and figure out something else

    int roundedKey;

    //iterate through every key in the map
    for(auto iterator=(distancesFromEntryPositions.begin());iterator!=distancesFromEntryPositions.end();iterator++){
      //printf("picking entrance. key: %d,length of vector: %ld\n",iterator->first,iterator->second.size());
      //for(int z=0;z<iterator->second.size();z++){
      //  printf("{ %d , %d } ",iterator->second[z].first,iterator->second[z].second);
      //}
      //printf("\n");
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

    //printf("rounded key: %d\n",roundedKey);

    //now that we have our distance key, we can get all of the entry positions with that distance
    vector<intPair> chosenEntrances=distancesFromEntryPositions[roundedKey];

    /*
    printf("chosen entrances size: %ld\n",chosenEntrances.size());
    for(int z=0;z<chosenEntrances.size();z++){
      printf("{ %d , %d } ",chosenEntrances[z].first,chosenEntrances[z].second);
    }
    printf("\n");
*/
    //pick a random intPair from the vector
    uniform_int_distribution<unsigned long> entrance_chooser_rng(0,chosenEntrances.size()-1);
    intPair entryPoint=chosenEntrances[entrance_chooser_rng(rnd_gen)];

    printf("chosen entry point row: %d\ncol: %d\n",entryPoint.first,entryPoint.second);

    //set the intPair to the enemy's starting point on the board grid
    enemy->setRow(entryPoint.first);
    enemy->setCol(entryPoint.second);

    uniform_real_distribution<float>entry_offset_rng(0.0001,0.9999);

    float offset=entry_offset_rng(rnd_gen);
    float xOffset,yOffset;

    if(entryPoint.first == 0){
      yOffset =0.001;
      xOffset=offset;
    }else if(entryPoint.second==0){
      yOffset =offset;
      xOffset=0.001;
    }else if(entryPoint.first==distances.size()-1){
      yOffset =0.999;
      xOffset=offset;
    }else{
      yOffset =offset;
      xOffset=0.999;
    }

    enemy->setXCoordinate((float)windowX / (float)distances[0].size() * ((float)entryPoint.second + xOffset)); // multiply tile size by tiles
    enemy->setYCoordinate((float)windowY/ (float)distances.size() * ((float)entryPoint.first + yOffset)); //window size / board size = tile size

    currentWave.push(enemy);
  }
  printf("created a wave with %ld units\n",currentWave.size());
}


void WaveManager::startNextWave() {
  assert(currentWave.empty() && "this will make a wave for you... so there shouldn't be a wave");
  assert(spawnedCurrentWave.empty() && "A new wave should only begin if the last wave is completely eliminated.");
  createNextWave();
  numWaves--;
}


void WaveManager::endCurrentWave() {
  assert(spawnedCurrentWave.empty());
}

void WaveManager::spawnNextUnit() {
  //this should only ever be called if there are units to spawn
  assert(!currentWave.empty());

  shared_ptr<MeleeUnit> next_unit = currentWave.front();
  currentWave.pop();

  //add the unit to the vector of currently spawned units
  //use the ID
  spawnedCurrentWave[next_unit->getID()]=next_unit;

  printf("birthed a unit: %llx \nspawned:%ld\nleft:%ld\nxcor: %f\n ycor: %f\nrow: %d\ncol: %d\n*****\n",
          next_unit->getID(),spawnedCurrentWave.size(),currentWave.size(),next_unit->getXCoordinate(),
          next_unit->getYCoordinate(),next_unit->getRow(),next_unit->getCol());

}

void WaveManager::update(float deltaS) {
  // if there are no waves left, make a LevelChangeEvent for a new level
  // if there are waves left but no enemies left do nothing
  //printf("updating wave manager...\n");

  timeElapsed+=deltaS;
  if(timeElapsed > textLoader->getDouble("IDS_SECONDS_BETWEEN_ENEMY_SPAWNS") && !currentWave.empty())
  {
    timeElapsed=0;
    spawnNextUnit();
  }


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

  int max=(--distancesFromEntryPositions.end())->first;

  for( auto it = distancesFromEntryPositions.begin(); it != distancesFromEntryPositions.end(); it++ )
  {
    int newkey=max-(it->first);

    result[newkey]=it->second;
  }
  return result;
}


queue<shared_ptr<MeleeUnit>> WaveManager::getNextWave() {return currentWave;}

unordered_map<long long,shared_ptr<MeleeUnit>>& WaveManager::getSpawnedEnemyUnits(){return spawnedCurrentWave;}


/*
 * Handle destruction of an actor by removing it from the map of actors
 */
void WaveManager::handleActorDestroyed(const EventInterface& event) {
  /*
   * cast it
   */
  const ActorDestroyedEvent* actorDestroyedEvent = static_cast<const ActorDestroyedEvent*>(&event);

  ActorDestroyedEventData* actorDestroyedEventData = static_cast<ActorDestroyedEventData*>((actorDestroyedEvent -> data).get());

  long long actorID = actorDestroyedEventData -> actorID;//get the dead actor's ID

  //the time object of the class
  auto now = high_resolution_clock::now();
  //the actual count in nanoseconds for the time
  auto nowInNano = duration_cast<nanoseconds>(now.time_since_epoch()).count();


  if(spawnedCurrentWave.count(actorID)) {
    spawnedCurrentWave.erase(actorID);//take him off the map. he gone!

    if(spawnedCurrentWave.empty() && currentWave.empty()){
      //if both of these are empty, that means the last guy in the wave just died
      currentWaveNumber++;
      shared_ptr<EventInterface> wcEvent = make_shared<WaveChangeEvent>(currentWaveNumber, nowInNano);

      eventManager->queueEvent(wcEvent);
    }
  }
}

void WaveManager::handleMapGenerated(const EventInterface& event){
  auto mapGeneratedEvent= static_cast<const MapGeneratedEvent*>(&event);

  auto mapGeneratedEventData = static_cast<MapGeneratedEventData*>((mapGeneratedEvent->data).get());

  setDistances(mapGeneratedEventData->dists);
  setEntryPoints(mapGeneratedEventData->entrances);
}

void WaveManager::handleLevelChanged(const EventInterface& event){
  auto levelChangedEvent = static_cast<const LevelChangeEvent*>(&event);
  auto levelChangedEventData = static_cast<LevelChangeEventData*>((levelChangedEvent->data).get());

  level=levelChangedEventData->level;
  setupWaves();
}

void WaveManager::handleDiffChanged(const EventInterface& event){
  auto difficultyChangedEvent = static_cast<const DifficultyChangeEvent*>(&event);
  auto difficultyChangedEventData = static_cast<DifficultyChangeEventData*>((difficultyChangedEvent->data).get());

  difficulty=difficultyChangedEventData->difficulty;
}

void WaveManager::handleWaveChange(const EventInterface& event){
  auto waveChangeEvent = static_cast<const WaveChangeEvent*>(&event);
  auto waveChangeEventData = static_cast<const WaveChangeEventData*>((waveChangeEvent->data).get());

  if(waveChangeEventData->waveStart){
    startNextWave();
  }
}
