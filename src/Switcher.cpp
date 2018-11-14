#include "Switcher.hpp"
#include <string>
#include <memory>

using namespace std;

Switcher::Switcher(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader,int windowX, int windowY, int id, int len){
    this -> windowX = windowX;
    this -> windowY = windowY;
    this -> id = id;
    this -> selected = 0;

    this -> initText();
}

void Switcher::initText(){

    //get the path for the font
    string mainFontPath = textLoader -> getString(string("IDS_MFP"));

    //load the font
    if(!font.loadFromFile(mainFontPath)){
        cout << "No font!" << endl;
    }
    else{
        //cout << "loaded font!" << endl;
    }

    //construct the switcher based on the id passed to the constructor and use that to populate the options vector
    string path = "";

    switch(id) {
        case 0: string path = "IDS_Switcher_School_";
        case 1: string path = "IDS_Switcher_Population_";
        case 2: string path = "IDS_Switcher_Obstacles_";
        case 3: string path = "IDS_Switcher_Waves_";
        case 4: string path = "IDS_Switcher_Start_Money_";
        case 5: string path = "IDS_Switcher_Cafeteria_Size_";
    }

    //Iterate through the xml to populate the vector
    int i = 0;for(i < len){
                string option = textLoader -> getString(string(path + std::to_string(i))
                options.push_back(option);
    }
}


void Switcher::changeSelected(int direction){
    if(direction == 1){
        selected == (selected + 1) % len;

    }
    else{
        selected == selected % len;
        selected--;
        //OOB check
        selected = selected >= 0 ? selected: len + selected;
        selected = selected % len;
    }
    switcher::draw();
}
void Switcher::getSelected(){
    return selected;
}
void Switcher::getID(){
    return id;
}
void Switcher::draw(){
    getSelected();
    text.setString(options(selected))
    text.setPostion(sf::Vector2f((windowX / 4) * 3, (windowY / 7) * (id + 1)))


}