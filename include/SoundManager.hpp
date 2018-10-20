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

  //Stores game objects referencing streaming music.
  vector<sf::Music>music_objs;

  //Stores game objects referencing pre-loaded sounds.
  vector<sf::Sound>sound_objs;

  /*
    A SoundBuffer to keep all of the game's sounds loaded into memory before
    they're played.
  */
  sf::SoundBuffer buffer;
  
private:

  /*
    Constructor for the SoundManager class. Initializes the Music and Sound
    vectors with all their needed sounds and links the sounds to a central
    buffer.
   */
  SoundManager();

  /*
    Play the sound stored at the given index in sound_objs.
    
    @param dex the index in sound_objs where the sound is stored.
   */
  void playSound(int dex);

  /*
    Resume the sound from sound_objs at the given index from the point at which
    it was last stopped.

    [potential redundancy with playsound?]

    @param dex the index in sound_objs where the sound is stored.
   */
  void resumeSound(int dex);

  /*
    Stop the sound from sound_objs at the given index if it is currently
    playing.
    
    @param dex the index in sound_objs where the sound is stored.
   */
  void stopSound(int dex);

  /*
    Play the music stored at the given index in music_objs.
    
    @param dex the index in music_objs where the music is stored.
   */
  void playMusic(int dex);

  /*
    Resume the music from music_objs at the given index from the point at which
    it was last stopped.

    [potential redundancy with playMusic?]

    @param dex the index in music_objs where the music is stored.
   */
  void resumeMusic(int dex);

  /*
    Stop the music from music_objs at the given index if it is currently
    playing.
    
    @param dex the index in music_objs where the music is stored.
   */
  void stopMusic(int dex);
};

#endif
