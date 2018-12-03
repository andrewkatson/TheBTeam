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
  vector<string>paths={"IDS_Unit_Escape_Sound_Path","IDS_Level_Start_Sound_Path","IDS_Jazzy_Sound_Path"};
  vector<string>ids={"IDS_Unit_Escape_Noise","IDS_Level_Start_Noise","IDS_Jazzy_Noise"};

  assert(paths.size()==ids.size());

  for(int z=0;z<paths.size();z++){
    loadSound(paths[z],ids[z]);
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

void SoundManager::playMusic(string musicID){
  music_objs[musicID].play();
}

void SoundManager::pauseMusic(string musicID){
  music_objs[musicID].pause();

}

void SoundManager::stopMusic(string musicID){
  music_objs[musicID].stop();

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