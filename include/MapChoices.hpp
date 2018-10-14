#ifndef MAPCHOICES_H
#define MAPCHOICES_H

class MapChoices {
public:
  //number of obstacles on the board
  int obstacleChoice;
  //the specific level of school (lower numbers are easier)
  int cafeteriaChoice;
  //higher values will make the path length longer
  int pathLengthChoice;
  //number of entries on the board
  int pathEntryChoice;

  MapChoices(int obstacles, int cafeteria, int pathLength, int entries);
};

#endif
