/*
  SoundManager.cpp

  Purpose: Handle loading and playing of all game sounds through simple methods.

  @author Jeremy Elkayam
*/

#include "SoundManager.hpp"

SoundManager::SoundManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader){
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
   this -> eventManager = eventManager;
   this -> textLoader = textLoader;
   this -> registerDelegates();
}

SoundManager::~SoundManager(){
  this -> deregisterDelegates();
}

void SoundManager::registerDelegates(){

}

void SoundManager::deregisterDelegates(){

}


void SoundManager::playSound(int dex){
  sound_objs[dex].play();
}

void SoundManager::pauseSound(int dex){
  sound_objs[dex].pause();
}

void SoundManager::stopSound(int dex){
  sound_objs[dex].stop();
}

void SoundManager::playMusic(int dex){
  music_objs[dex].play();
}

void SoundManager::pauseMusic(int dex){
  music_objs[dex].pause();

}

void SoundManager::stopMusic(int dex){
  music_objs[dex].stop();

}
