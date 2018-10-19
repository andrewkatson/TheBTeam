/*
  SoundManager.hpp
  
  Purpose: Handle loading and playing of all game sounds through simple methods.
  
  @author Jeremy Elkayam
*/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>

using namespace std;

class SoundManager{
public:

  //Stores 
  vector<sf::Music>music_objs;

  vector<sf::Sound>sound_objs;
  
private:

  SoundManager();
  
  void playSound();
  
  void resumeSound();

  void stopSound();
};

#endif
