#include "Actor.h"
#include "StudentWorld.h"
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(StudentWorld* sw, int imageID, int startX, int startY,
             int startDirection, int depth, double size)
:GraphObject(imageID, startX, startY, startDirection, depth, size)
{
    cerr << "Actor created at " << startX << ", " << startY << endl;
    m_world = sw;
}

bool Actor::canMove(int dir)
{
    int newX, newY;
    getPositionInThisDirection(dir, SPRITE_WIDTH, newX, newY);
    cerr << "Checking " <<  newX << ", " << newY << endl;

    return (getWorld()->squareExists(newX, newY));
//    if (!getWorld()->squareExists(newX, newY))
//        return false;
//    return true;
}


Alive::Alive(StudentWorld* sw, int imageID, int startX, int startY, int state)
:Actor(sw, imageID, startX, startY)
{
    m_state = state;
    m_moveDir = right;
}

bool Alive::setState(int newState)
{
    if(newState > 2 || newState < 0)
        return false;
    return (m_state = newState);
}

bool Alive::setMoveDir(int newDir)
{
    cerr << "New direction is " << newDir << endl;
    if (newDir < 0)
        newDir = 360 - (-newDir % 360);
    m_moveDir = newDir % 360;
    return true;
}

Player::Player(StudentWorld* sw, int imageID, int startX, int startY)
:Alive(sw, imageID, startX, startY)
{
    m_playerNum = 1;
    m_stars = 0;
    m_coins = 0;
    m_numVortex = 0;
    m_ticks_to_move = 0;
}

void Player::doSomething()
{
    if(getState() == WAITING_TO_ROLL)
    {
        //[IMPLEMENT LATER] step a page 28

        int action = getWorld()->getAction(m_playerNum);
        switch (action)
        {
            case ACTION_ROLL:
                m_dieRoll = 1 + (rand() % 10);
                m_ticks_to_move = m_dieRoll * 8;
                setState(WALKING);
                break;
            
            case ACTION_FIRE: //[IMPLEMENT LATER] step d page 29
//Introduce a new Vortex projectile on the square directly in front of the Avatar in the Avatar's current walk direction.
                getWorld()->playSound(SOUND_PLAYER_FIRE);
                m_numVortex--;
                cerr << "Action Fire" << endl;
                break;
             
            default:
                return;
        }
    }

    if(getState() == WALKING)
    {
        //OPTION c
        if (!canMove(getMoveDir()) && m_ticks_to_move % 8 == 0)
        {
            cerr << "CANT MOVE " << endl;
            switch (getMoveDir()) {
                case left:
                case right:
                    if (canMove(up))
                        setMoveDir(up);
                    else
                        setMoveDir(down);
                    setDirection(right);
                    cerr << "entered switch" << endl;
                    break;
                    
                case up:
                case down:
                    if (canMove(right)) {
                        setMoveDir(right);
                        setDirection(right);
                    }
                    else {
                        setMoveDir(left);
                        setDirection(left);
                    }
                    cerr << "entered switch" << endl;
                    break;
            } //switch ends
            
        } //if cant move ends
        
        moveAtAngle(getMoveDir(), 2);
        cerr << "New position is " <<  getX() << ", " << getY() << endl;
        m_ticks_to_move--;
        if (m_ticks_to_move == 0)
            setState(WAITING_TO_ROLL);
    } //if walking state ends
    
} //dosomething ends



Baddie::Baddie(StudentWorld* sw, int imageID, int startX, int startY)
:Alive(sw, imageID, startX, startY, PAUSED)
{
    m_travelDist = 0;
    m_pauseCount = 180;
}

Square::Square(StudentWorld* sw, int imageID, int startX, int startY)
:Actor(sw, imageID, startX, startY, right, 1)
{
    //m_alive = true;
}

void Square::doSomething()
{
    
}

CoinSquare::CoinSquare(StudentWorld* sw, int imageID, int startX, int startY)
:Square(sw, imageID, startX, startY)
{
    m_alive = true;
}

StarSquare::StarSquare(StudentWorld* sw, int imageID, int startX, int startY)
:Square(sw, imageID, startX, startY)
{
    
}













//    switch (dir) {
//        case right:
//            getPositionInThisDirection(right, 16, newX, newY);
//            if ((newX / SPRITE_WIDTH > BOARD_WIDTH) || (newY / SPRITE_HEIGHT > BOARD_WIDTH))
//                return false;
//            break;
//
//        case up:
//            getPositionInThisDirection(up, 16, newX, newY);
//            if ((newX / SPRITE_WIDTH > BOARD_WIDTH) || (newY / SPRITE_HEIGHT > BOARD_WIDTH))
//                return false;
//            break;
//
//        case left:
//            getPositionInThisDirection(left, 16, newX, newY);
//            if ((newX / SPRITE_WIDTH < 0) || (newY / SPRITE_HEIGHT < 0))
//                return false;
//            break;
//
//        case down:
//            getPositionInThisDirection(down, 16, newX, newY);
//            if ((newX / SPRITE_WIDTH < 0) || (newY / SPRITE_HEIGHT < 0))
//                return false;
//            break;
//    }
//    return true;
//}
