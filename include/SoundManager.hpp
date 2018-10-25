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
#include <memory>

using namespace std;

class SoundManager{
private:

  //Stores game objects referencing streaming music.
  vector<sf::Music>music_objs;

  //Stores game objects referencing pre-loaded sounds.
  vector<sf::Sound>sound_objs;

  //event manager (used to register, deregister from events, and create them)
  shared_ptr<EventManager> eventManager;

  /*
    A SoundBuffer to keep all of the game's sounds loaded into memory before
    they're played.
  */
  sf::SoundBuffer buffer;

public:

  /*
    Constructor for the SoundManager class. Initializes the Music and Sound
    vectors with all their needed sounds and links the sounds to a central
    buffer.
   */
  SoundManager(shared_ptr<EventManager> eventManager);

  void delegateMethod(const EventInterface& event);

  /*
    Play the sound stored at the given index in sound_objs.

    @param dex the index in sound_objs where the sound is stored.
   */
  void playSound(int dex);

  /*
    Pause the music from music_objs at the given index if it is currently
    playing. Remembers the current place in the music, so that when the music is
    played next, it will play from where it was paused.

    @param dex the index in sound_objs where the sound is stored.
   */
  void pauseSound(int dex);

  /*
    Stop the music from music_objs at the given index if it is currently
    playing. Discards the current place in the music, so that when the music is
    played next, it will play from the beginning.

    @param dex the index in sound_objs where the sound is stored.
   */
  void stopSound(int dex);

  /*
    Play the music stored at the given index in music_objs.

    @param dex the index in music_objs where the music is stored.
   */
  void playMusic(int dex);

  /*
    Pause the music from music_objs at the given index if it is currently
    playing. Remembers the current place in the music, so that when the music is
    played next, it will play from where it was paused.

    @param dex the index in music_objs where the music is stored.
   */
  void pauseMusic(int dex);

  /*
    Stop the music from music_objs at the given index if it is currently
    playing. Discards the current place in the music, so that when the music is
    played next, it will play from the beginning.

    @param dex the index in music_objs where the music is stored.
   */
  void stopMusic(int dex);
};

#endif
