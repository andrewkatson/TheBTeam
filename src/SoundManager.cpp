/*
  SoundManager.cpp

  Purpose: Handle loading and playing of all game sounds through simple methods.

  @author Jeremy Elkayam
*/

#include <Events/TowerRemoveEvent.hpp>
#include <Events/TowerCreationEvent.hpp>
#include "SoundManager.hpp"

SoundManager::SoundManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){

   this -> eventManager = eventManager;
   this -> textLoader = textLoader;
   this -> registerDelegates();
}

SoundManager::~SoundManager(){
  this -> deregisterDelegates();
}

void SoundManager::registerDelegates(){
  EventManager::EventDelegate playSoundDelegate = std::bind(&SoundManager::handleSoundPlay, this, _1);
  PlaySoundEvent playSoundEvent= PlaySoundEvent();
  const EventType playSoundEventType = playSoundEvent.getEventType();
  this -> eventManager -> registerDelegate(playSoundDelegate, textLoader -> getString(string("IDS_SoundManager_PlaySound")),playSoundEventType);

  EventManager::EventDelegate levelChangeDelegate = std::bind(&SoundManager::handleLevelChanged, this, _1);
  LevelChangeEvent levelChangeEvent = LevelChangeEvent();
  const EventType levelChangeEventType = levelChangeEvent.getEventType();
  this -> eventManager -> registerDelegate(levelChangeDelegate, textLoader -> getString(string("IDS_SoundManager_LevelChange")),levelChangeEventType);

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
  vector<string>sound_paths={"IDS_Unit_Escape_Sound_Path",
                       "IDS_Level_Start_Sound_Path",
                       "IDS_Jazzy_Sound_Path",
                       "IDS_Tower_Creation_Sound_Path",
                       "IDS_Tower_Remove_Sound_Path",
                       "IDS_Failure_Sound_Path",
                       "IDS_Ding_Sound_Path",
                       "IDS_QFG_Win_Sound_Path"};
  vector<string>ids={"IDS_Unit_Escape_Noise",
                     "IDS_Level_Start_Noise",
                     "IDS_Jazzy_Noise",
                     "IDS_Tower_Creation_Noise",
                     "IDS_Tower_Remove_Noise",
                     "IDS_Failure_Noise",
                     "IDS_Ding_Noise",
                     "IDS_QFG_Win_Noise"};

  assert(sound_paths.size()==ids.size());

  for(int z=0;z<sound_paths.size();z++){
    loadSound(sound_paths[z],ids[z]);
  }
  //cout << textLoader->getString(("IDS_Combat_")+std::to_string(0)+string("_Music_Path")) << endl;


  for(int z=0;z<=5;z++){
    std::shared_ptr<sf::Music>music=make_shared<sf::Music>();
    assert(music->openFromFile(textLoader->getString(string("IDS_Combat_")+std::to_string(z)+string("_Music_Path"))));
    music->setLoop(true);
    music_objs[MusicType::Combat].push_back(music);
  }



}

void SoundManager::loadSound(string path, string soundID){
  string true_path=textLoader->getString(path);
  string id=textLoader->getString(soundID);
  //cout << "path" << textLoader->getString(path) << endl;
  assert(buffers[id].loadFromFile(true_path));

  //cout << "adding sound " << textLoader->getString(soundID) << endl;
  sound_objs[id].setBuffer(buffers[id]);
  //cout << sound_objs.count(textLoader->getString(soundID)) << endl;
}


void SoundManager::playSound(string soundID){
  //cout << "playing sound " << soundID << endl;
  assert(sound_objs.count(soundID));
  sound_objs[soundID].play();
}

void SoundManager::pauseSound(string soundID){
  sound_objs[soundID].pause();
}

void SoundManager::stopSound(string soundID){
  sound_objs[soundID].stop();
}

void SoundManager::playMusic(){
  music_objs[playingType][playingIndex]->play();
}

void SoundManager::pauseMusic(){
  music_objs[playingType][playingIndex]->pause();
}

void SoundManager::stopMusic(){
  music_objs[playingType][playingIndex]->stop();

}

void SoundManager::startSongOfType(MusicType type){
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
  playSound(textLoader->getString("IDS_Level_Start_Noise"));
}

void SoundManager::handleTowerCreation(const EventInterface &event) {
  playSound(textLoader->getString("IDS_Tower_Creation_Noise"));
}

void SoundManager::handleTowerRemove(const EventInterface &event) {
  playSound(textLoader->getString("IDS_Tower_Remove_Noise"));
}

void SoundManager::handleWaveChange(const EventInterface & event){
  stopSound(textLoader->getString("IDS_Jazzy_Noise"));
  stopSound(textLoader->getString("IDS_QFG_Win_Noise"));


  const WaveChangeEvent* waveChangeEvent= static_cast<const WaveChangeEvent*>(&event);

  WaveChangeEventData* waveChangeEventData= static_cast<WaveChangeEventData*>((waveChangeEvent-> data).get());

  if(waveChangeEventData->waveStart){
    startSongOfType(MusicType::Combat);
  }else{
    stopMusic();
    if(playingIndex==3){
      playSound(textLoader->getString("IDS_QFG_Win_Noise"));
    }else{
      playSound(textLoader->getString("IDS_Jazzy_Noise"));
    }
  }
}