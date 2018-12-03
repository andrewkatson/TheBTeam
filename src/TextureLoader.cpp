#include "TextureLoader.hpp"


TextureLoader::TextureLoader(shared_ptr<TextLoader> textLoader){
  this->textLoader=textLoader;
  initTextures();
}

/*
 * Load all the textures used by the game for any unit, tower, obstacle, or projectile
 * into the unordered map of textures
 */
void TextureLoader::initTextures(){
  //get all the type ids for the system
  unordered_map<string,string> allTypeIDS = textLoader -> getAllTypeIDS();

  /*
   * Iterate through all the typeIDS and append a number increasing from 0
   * if we get a "No String" that means that there is no texture path so
   * we stop loading in textures
   */
  for(auto iterator = allTypeIDS.begin(); iterator != allTypeIDS.end(); ++iterator){
    //the current type id
    string currentTypeID = (*iterator).second;

    //the number to append to the end of the typeidstring
    int texturePathCounter = 0;
    //will be used to store the path of the texture file we add
    string texturePathString = "";
    //combine the IDS designation with the type id
    string baseTypeIDString = "IDS_" + currentTypeID + "_";

    //add an entry into the map for this type id
    shared_ptr<vector<sf::Texture>> typeIDTextures = make_shared<vector<sf::Texture>>();
    allTextures.insert({currentTypeID, typeIDTextures});

    //we break inside the loop whenever a texturePathString does not
    //return a valid path
    while(true){
      //make a new path string using the base type id with the counter at the end
      //ex: ../resources/sprites/projectile/cheezpizz/slice.png
      // using IDS_Cheese_Pizza_Projectile_0
      texturePathString = textLoader->getString(baseTypeIDString + string(to_string(texturePathCounter)));
      //if this is not a valid path we break
      if(texturePathString == "String not found"){
        break;
      }

      sf::Texture textureToAdd;
      //load the texture specified by the current path string
      textureToAdd.loadFromFile(texturePathString);
      textureToAdd.setSmooth(true);
      //add it to the vector of textures for the current type
      allTextures.at(currentTypeID) -> push_back(textureToAdd);
      //increment to the next texture path
      texturePathCounter++;
    }
  }
}


/*
 * @param typeID: the string identifier for the class requesting its textures
 * @return a pointer to a vector of all the textures used by a class
 */
shared_ptr<vector<sf::Texture>> TextureLoader::getTexture(string typeID){
  //if the typeID has textures
  if(allTextures.find(typeID) != allTextures.end()){
    return allTextures.at(typeID);
  }
  return NULL;
}
