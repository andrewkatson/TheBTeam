/*
 * WaveManager.cpp
 *
 * Purpose: Handle loading and playing of all game sounds through simple methods.
 *
 * @author Jeremy Elkayam
*/

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include "Player.hpp"
#include "TextLoader.hpp"
#include "Events/PlaySoundEvent.hpp"

#include <memory>
#include <vector>
#include <cassert>
#include <random>
#include <map>

using std::string;
using std::vector;

class SoundManager{
private:

  //Stores game objects referencing streaming music.
  std::unordered_map<int,vector<sf::Music*>>music_objs;

  //Stores game objects referencing pre-loaded sounds.
  std::unordered_map<std::string,sf::Sound>sound_objs;

  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  /*
    A SoundBuffer to keep all of the game's sounds loaded into memory before
    they're played.
  */
  std::unordered_map<string,sf::SoundBuffer>buffers;

  void loadSound(string path, string soundID);

  int playingType;
  unsigned int playingIndex;

  const int COMBAT=0;
  const int PREP=1;
  const int WIN=2;

  std::random_device rd;

  bool newLevel;

public:

  /*
    Constructor for the SoundManager class. Initializes the Music and Sound
    vectors with all their needed sounds and links the sounds to a central
    buffer.
   */
  SoundManager(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader);
  ~SoundManager();
  void registerDelegates();
  void deregisterDelegates();

  void loadSounds();


  /*
    Play the sound stored at the given index in sound_objs.

    @param dex the index in sound_objs where the sound is stored.
   */
  void playSound(string soundID);

  /*
    Pause the music from music_objs at the given index if it is currently
    playing. Remembers the current place in the music, so that when the music is
    played next, it will play from where it was paused.

    @param dex the index in sound_objs where the sound is stored.
   */
  void pauseSound(string soundID);

  /*
    Stop the music from music_objs at the given index if it is currently
    playing. Discards the current place in the music, so that when the music is
    played next, it will play from the beginning.

    @param dex the index in sound_objs where the sound is stored.
   */
  void stopSound(string soundID);

  /*
    Play the music stored at the given index in music_objs.

    @param dex the index in music_objs where the music is stored.
   */
  void playMusic();

  /*
    Pause the music from music_objs at the given index if it is currently
    playing. Remembers the current place in the music, so that when the music is
    played next, it will play from where it was paused.

    @param dex the index in music_objs where the music is stored.
   */
  void pauseMusic();

  /*
    Stop the music from music_objs at the given index if it is currently
    playing. Discards the current place in the music, so that when the music is
    played next, it will play from the beginning.

    @param dex the index in music_objs where the music is stored.
   */
  void stopMusic();

  void startSongOfType(int type);

  void handleSoundPlay(const EventInterface& event);

  void handleLevelChanged(const EventInterface& event);

  void handleTowerRemove(const EventInterface& event);

  void handleTowerCreation(const EventInterface& event);

  void handleWaveChange(const EventInterface & event);

};

#endif
