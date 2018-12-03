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

  if(!buffer.loadFromFile(textLoader->getString("IDS_Unit_Escape_Sound_Path"))){
    //you fucked up
  }

  sound_objs[textLoader->getString("IDS_Unit_Escape_Noise")].setBuffer(buffer);

}


void SoundManager::playSound(string soundID){
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
