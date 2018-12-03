#include "Switcher.hpp"
#include <string>
#include <memory>

using namespace std;

Switcher::Switcher(shared_ptr<EventManager> eventManager, shared_ptr<TextLoader> textLoader,int windowX, int windowY, int id, int len){
    this -> windowX = windowX;
    this -> windowY = windowY;
    this -> id = id;
    this -> len = len;
    this -> selected = 0;
    this -> textLoader = textLoader;
    this -> initText();
}

void Switcher::initText(){
    //get the path for the font
    string mainFontPath = textLoader -> getString(string("IDS_Title_Font_Path"));

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
        case 0:  path = "IDS_Switcher_School_";
                break;
        case 1:  path = "IDS_Switcher_Population_";
                break;
        case 2:  path = "IDS_Switcher_Obstacles_";
                break;
        case 3:  path = "IDS_Switcher_Meal_";
                break;
        case 4:  path = "IDS_Switcher_Start_Money_";
                break;
        case 5:  path = "IDS_Switcher_Cafeteria_Size_";
                break;
    }

    //Iterate through the xml to populate the vector
    int i = 0;
    for(i= 0;i < len;i++){
        string option = textLoader -> getString(path + std::to_string(i));
        options.push_back(option);
    }

}


void Switcher::changeSelected(int direction){
    //direction = 1, should be called as moveRight, and 0 should be called as moveLeft
    if(direction == 1){
        selected = ((selected + 1) % len);

    }
    else{
        selected == selected % len;
        selected--;
        //OOB check
        selected = selected >= 0 ? selected: len + selected;
        selected = selected % len;
        
    }
}
int Switcher::getSelected(){
    return selected;
}
int Switcher::getID(){
    return id;
}
void Switcher::draw(sf::RenderWindow &window){
    getSelected();
    this -> text.setString(options.at(selected));
    this -> text.setFillColor(sf::Color::White);
    this -> text.setCharacterSize(15);
    this -> text.setFont(font);
    this -> text.setPosition(sf::Vector2f((((windowX / 4) * 3)), (windowY / 7) * (id + 1)));
    window.draw(this -> text);
}
