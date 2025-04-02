// rabbits.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in the arena
const int MAXCOLS = 25;               // max number of columns in the arena
const int MAXRABBITS = 100;           // max number of rabbits allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_POISON = 1;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
  public:

      // Accessors
    int  col() const; //DONE
    bool isDead() const; //I THINK DONE

      // Mutators
    void move(); //MAYBE DONE?? QS

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_nCarrots;
    bool   m_moved;
      // TODO: needs additional
    //I THINK DONE
};

class Player
{
  public:

      // Accessors
    int  row() const; //DONE
    int  col() const; //DONE
    bool isDead() const; //I THINK DONE

      // Mutators
    string move(int dir); //MAYBE DONE?? QS
    void   setDead(); //I THINK DONE
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena(); //I THINK DONE

      // Accessors
    int     rows() const; //DONE
    int     cols() const; //DONE
    int     rabbitCount() const; //DONE
    int     numberOfRabbitsAt(int r, int c) const; //MAYBE DONE?? QS + check
    void    display(string msg) const; //MAYBE DONE?? QS

      // Mutators
    bool addRabbit(int r, int c); //MAYBE DONE?? QS
    void moveRabbits(); //I THINK DONE
};
///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

bool attemptMove(const Arena& a, int dir, int& r, int& c); //MAYBE DONE?? QS
bool recommendMove(const Arena& a, int r, int c, int& bestDir); //NEED TO DO


class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    string takePlayerTurn();
};



if (!attemptMove(*m_arena, dir, m_row, m_col)) //this should also update the pos so now --++ not needed //*m_arena?
    return "Player couldn't move; player stands.";
switch (dir){
    case 0: //north
        if (m_arena->numberOfRabbitsAt(m_row,m_col) != 0){
            setDead();
            return "Player walked into a rabbit and died.";
        }
        return "Player moved north.";
    case 1: //east
        if (m_arena-> numberOfRabbitsAt(m_row, m_col) != 0){
            setDead();
            return "Player walked into a rabbit and died.";
        }
        return "Player moved east.";
    case 2: //south
        if (m_arena-> numberOfRabbitsAt(m_row,m_col)){
            setDead();
            return "Player walked into a rabbit and died.";
        }
        return "Player moved south.";
    case 3: //west
        if (m_arena-> numberOfRabbitsAt(m_row ,m_col)){
            setDead();
            return "Player walked into a rabbit and died.";
        }
        return "Player moved west.";
}

