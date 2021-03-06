/*
  SoundManager.cpp

  Purpose: Handle loading and playing of all game sounds through simple methods.

  @author Jeremy Elkayam
*/

#include "SoundManager.hpp"

SoundManager::SoundManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){

   this -> eventManager = eventManager;
   this -> textLoader = textLoader;
   this -> registerDelegates();
   playingIndex=-1;
   newLevel=false;
   musicPlaying=false;
   musicVolume=100;
   sfxVolume=100;
}

SoundManager::~SoundManager(){
  this -> deregisterDelegates();

  for(auto iterator : music_objs){
    for(auto music : iterator.second){
      delete(music);
    }
  }

}

void SoundManager::registerDelegates(){
  EventManager::EventDelegate playSoundDelegate = std::bind(&SoundManager::handleSoundPlay, this, _1);
  PlaySoundEvent playSoundEvent= PlaySoundEvent();
  const EventType playSoundEventType = playSoundEvent.getEventType();
  this -> eventManager -> registerDelegate(playSoundDelegate, textLoader -> getString(string("IDS_SoundManager_PlaySound")),playSoundEventType);

  EventManager::EventDelegate towerCreationDelegate = std::bind(&SoundManager::handleTowerCreation, this, _1);
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  const EventType towerCreationEventType = towerCreationEvent.getEventType();
  this -> eventManager -> registerDelegate(towerCreationDelegate, textLoader -> getString(string("IDS_SoundManager_TowerCreation")),towerCreationEventType);

  EventManager::EventDelegate towerRemoveDelegate = std::bind(&SoundManager::handleTowerRemove, this, _1);
  TowerRemoveEvent towerRemoveEvent = TowerRemoveEvent();
  const EventType towerRemoveEventType = towerRemoveEvent.getEventType();
  this -> eventManager -> registerDelegate(towerRemoveDelegate, textLoader -> getString(string("IDS_SoundManager_TowerRemove")),towerRemoveEventType);

  EventManager::EventDelegate waveChangeDelegate = std::bind(&SoundManager::handleWaveChange, this, _1);
  WaveChangeEvent waveChangeEvent= WaveChangeEvent();
  const EventType waveChangeEventType = waveChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(waveChangeDelegate, textLoader -> getString(string("IDS_SoundManager_WaveChange")),waveChangeEventType);

  EventManager::EventDelegate stateChangeDelegate = std::bind(&SoundManager::handleStateChange, this, _1);
  StateChangeEvent stateChangeEvent= StateChangeEvent();
  const EventType stateChangeEventType = stateChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(stateChangeDelegate, textLoader -> getString(string("IDS_SoundManager_StateChange")),stateChangeEventType);

  EventManager::EventDelegate volumeChangeDelegate = std::bind(&SoundManager::handleVolumeChange, this, _1);
  VolumeChangeEvent volumeChangeEvent= VolumeChangeEvent();
  const EventType volumeChangeEventType = volumeChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(volumeChangeDelegate, textLoader -> getString(string("IDS_SoundManager_VolumeChange")),volumeChangeEventType);
}

void SoundManager::deregisterDelegates(){

}

void SoundManager::loadSounds(){
  /*
  pseudocode since we don't have any sounds or an xml storing our sound
  file paths

  for all the filenames in the sound files
     if(you found the file)
        append it to the sound vector
        set its buffer to buffer
     else
        stop the game and pull up a box saying you fucked up

  for all the filenames in the music files
     if(you found the file)
        append it to the music vector
  set looping t/f ****probably true but there may be special cases***
     else
        stop the game and pull up a box saying you 'screwed' up (family friendly)
 */



  //yes this hardcoded vector sucks... I know... sorry...

  vector<string>sound_paths={"IDS_Unit_Escape_Sound_Path",
                       "IDS_Level_Start_Sound_Path",
                       "IDS_Jazzy_Sound_Path",
                       "IDS_Tower_Creation_Sound_Path",
                       "IDS_Tower_Remove_Sound_Path",
                       "IDS_Failure_Sound_Path",
                       "IDS_Ding_Sound_Path",
                       "IDS_QFG_Win_Sound_Path",
                       "IDS_QFG4_Win_Sound_Path",
                       "IDS_Unit_Death_Sound_Path",
                       "IDS_Unit_Hit_By_Projectile_Sound_Path",
                       "IDS_Unit_Punch_Sound_Path",
                       "IDS_Fire_Drink_Sound_Path",
                       "IDS_Fire_MnM_Sound_Path",
                       "IDS_Fire_Pizza_Sound_Path"};
  vector<string>ids={"IDS_Unit_Escape_Noise",
                     "IDS_Level_Start_Noise",
                     "IDS_Jazzy_Noise",
                     "IDS_Tower_Creation_Noise",
                     "IDS_Tower_Remove_Noise",
                     "IDS_Failure_Noise",
                     "IDS_Ding_Noise",
                     "IDS_QFG_Win_Noise",
                     "IDS_QFG4_Win_Noise",
                     "IDS_Unit_Death_Noise",
                     "IDS_Unit_Hit_By_Projectile_Noise",
                     "IDS_Unit_Punch_Noise",
                     "IDS_Fire_Drink_Noise",
                     "IDS_Fire_MnM_Noise",
                     "IDS_Fire_Pizza_Noise",};

  assert(sound_paths.size()==ids.size());

  for(int z=0;z<sound_paths.size();z++){
    loadSound(sound_paths[z],ids[z]);
  }

  //this also sucks.... sorry...
  for(int z=0;z<=6;z++){
    sf::Music *music=new sf::Music();
    assert(music->openFromFile(textLoader->getString(string("IDS_Combat_")+std::to_string(z)+string("_Music_Path"))));
    music->setLoop(true);
    music_objs[COMBAT].push_back(music);
  }
  for(int z=0;z<=3;z++){
    sf::Music *music=new sf::Music();
    assert(music->openFromFile(textLoader->getString(string("IDS_Prep_")+std::to_string(z)+string("_Music_Path"))));
    music->setLoop(true);
    music_objs[PREP].push_back(music);
  }
  for(int z=0;z<=0;z++){
    sf::Music *music=new sf::Music();
    assert(music->openFromFile(textLoader->getString(string("IDS_End_")+std::to_string(z)+string("_Music_Path"))));
    music->setLoop(true);
    music_objs[LOSE].push_back(music);
  }

}

void SoundManager::loadSound(string path, string soundID){
  string true_path=textLoader->getString(path);
  string id=textLoader->getString(soundID);
  assert(buffers[id].loadFromFile(true_path));

  sound_objs[id].setBuffer(buffers[id]);
}


void SoundManager::playSound(string soundID){
  assert(sound_objs.count(soundID));
  sound_objs[soundID].setVolume(sfxVolume);
  sound_objs[soundID].play();
}

void SoundManager::pauseSound(string soundID){
  sound_objs[soundID].pause();
}

void SoundManager::stopSound(string soundID){
  sound_objs[soundID].stop();
}

void SoundManager::playMusic(){
  musicPlaying=true;
  music_objs[playingType][playingIndex]->setVolume(musicVolume);
  music_objs[playingType][playingIndex]->play();
}

void SoundManager::pauseMusic(){
  music_objs[playingType][playingIndex]->pause();
}

void SoundManager::stopMusic(){
  musicPlaying=false;
  music_objs[playingType][playingIndex]->stop();

}

void SoundManager::startSongOfType(int type){
  playingType=type;
  auto musics=music_objs[type];
  std::uniform_int_distribution<unsigned int> musicPicker(0,musics.size()-1);

  std::mt19937 rnd_gen(rd());

  playingIndex=musicPicker(rnd_gen);


  playMusic();
}

void SoundManager::handleSoundPlay(const EventInterface& event){

  const PlaySoundEvent* playSoundEvent = static_cast<const PlaySoundEvent*>(&event);

  PlaySoundEventData* playSoundEventData= static_cast<PlaySoundEventData*>((playSoundEvent-> data).get());

  string typeID=playSoundEventData->typeID;
  string soundID=playSoundEventData->soundID;

  playSound(typeID+soundID);
}

void SoundManager::handleLevelChanged(const EventInterface& event){
  cout << "yay sounds" << endl;
  stopMusic();
  stopSound(textLoader->getString("IDS_Jazzy_Noise"));
  stopSound(textLoader->getString("IDS_QFG_Win_Noise"));
  stopSound(textLoader->getString("IDS_QFG4_Win_Noise"));

  playSound(textLoader->getString("IDS_Level_Start_Noise"));

  startSongOfType(PREP);

  newLevel=true;
}

void SoundManager::handleTowerCreation(const EventInterface &event) {
  playSound(textLoader->getString("IDS_Tower_Creation_Noise"));
}

void SoundManager::handleTowerRemove(const EventInterface &event) {
  playSound(textLoader->getString("IDS_Tower_Remove_Noise"));
}

void SoundManager::handleWaveChange(const EventInterface & event){
//  //cout << "starting song of type" << playingIndex;
  stopSound(textLoader->getString("IDS_Jazzy_Noise"));
  stopSound(textLoader->getString("IDS_QFG_Win_Noise"));
  stopSound(textLoader->getString("IDS_QFG4_Win_Noise"));


  const WaveChangeEvent* waveChangeEvent= static_cast<const WaveChangeEvent*>(&event);

  WaveChangeEventData* waveChangeEventData= static_cast<WaveChangeEventData*>((waveChangeEvent-> data).get());

  if(waveChangeEventData->waveStart){
    if(playingIndex!=-1) stopMusic();
    startSongOfType(COMBAT);
  }else{
    stopMusic();
    if (newLevel){
      newLevel=false;
    }else {
      if (playingIndex == 3) {
        cout << "fuck yeah" << endl;
        playSound(textLoader->getString("IDS_QFG_Win_Noise"));
      } else if (playingIndex == 4 || playingIndex == 5) {
        playSound(textLoader->getString("IDS_QFG4_Win_Noise"));
      } else {
        playSound(textLoader->getString("IDS_Jazzy_Noise"));
      }
      startSongOfType(PREP);
    }
  }
}

void SoundManager::handleStateChange(const EventInterface & event){

  const StateChangeEvent* stateChangeEvent=static_cast<const StateChangeEvent*>(&event);

  StateChangeEventData* stateChangeEventData=static_cast<StateChangeEventData*>((stateChangeEvent->data).get());

  if(stateChangeEventData->state==State::Restart) {
    stopSound(textLoader->getString("IDS_Level_Start_Noise"));
    stopSound(textLoader->getString("IDS_Jazzy_Noise"));
    stopSound(textLoader->getString("IDS_QFG_Win_Noise"));
    stopSound(textLoader->getString("IDS_QFG4_Win_Noise"));
    stopMusic();
    //play the evangelion ending
    startSongOfType(LOSE);
  }else if(stateChangeEventData->state==State::Playing){
    if(!musicPlaying){
      cout << "lol" << endl;
      startSongOfType(PREP);
    }else if(playingType==LOSE){
      cout << "lol" << endl;
      stopMusic();
    }
  }else if(stateChangeEventData->state==State::MainMenu || stateChangeEventData->state==State::OptionsMenu){
    if(playingIndex!=-1) stopMusic();
  }
}

void SoundManager::handleVolumeChange(const EventInterface &event) {

  const VolumeChangeEvent* volumeChangeEvent= static_cast<const VolumeChangeEvent *>(&event);

  VolumeChangeEventData* volumeChangeEventData= static_cast<VolumeChangeEventData*>((volumeChangeEvent->data).get());

  if(volumeChangeEventData->type==SoundType::Music){
    musicVolume=volumeChangeEventData->newVolume;
  }else{
    sfxVolume=volumeChangeEventData->newVolume;
  }
}
