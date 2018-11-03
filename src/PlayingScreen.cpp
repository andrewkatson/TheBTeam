#include "PlayingScreen.hpp"


PlayingScreen::PlayingScreen(shared_ptr<EventManager> eventManager,shared_ptr<TextLoader> textLoader, shared_ptr<GameLogic> gameLogic, int windowX, int windowY){
  this -> windowX = windowX;
  this -> windowY = windowY;
  this -> eventManager = eventManager;
  this -> textLoader = textLoader;
  this -> gameLogic = gameLogic;
  somethingChanged = true;
  this -> registerDelegates();
}

/*
 * Register the delegate method for this class
 * with any events it needs to know about
 */
void PlayingScreen::registerDelegates(){
  //bind our delegate function for tower creation events
  EventManager::EventDelegate towerCreationEventDelegate = std::bind(&PlayingScreen::handleTowerCreation, this, _1);

  //make an event and get its type
  TowerCreationEvent towerCreationEvent = TowerCreationEvent();
  EventType towerCreationEventType = towerCreationEvent.getEventType();
  //register the delegate and its type
  this -> eventManager -> registerDelegate(towerCreationEventDelegate,
  textLoader -> getString(string("IDS_PS_TC")),towerCreationEventType);
}


void PlayingScreen::draw(sf::RenderWindow &window){
  //TODO change into real code for drawing the map!
  if(somethingChanged){
    cout << endl << "THE FLOOR " << endl;
    const vector<vector<int>> floor = gameLogic -> getFloor();
    printVector(floor);

    cout << endl << "ABOVE THE FLOOR" << endl;
    const vector<vector<int>> aboveFloor = gameLogic -> getAboveFloor();
    printVector(aboveFloor);

    cout << endl << "DISTANCES " << endl;
    const vector<vector<int>> distances = gameLogic -> getDistances();
    printVector(distances);

    somethingChanged = false;
  }

}
/*
 * Handle any tower creation
 * @param event: event of the tower creation
 */
void PlayingScreen::handleTowerCreation(const EventInterface& event){
  /*
   * cast the EventInterface reference to a CONST pointer to the
   * TowerCreationEvent type which allows us to access variables and methods
   * specific to TowerCreationEvent
   */
  const TowerCreationEvent* tcEvent = static_cast<const TowerCreationEvent*>(&event);
  /*
   * cast the "data" (a EventDataInterface) to a TowerCreationEventData type
   * the .get() is because data is a unique_ptr and we need to grab the
   * raw pointer inside of it for this
   */
  TowerCreationEventData* tcEventData = static_cast<TowerCreationEventData*>((tcEvent -> data).get());

  somethingChanged = true;
}

template <class T>
void PlayingScreen::printVector(const vector<vector<T>> &v){
  //cout << " here !" << endl;
  for(const vector<int> vec : v){
    for(auto it = vec.begin(); it != vec.end(); ++it){
      if(*it < 0){
        cout << *it << " ";
      }
      else{
        cout << *it << "  ";
      }
    }
    cout << endl;
  }
  cout <<endl;
}
