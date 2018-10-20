/*
  SoundManager.cpp
  
  Purpose: Handle loading and playing of all game sounds through simple methods.
  
  @author Jeremy Elkayam
*/

#include "SoundManager.hpp"

SoundManager::SoundManager(){
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
       else
          stop the game and pull up a box saying you 'screwed' up (family friendly)

   */
}

void SoundManager::playSound(int dex){
  
}

void SoundManager::resumeSound(int dex){
  
}

void SoundManager::stopSound(int dex){

}
