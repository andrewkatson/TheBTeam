#ifndef COMPVIEW_H
#define COMPVIEW_H

class CompView{
private:
public:
  CompView();

  void updateCompView(float deltaS);
  
  void attackEnemies();
  
  void moveUnits();
  
  void delegateEvents();

};

#endif