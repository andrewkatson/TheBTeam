#pragma once

/*
 * Loads in textures for all the towers,units,projectiles, and obstacles
 * stores each of them according to their id (defined in strings)
 * this allows for a clean and single use texture for all the different
 * objects (static is not as flexible as this)
 * @author Andrew Katson
 */
 #include "SFML/Graphics.hpp"
 #include <memory>
 #include <vector>
 #include "TextLoader.hpp"

 using std::to_string;
 using std::shared_ptr;
 using std::unique_ptr;
 using std::make_shared;
 using std::vector;
class TextureLoader{
private:
  //Store the textLoader to make requests for strings and constants
  shared_ptr<TextLoader> textLoader;
  //every texture used by any obstacle, projectile, unit, or tower (not no tower)
  //each typeID corresponds to shared pointer to a vector of textures used by
  //that class type
  unordered_map<string, shared_ptr<vector<sf::Texture>>> allTextures;
public:
  TextureLoader(shared_ptr<TextLoader> textLoader);

  void initTextures();

  shared_ptr<vector<sf::Texture>> getTexture(string typeID);

};
