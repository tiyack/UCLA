#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();
    
    ~StudentWorld(); //destructor
    
    //helper functions
    bool loadBoard();
    
    //functions for actor
    bool squareExists(const int& x1, const int& y1);
    bool landed(int x, int y);
    
private:
    std::vector<Player*> m_player;
    std::vector<Actor*> m_container;

};

#endif // STUDENTWORLD_H_
