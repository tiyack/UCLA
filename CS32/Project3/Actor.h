#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
//#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* sw, int imageID, int startX, int startY,
          int startDirection = right, int depth = 0, double size = 1.0);
    virtual ~Actor() {}; //Destructor
    
    //accessor
    StudentWorld* getWorld() {return m_world;}
    
    virtual void doSomething() = 0;
    
    //helper functions
    bool canMove (int dir);

private:
    StudentWorld* m_world;
};

class Alive: public Actor
{
public:
    
    static const int WAITING_TO_ROLL = 0;
    static const int WALKING = 1;
    static const int PAUSED = 2;
    
    Alive(StudentWorld* sw, int imageID, int startX, int startY, int state = WAITING_TO_ROLL);
    virtual ~Alive() {} //Destructor
    
    //mutator
    bool setState(int newState);
    bool setMoveDir (int newDir);
    
    //accessor
    int getState() {return m_state;}
    int getMoveDir() {return m_moveDir;}
    
private:
    int m_state;
    int m_moveDir;
};

class Player: public Alive
{
public:
    Player(StudentWorld* sw, int imageID, int startX, int startY);
    ~Player() {} //Destructor
    
    //functions
    virtual void doSomething();
    
    //accessor
    int nCoin() const {return m_coins;}
    int nStar() const {return m_stars;}
    int nVortex() const {return m_numVortex;}
    int nTicks() const {return m_ticks_to_move;}
    
    //mutator
    
    
private:
    int m_playerNum;
    int m_stars;
    int m_coins;
    int m_numVortex;
    int m_ticks_to_move;
    int m_dieRoll;
};

class Baddie: public Alive
{
public:
    Baddie(StudentWorld* sw, int imageID, int startX, int startY);
    ~Baddie() {} //Destructor
    
    //functions
    virtual void doSomething() {}
    
private:
    int m_travelDist;
    int m_pauseCount;
};

class Square: public Actor
{
public:
    Square(StudentWorld* sw, int imageID, int startX, int startY);
    ~Square() {} //Destructor
    
    //functions
    virtual void doSomething();
    
private:
    bool m_alive;
};


#endif // ACTOR_H_
