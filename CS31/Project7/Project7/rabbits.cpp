// rabbits.cpp
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
#include <type_traits>
#include <cassert>
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
      // Constructor
    Rabbit(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_nCarrots;
    bool   m_moved;
      // TODO: You'll probably find that a rabbit object needs additional
      // data members to support your implementation of the behavior affected
      // by poisoned carrots.
};

class Player
{
  public:
      // Constructor
    Player(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    string dropPoisonedCarrot();
    string move(int dir);
    void   setDead();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
  public:
      // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();

      // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     rabbitCount() const;
    int     getCellStatus(int r, int c) const;
    int     numberOfRabbitsAt(int r, int c) const;
    void    display(string msg) const;

      // Mutators
    void setCellStatus(int r, int c, int status);
    bool addRabbit(int r, int c);
    bool addPlayer(int r, int c);
    void moveRabbits();

  private:
    int     m_grid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Rabbit* m_rabbits[MAXRABBITS];
    int     m_nRabbits;
    int     m_turns;

      // Helper functions
    void checkPos(int r, int c, string functionName) const;
    bool isPosInBounds(int r, int c) const;
};

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

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool decodeDirection(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Rabbit implementation
///////////////////////////////////////////////////////////////////////////

Rabbit::Rabbit(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A rabbit must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Rabbit created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_nCarrots = 0;
}

int Rabbit::row() const
{
    return m_row;
}

int Rabbit::col() const
{
      // TODO: DONE: TRIVIAL: Return what column the Rabbit is at
    return m_col;
}

bool Rabbit::isDead() const
{
    //cerr << "Checking for rabbit death\n";
      // TODO:  DONE: Return whether the Rabbit is dead
      if (m_nCarrots == 2)
          return true;
    return false;
}

void Rabbit::move()
{
      // TODO:  DONE:
      //   Return without moving if the rabbit has eaten one poisoned
      //   carrot (so is supposed to move only every other turn) and
      //   this is a turn it does not move.

      //   Otherwise, attempt to move in a random direction; if can't
      //   move, don't move.  If it lands on a poisoned carrot, eat the
      //   carrot and remove it from the game (so it is no longer on that
      //   grid point).
    if (m_nCarrots == 0){
        m_moved = true;
        int moveDir = randInt(0, NUMDIRS - 1);
//        switch(moveDir){
//            case 0: cerr << "Moving north\n"; break;
//            case 1: cerr << "Moving east\n"; break;
//            case 2: cerr << "Moving south\n"; break;
//            case 3: cerr << "Moving west\n";
//        }
        //cerr << "row " << m_row << " col " << m_col << endl;
        if (!attemptMove(*m_arena, moveDir, m_row, m_col)) return;//this should also update the pos so now --++ not needed //*m_arena?
        //cerr << "after row " << m_row << " col " << m_col << endl;
        if(m_arena->getCellStatus(m_row, m_col) == HAS_POISON){
           // cerr << "Ate carrot!\n";
            m_nCarrots++;
            m_arena->setCellStatus(m_row, m_col, EMPTY);
        }
    }
    else if (m_nCarrots == 1 && m_moved == true){ //TO SKIP A TURN
      //  cerr << "Skipped a turn for rabbit on row " << m_row << " and col " << m_col <<  endl;
        m_moved = false;
        return;
    }
    else if (m_nCarrots == 1 && m_moved == false){
        m_moved = true;
        int moveDir = randInt(0, NUMDIRS-1);
        if (!attemptMove(*m_arena, moveDir, m_row, m_col)) return;//this should also update the pos so now --++ not needed //*m_arena?
        else
            if(m_arena->getCellStatus(m_row, m_col) == HAS_POISON){
                //cerr << "Ate carrot!\n";
                m_nCarrots++;
                m_arena->setCellStatus(m_row, m_col, EMPTY);
            }
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
      // TODO: DONE: TRIVIAL:  Return what row the Player is at
    return m_row;
}

int Player::col() const
{
      // TODO: DONE: TRIVIAL:  Return what column the Player is at
    return m_col;
}

string Player::dropPoisonedCarrot()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_POISON)
        return "There's already a poisoned carrot at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_POISON);
    return "A poisoned carrot has been dropped.";
}

string Player::move(int dir)
{
      // TODO: DONE: Attempt to move the player one step in the indicated
      //        direction.  If this fails,
      //        return "Player couldn't move; player stands."
      //        A player who moves onto a rabbit, and this
      //        returns "Player walked into a rabbit and died."
      //        Otherwise, return one of "Player moved north.",
      //        "Player moved east.", "Player moved south.", or
      //        "Player moved west."
    if (!attemptMove(*m_arena, dir, m_row, m_col)) //this should also update the pos so now --++ not needed
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
    return "Player couldn't move; player stands.";
}

bool Player::isDead() const
{
      // TODO: DONE: Return whether the Player is dead
    if (m_dead)
        return true;
    return false;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nRabbits = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    // TODO: DONE: Deallocate the player and all remaining dynamically allocated
    //        rabbits.
    delete m_player;
    for (int i = 0; i < m_nRabbits; i++)
        delete m_rabbits[i];
}

int Arena::rows() const
{
      // TODO: DONE: TRIVIAL:  Return the number of rows in the arena
    return m_rows;
}

int Arena::cols() const
{
      // TODO: DONE: TRIVIAL:  Return the number of columns in the arena
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::rabbitCount() const
{
      // TODO: DONE: TRIVIAL:  Return the number of rabbits in the arena
    return m_nRabbits;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c, "Arena::getCellStatus");
    return m_grid[r-1][c-1];
}

int Arena::numberOfRabbitsAt(int r, int c) const
{
      // TODO: DONE: Return the number of rabbits at row r, column c
      // Delete the following line and replace it with the correct code.
    
    int count = 0;
    for (int i = 0; i < rabbitCount(); i++){
        if (m_rabbits[i]->row() == r && m_rabbits[i]->col() == c){
            //cerr << "Found rabbit on " << r << " and " << c <<  endl;
            count++;
        }
    }
    return count;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (poisoned carrots)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

      // Indicate each rabbit's position
      // TODO: DONE:  If one rabbit is at some grid point, set the displayGrid char
      //        to 'R'.  If it's 2 though 8, set it to '2' through '8'.
      //        For 9 or more, set it to '9'.
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++){
            if (numberOfRabbitsAt(r, c) == 1)
                displayGrid[r-1][c-1] = 'R';
            else if (numberOfRabbitsAt(r, c) >= 9)
                displayGrid[r-1][c-1] = '9';
            else if (numberOfRabbitsAt(r, c) > 1 && numberOfRabbitsAt(r, c) < 9)
                displayGrid[r-1][c-1] = (numberOfRabbitsAt(r, c) + '0');
        }

      // Indicate the player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, rabbit, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << rabbitCount() << " rabbits remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c, "Arena::setCellStatus");
    m_grid[r-1][c-1] = status;
}

bool Arena::addRabbit(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a rabbit on a spot with a poisoned carrot
    if (getCellStatus(r, c) != EMPTY)
        return false;

      // Don't add a rabbit on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

      // If there are MAXRABBITS existing rabbits, return false.  Otherwise,
      // dynamically allocate a new rabbit at coordinates (r,c).  Save the
      // pointer to newly allocated rabbit and return true.

      // TODO: DONE: Implement this.
    if (rabbitCount() >= MAXRABBITS)
        return false;
    m_rabbits[m_nRabbits] = new Rabbit(this, r, c);
    //cerr << "Creadted new rabbit at " << r << " " << c << endl;
    m_nRabbits++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (! isPosInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a rabbit
    if (numberOfRabbitsAt(r, c) > 0)
        return false;

    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveRabbits()
{
      // Move all rabbits
      // TODO: DONE: Move each rabbit.  Mark the player as dead if necessary.
      //        Deallocate any dead dynamically allocated rabbit.
    for (int i = 0; i < m_nRabbits; i++){
        if (m_rabbits[i]->isDead()){
            delete m_rabbits[i];
          //  cerr << "delete 1" << endl;
            for (int k = i; k < m_nRabbits - 1; k++){
                m_rabbits[k] = m_rabbits[k+1];
             //   cerr << "shifting " << m_rabbits[k] << " is now " << m_rabbits[k+1] << endl;
            }
            m_rabbits[m_nRabbits - 1] = nullptr;
            m_nRabbits--;
            i--;
         //   cerr << "Reduced rabbit to " << m_nRabbits << endl;
        }
    }
    for (int i = 0; i < m_nRabbits; i++){
       // cerr << i << endl;
        m_rabbits[i]->move();
        if (m_rabbits[i]->row() == m_player->row() && m_rabbits[i]->col() == m_player->col())
            m_player->setDead();
        if (m_rabbits[i]->isDead()){
            delete m_rabbits[i];
         //               cerr << "delete 1" << endl;
         //   cerr << "There are " << m_nRabbits << " rabbits\n";
            for (int k = i; k < m_nRabbits - 1; k++){
                m_rabbits[k] = m_rabbits[k+1];
         //       cerr << "shiting " << m_rabbits[k] << " is now " << m_rabbits[k+1] << endl;
          //      cerr << "Number " << k << " became " << k+1 << endl;
            }
            m_rabbits[m_nRabbits - 1] = nullptr;
            m_nRabbits--;
            i--;
          //  cerr << "Reduced rabbit to " << m_nRabbits << endl;
        }
    }
      //0,24,49,73
      // Another turn has been taken
    m_turns++;
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nRabbits)
{
    if (nRabbits < 0)
    {
        cout << "***** Cannot create Game with negative number of rabbits!" << endl;
        exit(1);
    }
    if (nRabbits > MAXRABBITS)
    {
        cout << "***** Trying to create Game with " << nRabbits
             << " rabbits; only " << MAXRABBITS << " are allowed!" << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nRabbits - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
             << cols << " arena, which is too small too hold a player and "
             << nRabbits << " rabbits!" << endl;
        exit(1);
    }

      // Create arena
    m_arena = new Arena(rows, cols);

      // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);

      // Populate with rabbits
    while (nRabbits > 0)
    {
        int r = randInt(1, rows);
       // cerr << "Generating row for rabbit\n";
        int c = randInt(1, cols);
       // cerr << "Generating col for rabbit\n";
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addRabbit(r, c);
        //cerr << "Did addRabbit\n";
        nRabbits--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/c or nothing): ";
        string playerMove;
        getline(cin, playerMove);

        Player* player = m_arena->player();
        int dir;

        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropPoisonedCarrot();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'c')
                return player->dropPoisonedCarrot();
            else if (decodeDirection(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/c." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->rabbitCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        m_arena->moveRabbits();
        m_arena->display(msg); //IS THIS MAKING IT DOUBLE?
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

  // Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(lowest, highest);
    return distro(generator);
}

bool decodeDirection(char ch, int& dir)
{
    switch (tolower(ch))
    {
      default:  return false;
      case 'n': dir = NORTH; break;
      case 'e': dir = EAST;  break;
      case 's': dir = SOUTH; break;
      case 'w': dir = WEST;  break;
    }
    return true;
}

  // Return false without changing anything if moving one step from (r,c)
  // in the indicated direction would run off the edge of the arena.
  // Otherwise, update r and c to the position resulting from the move and
  // return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    // TODO: DONE: Implement this function
    // Delete the following line and replace it with the correct code.
    switch (dir){
        case 0: //north
         //   cerr << "OG row is " << r << endl;
            if (r-1 < 1)
                return false;
        //    cerr << "Row is " << r;
            r--;
        //    cerr << "MOVED NORTH ROW IS NOW " << r << endl;
            return true;
        case 1: //east
        //    cerr << "OG col is " << c << endl;
            if (c+1 > a.cols())
                return false;
        //    cerr << c;
       //     cerr << "Col is " << c;
            c++;
       //     cerr << "MOVED east col IS NOW " << c << endl;
            return true;
        case 2: //south
        //    cerr << "OG row is " << r << endl;
            if (r+1 > a.rows())
                return false;
          //  cerr << "Row is " << r;
            r++;
            //cerr << "MOVED south ROW IS NOW " << r << endl;
            return true;
        case 3: //west
         //   cerr << "OG col is " << c << endl;
            if (c-1 < 1)
                return false;
           // cerr << "Col is " << c;
            c--;
         //   cerr << "MOVED east col IS NOW " << c << endl;
            return true;
    }
    return false;
}

  // Recommend a move for a player at (r,c):  A false return means the
  // recommendation is that the player should drop a poisoned carrot and
  // not move; otherwise, this function sets bestDir to the recommended
  // direction to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // TODO: DONE: Implement this function
    // Delete the following line and replace it with your code.
    int rabbitN = -1;
    int rabbitS = -1;
    int rabbitE = -1;
    int rabbitW = -1;
    int stayCount = 0;
    
    if (r-1 >= 1  &&  r-1 <= a.rows()  &&  c >= 1  &&  c <= a.cols()){ //IF NORTH Exists
        rabbitN = a.numberOfRabbitsAt(r-1, c);
        stayCount += a.numberOfRabbitsAt(r-1, c);
        cerr << "North exists & rabbitN is " << rabbitN << " stayCount is " << stayCount << endl;
    }
    if (r+1 >= 1  &&  r+1 <= a.rows()  &&  c >= 1  &&  c <= a.cols()){ //IF SOUTH Exists
        rabbitS = a.numberOfRabbitsAt(r+1, c);
        stayCount += a.numberOfRabbitsAt(r+1, c);
        cerr << "South exists & rabbitS is " << rabbitS << " stayCount is " << stayCount << endl;
    }
    if (r >= 1  &&  r <= a.rows()  &&  c-1 >= 1  &&  c-1 <= a.cols()){ //IF WEST Exists
        rabbitW = a.numberOfRabbitsAt(r, c-1);
        stayCount += a.numberOfRabbitsAt(r, c-1);
        cerr << "West exists & rabbitW is " << rabbitW << " stayCount is " << stayCount << endl;
    }
    if (r >= 1  &&  r <= a.rows()  &&  c+1 >= 1  &&  c+1 <= a.cols()){ //IF EAST Exists
        rabbitE = a.numberOfRabbitsAt(r, c+1);
        stayCount += a.numberOfRabbitsAt(r, c+1);
        cerr << "East exists & rabbitE is " << rabbitE << " stayCount is " << stayCount << endl;
    }
    if (rabbitN > 0 && rabbitS > 0 && rabbitE > 0 && rabbitW > 0){ //IF SURROUNDED
        return false;
    }
    if (rabbitN == 0 && rabbitS == 0 && rabbitE == 0 && rabbitW == 0){ //NO RABBITS AROUND
        return false;
    }
    int nCount = -2;;
    if (rabbitN == 0){
        nCount = 0;
        //EAST
        if (r-1 >= 1  &&  r-1 <= a.rows()  &&  c+1 >= 1  &&  c+1 <= a.cols()){ //east exists
            nCount += a.numberOfRabbitsAt(r-1, c+1);
            cerr << "There are " << nCount << " rabbits near north\n";
        }
        //WEST
        if (r-1 >= 1  &&  r-1 <= a.rows()  &&  c-1 >= 1  &&  c-1 <= a.cols()){ //west exists
            nCount += a.numberOfRabbitsAt(r-1, c-1);
            cerr << "There are " << nCount << " rabbits near north\n";
        }
        //NORTH
        if (r-2 >= 1  &&  r-2 <= a.rows()  &&  c >= 1  &&  c <= a.cols()){ //north exists
            nCount += a.numberOfRabbitsAt(r-2, c);
            cerr << "There are " << nCount << " rabbits near north\n";
        }
    }
    int sCount = -2;
    if (rabbitS == 0){
        sCount = 0;
        //EAST
        if (r+1 >= 1  &&  r+1 <= a.rows()  &&  c+1 >= 1  &&  c+1 <= a.cols()){ //east exists
            sCount += a.numberOfRabbitsAt(r-1, c+1);
            cerr << "There are " << sCount << " rabbits near south\n";
        }
        //WEST
        if (r+1 >= 1  &&  r+1 <= a.rows()  &&  c-1 >= 1  &&  c-1 <= a.cols()){ //west exists
            sCount += a.numberOfRabbitsAt(r-1, c-1);
            cerr << "There are " << sCount << " rabbits near south\n";
        }
        //SOUTH
        if (r+2 >= 1  &&  r+2 <= a.rows()  &&  c >= 1  &&  c <= a.cols()){ //south exists
            sCount += a.numberOfRabbitsAt(r+2, c);
            cerr << "There are " << sCount << " rabbits near south\n";
        }
    }
    int eCount = -2;
    if (rabbitE == 0){
        eCount = 0;
        //NORTH
        if (r-1 >= 1  &&  r-1 <= a.rows()  &&  c+1 >= 1  &&  c+1 <= a.cols()){ //north exists
            eCount += a.numberOfRabbitsAt(r-1, c+1);
            cerr << "There are " << eCount << " rabbits near east\n";
        }
        //EAST
        if (r >= 1  &&  r <= a.rows()  &&  c+2 >= 1  &&  c+2 <= a.cols()){ //east exists
            eCount += a.numberOfRabbitsAt(r, c+2);
            cerr << "There are " << eCount << " rabbits near east\n";
        }
        //SOUTH
        if (r+1 >= 1  &&  r+1 <= a.rows()  &&  c+1 >= 1  &&  c+1 <= a.cols()){ //south exists
            eCount += a.numberOfRabbitsAt(r+1, c+1);
            cerr << "There are " << eCount << " rabbits near east\n";
        }
    }
    int wCount = -2;
    if (rabbitW == 0){
        wCount = 0;
        //NORTH
        if (r-1 >= 1  &&  r-1 <= a.rows()  &&  c-1 >= 1  &&  c-1 <= a.cols()){ //north exists
            wCount += a.numberOfRabbitsAt(r-1, c-1);
            cerr << "There are " << wCount << " rabbits near west\n";
        }
        //WEST
        if (r >= 1  &&  r <= a.rows()  &&  c-2 >= 1  &&  c-2 <= a.cols()){ //east exists
            wCount += a.numberOfRabbitsAt(r, c-2);
            cerr << "There are " << wCount << " rabbits near west\n";
        }
        //SOUTH
        if (r+1 >= 1  &&  r+1 <= a.rows()  &&  c-1 >= 1  &&  c-1 <= a.cols()){ //south exists
            wCount += a.numberOfRabbitsAt(r+1, c-1);
            cerr << "There are " << wCount << " rabbits near west\n";
        }
    }
    if (nCount < 0)
        nCount = 2000;
    if (sCount < 0)
        sCount = 2000;
    if (eCount < 0)
        eCount = 2000;
    if (wCount < 0)
        wCount = 2000;
    
    if (stayCount <= nCount && stayCount <= sCount && stayCount <= wCount && stayCount <= eCount){
        //staying is best
        cerr << "Staying is best\n";
        return false;
    }
    if (nCount <= stayCount && nCount <= sCount && nCount <= eCount && nCount <= wCount){
        //north is best
        bestDir = 0;
        cerr << "North is best\n";
        return true;
    }
    if (sCount <= stayCount && sCount <= nCount && sCount <= eCount && sCount <= wCount){
        //south is best
        bestDir = 2;
        cerr << "South is best\n";
        return true;
    }
    if (eCount <= stayCount && eCount <= sCount && eCount <= nCount && eCount <= wCount){
        //east is best
        bestDir = 1;
        cerr << "East is best\n";
        return true;
    }
    if (wCount <= stayCount && wCount <= sCount && wCount <= eCount && wCount <= nCount){
        //west is best
        bestDir = 3;
        cerr << "West is best\n";
        return true;
    }
    
    return false;
}
      // Your replacement implementation should do something intelligent.
      // You don't have to be any smarter than the following, although
      // you can if you want to be:  If staying put runs the risk of a
      // rabbit possibly moving onto the player's location when the rabbits
      // move, yet moving in a particular direction puts the player in a
      // position that is safe when the rabbits move, then the chosen
      // action is to move to a safer location.  Similarly, if staying put
      // is safe, but moving in certain directions puts the player in
      // danger of dying when the rabbits move, then the chosen action should
      // not be to move in one of the dangerous directions; instead, the player
      // should stay put or move to another safe position.  In general, a
      // position that may be moved to by many rabbits is more dangerous than
      // one that may be moved to by few.
      //
      // Unless you want to, you do not have to take into account that a
      // rabbit might be poisoned and thus sometimes less dangerous than one
      // that is not.  That requires a more sophisticated analysis that
      // we're not asking you to do.

//
//#define CHECKTYPE(c, f, r, a)  \
//    static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
//       "FAILED: You changed the type of " #c "::" #f);  \
//    { [[gnu::unused]] auto p = static_cast<r (c::*) a>(&c::f); }
//
//void thisFunctionWillNeverBeCalled()
//{
//      // If the student deleted or changed the interfaces to the public
//      // functions, this won't compile.  (This uses magic beyond the scope
//      // of CS 31.)
//
//    Rabbit r(static_cast<Arena*>(0), 1, 1);
//    CHECKTYPE(Rabbit, row, int, () const);
//    CHECKTYPE(Rabbit, col, int, () const);
//    CHECKTYPE(Rabbit, isDead, bool, () const);
//    CHECKTYPE(Rabbit, move, void, ());
//
//    Player p(static_cast<Arena*>(0), 1, 1);
//    CHECKTYPE(Player, row, int, () const);
//    CHECKTYPE(Player, col, int, () const);
//    CHECKTYPE(Player, isDead, bool, () const);
//    CHECKTYPE(Player, dropPoisonedCarrot, string, ());
//    CHECKTYPE(Player, move, string, (int));
//    CHECKTYPE(Player, setDead, void, ());
//
//    Arena a(1, 1);
//    CHECKTYPE(Arena, rows, int, () const);
//    CHECKTYPE(Arena, cols, int, () const);
//    CHECKTYPE(Arena, player, Player*, () const);
//    CHECKTYPE(Arena, rabbitCount, int, () const);
//    CHECKTYPE(Arena, getCellStatus, int, (int,int) const);
//    CHECKTYPE(Arena, numberOfRabbitsAt, int, (int,int) const);
//    CHECKTYPE(Arena, display, void, (string) const);
//    CHECKTYPE(Arena, setCellStatus, void, (int,int,int));
//    CHECKTYPE(Arena, addRabbit, bool, (int,int));
//    CHECKTYPE(Arena, addPlayer, bool, (int,int));
//    CHECKTYPE(Arena, moveRabbits, void, ());
//
//    Game g(1,1,1);
//    CHECKTYPE(Game, play, void, ());
//}
//
//void findTheRabbit(const Arena& a, int& r, int& c)
//{
//    if      (a.numberOfRabbitsAt(r-1, c) == 1) r--;
//    else if (a.numberOfRabbitsAt(r+1, c) == 1) r++;
//    else if (a.numberOfRabbitsAt(r, c-1) == 1) c--;
//    else if (a.numberOfRabbitsAt(r, c+1) == 1) c++;
//    else assert(false);
//}
//
//void surroundWithPoison(Arena& a, int r, int c)
//{
//    a.setCellStatus(r-1, c, HAS_POISON);
//    a.setCellStatus(r+1, c, HAS_POISON);
//    a.setCellStatus(r, c-1, HAS_POISON);
//    a.setCellStatus(r, c+1, HAS_POISON);
//}
//
//void doBasicTests()
//{
//    {
//        Arena a(10, 20);
//        assert(a.addPlayer(2, 5));
//        Player* pp = a.player();
//        assert(pp->row() == 2  &&  pp->col() == 5  && ! pp->isDead());
//        assert(pp->move(NORTH) == "Player moved north.");
//        assert(pp->row() == 1  &&  pp->col() == 5  && ! pp->isDead());
//        assert(pp->move(NORTH) == "Player couldn't move; player stands.");
//        assert(pp->row() == 1  &&  pp->col() == 5  && ! pp->isDead());
//        pp->setDead();
//        assert(pp->row() == 1  &&  pp->col() == 5  && pp->isDead());
//    }
//    {
//        Arena a(10, 20);
//        int r = 8;
//        int c = 18;
//        assert(a.addPlayer(r, c));
//        for (int k = 0; k < MAXRABBITS/4; k++)
//        {
//            assert(a.addRabbit(r-1, c));
//            assert(a.addRabbit(r+1, c));
//            assert(a.addRabbit(r, c-1));
//            assert(a.addRabbit(r, c+1));
//        }
//        assert(! a.player()->isDead());
//        a.moveRabbits();
//        assert(a.player()->isDead());
//    }
//    {
//        Arena a(10, 20);
//        int r = 4;
//        int c = 4;
//        assert(a.addRabbit(r, c));
//        surroundWithPoison(a, r, c);
//        assert(a.addPlayer(8, 18));
//        assert(a.rabbitCount() == 1  &&  a.numberOfRabbitsAt(r, c) == 1);
//        a.moveRabbits(); //eats carrot
//        assert(a.rabbitCount() == 1  &&  a.numberOfRabbitsAt(r, c) == 0);
//        findTheRabbit(a, r, c);
//        assert(a.getCellStatus(r, c) != HAS_POISON);
//        a.moveRabbits(); //skips turn
//        assert(a.rabbitCount() == 1  &&  a.numberOfRabbitsAt(r, c) == 1);
//        a.moveRabbits(); //moves but could eat carrot and die?
//        assert(a.rabbitCount() == 1  &&  a.numberOfRabbitsAt(r, c) == 0); //THIS
//        findTheRabbit(a, r, c);
//        a.moveRabbits(); //skips turn
//        assert(a.rabbitCount() == 1  &&  a.numberOfRabbitsAt(r, c) == 1);
//        surroundWithPoison(a, r, c);
//        a.moveRabbits();
//        assert(a.rabbitCount() == 0  &&  a.numberOfRabbitsAt(r, c) == 0); //HERE
//        assert(a.numberOfRabbitsAt(r-1, c) == 0);
//        assert(a.numberOfRabbitsAt(r+1, c) == 0);
//        assert(a.numberOfRabbitsAt(r, c-1) == 0);
//        assert(a.numberOfRabbitsAt(r, c+1) == 0);
//    }
//    {
//        Arena a(20, 20);
//        assert(a.addPlayer(1, 20));
//        struct Coord
//        {
//            int r;
//            int c;
//        };
//        assert(MAXRABBITS == 100);
//        const int NDOOMED = 4;
//        Coord doomed[NDOOMED];
//        for (int k = 0; k < NDOOMED; k++)
//        {
//            doomed[k].r = 3;
//            doomed[k].c = 5*k+3;
//            assert(a.addRabbit(doomed[k].r, doomed[k].c));
//            surroundWithPoison(a, doomed[k].r, doomed[k].c);
//            for (int i = 0; i < MAXRABBITS/NDOOMED - 1; i++)
//                assert(a.addRabbit(20, 20));
//        }
//        assert(!a.addRabbit(20, 20));
//        assert(a.rabbitCount() == MAXRABBITS);
//        a.moveRabbits();
//        assert(a.rabbitCount() == MAXRABBITS);
//        for (int k = 0; k < NDOOMED; k++)
//        {
//            findTheRabbit(a, doomed[k].r, doomed[k].c);
//            surroundWithPoison(a, doomed[k].r, doomed[k].c);
//        }
//        a.moveRabbits();
//        assert(a.rabbitCount() == MAXRABBITS);
//        a.moveRabbits(); //HERE
//        assert(a.rabbitCount() == MAXRABBITS - NDOOMED); //HERE
//        for (int k = 0; k < NDOOMED; k++)
//            assert(a.addRabbit(20, 20));
//        assert(!a.addRabbit(20, 20));
//          // If the program crashes after leaving this compound statement, you
//          // are probably messing something up when you delete a rabbit after
//          // it dies (or you have mis-coded the destructor).
//          //
//          // Draw a picture of your m_rabbits array before the rabbits move,
//          // and also note the values of m_nRabbits or any other variable you
//          // might have that's involved with the number of rabbits.  Trace
//          // through your code step by step as the rabbits move and die,
//          // updating the picture according to what the code says, not what
//          // you want it to do.  If you don't see a problem then, try tracing
//          // through the destruction of the arena.
//          //
//          // If you execute the code, use the debugger to check on the values
//          // of key variables at various points.  If you didn't try to learn
//          // to use the debugger, insert statements that write the values of
//          // key variables to cerr so you can trace the execution of your code
//          // and see the first place where something has gone amiss.
//    }
//    cout << "Passed all basic tests (as long as when run under g31 there is no further message after this)." << endl;
//}
///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

//int main()
//{
//    //doBasicTests(); // Remove this line after completing test.
//       //return 0;       // Remove this line after completing test.
//      // Create a game
//      // Use this instead to create a mini-game:
//    //Game g(3, 5, 2);
//    Game g(10, 12, 40);
//
//      // Play the game
//    g.play();
//}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#include <windows.h>

void clearScreen()
{
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    GetConsoleScreenBufferInfo(hConsole, &csbi);
//    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
//    COORD upperLeft = { 0, 0 };
//    DWORD dwCharsWritten;
//    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
//                                                        &dwCharsWritten);
//    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
//    static const char* term = getenv("TERM");
//    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
//        cout << endl;
//    else
//    {
//        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
//        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
//    }
}

#endif



//    switch (dir){
//        case 0: //north
//            if (m_arena-> numberOfRabbitsAt(m_row-- ,m_col)){
//                m_row--;
//                setDead();
//                return "Player walked into a rabbit and died.";
//            }//HOW TO CHECK IF RABBIT?
//            if (m_row-- < 1) //attemptMove?
//                return "Player couldn't move; player stands.";
//            m_row--;
//            return "Player moved north.";
//        case 1: //east
//            if (m_arena-> numberOfRabbitsAt(m_row, m_col++)){
//                m_col++;
//                setDead();
//                return "Player walked into a rabbit and died.";
//            }
//            if (m_col++ > MAXCOLS)
//                return "Player couldn't move; player stands.";
//            m_col++;
//            return "Player moved east.";
//        case 2: //south
//            if (m_arena-> numberOfRabbitsAt(m_row++ ,m_col)){
//                m_row++;
//                setDead();
//                return "Player walked into a rabbit and died.";
//            }
//            if (m_row++ > MAXROWS)
//                return "Player couldn't move; player stands.";
//            m_row++;
//            return "Player moved south.";
//        case 3: //west
//            if (m_arena-> numberOfRabbitsAt(m_row ,m_col--)){
//                m_col--;
//                setDead();
//                return "Player walked into a rabbit and died.";
//            }
//            if (m_col-- < 1)
//                return "Player couldn't move; player stands.";
//            m_col--;
//            return "Player moved west.";
//    }




////IF ONLY ONE RABBIT NEAR U
//    //check for rabbit at NORTH
//    if (r-1 >= 1  &&  r-1 <= a.rows()  &&  c >= 1  &&  c <= a.cols())
//    if (a.numberOfRabbitsAt(r-1, c) > 0){
//        //moving east
//        if (a.numberOfRabbitsAt(r-1, c+1) == 0 && a.numberOfRabbitsAt(r, c+2) == 0 && a.numberOfRabbitsAt(r+1, c+1) == 0){ //if east is completely safe thne move here
//            if (a.numberOfRabbitsAt(r, c+1) == 0){
//                bestDir = 1; //EAST
//                return true;
//            }
//        }
//        //moving south
//        if (a.numberOfRabbitsAt(r+2, c) == 0 && a.numberOfRabbitsAt(r+1, c+1) == 0 && a.numberOfRabbitsAt(r+1, c-1) == 0){//if south is completely safe thne move
//            if (a.numberOfRabbitsAt(r+1, c) == 0){
//                bestDir = 2;
//                return true;
//            }
//        }
//        //moving west
//        if (a.numberOfRabbitsAt(r+1, c-1) == 0 && a.numberOfRabbitsAt(r, c-2) == 0 && a.numberOfRabbitsAt(r-1, c-1) == 0){
//            if (a.numberOfRabbitsAt(r, c-1) == 0){
//                bestDir = 3;
//                return true;
//            }
//        }
//    }
//    //check for rabbit at SOUTH
//    if (r+1 >= 1  &&  r+1 <= a.rows()  &&  c >= 1  &&  c <= a.cols())
//    if (a.numberOfRabbitsAt(r+1, c) > 0){
//        //moving east
//        if (a.numberOfRabbitsAt(r-1, c+1) == 0 && a.numberOfRabbitsAt(r, c+2) == 0 && a.numberOfRabbitsAt(r+1, c+1) == 0){ //if east is completely safe thne move here
//            if (a.numberOfRabbitsAt(r, c+1) == 0){
//                bestDir = 1; //EAST
//                return true;
//            }
//        }
//        //moving north
//        if (a.numberOfRabbitsAt(r-2, c) == 0 && a.numberOfRabbitsAt(r-1, c+1) == 0 && a.numberOfRabbitsAt(r-1, c-1) == 0){//if north is completely safe thne move
//            if (a.numberOfRabbitsAt(r-1, c)){
//                bestDir = 0;
//                return true;
//            }
//        }
//        //moving west
//        if (a.numberOfRabbitsAt(r+1, c-1) == 0 && a.numberOfRabbitsAt(r, c-2) == 0 && a.numberOfRabbitsAt(r-1, c-1) == 0){
//            if (a.numberOfRabbitsAt(r, c-1) == 0){
//                bestDir = 3;
//                return true;
//            }
//        }
//    }
//    //check for rabbit at EAST
//    if (r >= 1  &&  r <= a.rows()  &&  c+1 >= 1  &&  c+1 <= a.cols())
//    if (a.numberOfRabbitsAt(r, c+1) > 0){
//        //moving south
//        if (a.numberOfRabbitsAt(r+2, c) == 0 && a.numberOfRabbitsAt(r+1, c+1) == 0 && a.numberOfRabbitsAt(r+1, c-1) == 0){//if south is completely safe thne move
//            if (a.numberOfRabbitsAt(r+1, c) == 0){
//                bestDir = 2;
//                return true;
//            }
//        }
//        //moving north
//        if (a.numberOfRabbitsAt(r-2, c) == 0 && a.numberOfRabbitsAt(r-1, c+1) == 0 && a.numberOfRabbitsAt(r-1, c-1) == 0){//if north is completely safe thne move
//            if (a.numberOfRabbitsAt(r-1, c)){
//                bestDir = 0;
//                return true;
//            }
//        }
//        //moving west
//        if (a.numberOfRabbitsAt(r+1, c-1) == 0 && a.numberOfRabbitsAt(r, c-2) == 0 && a.numberOfRabbitsAt(r-1, c-1) == 0){
//            if (a.numberOfRabbitsAt(r, c-1) == 0){
//                bestDir = 3;
//                return true;
//            }
//        }
//    }
//    //check for rabbit at WEST
//    if (r >= 1  &&  r <= a.rows()  &&  c-1 >= 1  &&  c-1 <= a.cols())
//    if (a.numberOfRabbitsAt(r, c-1) > 0){
//        //moving south
//        if (a.numberOfRabbitsAt(r+2, c) == 0 && a.numberOfRabbitsAt(r+1, c+1) == 0 && a.numberOfRabbitsAt(r+1, c-1) == 0){//if south is completely safe thne move
//            if (a.numberOfRabbitsAt(r+1, c) == 0){
//                bestDir = 2;
//                return true;
//            }
//        }
//        //moving north
//        if (a.numberOfRabbitsAt(r-2, c) == 0 && a.numberOfRabbitsAt(r-1, c+1) == 0 && a.numberOfRabbitsAt(r-1, c-1) == 0){//if north is completely safe thne move
//            if (a.numberOfRabbitsAt(r-1, c)){
//                bestDir = 0;
//                return true;
//            }
//        }
//        //moving east
//        if (a.numberOfRabbitsAt(r-1, c+1) == 0 && a.numberOfRabbitsAt(r, c+2) == 0 && a.numberOfRabbitsAt(r+1, c+1) == 0){ //if east is completely safe thne move here
//            if (a.numberOfRabbitsAt(r, c+1) == 0){
//                bestDir = 1; //EAST
//                return true;
//            }
//        }
//    }
////IF rabbit nowhere near you
//    if (a.numberOfRabbitsAt(r+1, c) == 0 && a.numberOfRabbitsAt(r-1, c) == 0 && a.numberOfRabbitsAt(r, c+1) == 0 && a.numberOfRabbitsAt(r, c-1) == 0){
//        return false;
//    }
////IF MORE THAN ONE RABBIT NEAR YOU
//    int dangerCount = 0;
//    if (a.numberOfRabbitsAt(r+1, c) != 0){
//        dangerCount = a.numberOfRabbitsAt(r+1, c);
//    }


#include <iostream>
#include <sstream>
#include <streambuf>
#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <cassert>
using namespace std;

class StreambufSwitcher
{
  public:
    StreambufSwitcher(ios& dest, streambuf* sb,
                                        ios::iostate exceptions = ios::goodbit)
     : dest_stream(dest), oldsb(dest.rdbuf(sb)), oldex(dest.exceptions())
    { dest_stream.exceptions(exceptions); }
    StreambufSwitcher(ios& dest, ios& src)
     : StreambufSwitcher(dest, src.rdbuf(), src.exceptions())
    {}
    ~StreambufSwitcher()
    { dest_stream.rdbuf(oldsb); dest_stream.exceptions(oldex); }
  private:
    ios& dest_stream;
    streambuf* oldsb;
    ios::iostate oldex;
};

map<void*, size_t> allocMap;
bool recordaddrs = false;

inline bool isRecordedSize(size_t n)
{
    return n == sizeof(Rabbit)  ||  n == sizeof(Player);
}

void* operator new(size_t n)
{
    void* p = malloc(n);
    fill_n(static_cast<char*>(p), n, 0xca);
    if (recordaddrs  &&  isRecordedSize(n))
    {
        recordaddrs = false;
        allocMap.insert(make_pair(p, n));
        recordaddrs = true;
    }
    return p;
}

void unrecordaddr(void* p)
{
    recordaddrs = false;
    auto it = allocMap.find(p);
    if (it != allocMap.end())
    {
        fill_n(static_cast<char*>(p), it->second, 0xcb);
        allocMap.erase(it);
    }
    recordaddrs = true;
}

#if __cplusplus >= 201402L  &&  ! defined(__clang__)
// Unless clang is supplied the -fsized-deallocation flag, it will
// not call the C++14/17 sized operator delete.

void operator delete(void* p) noexcept
{
    free(p);
}

void operator delete(void* p, size_t n) noexcept
{
    if (recordaddrs  &&  isRecordedSize(n))
        unrecordaddr(p);
    operator delete(p);
}
#else
void operator delete(void* p) noexcept
{
    if (recordaddrs)
        unrecordaddr(p);
    free(p);
}
#endif

bool recommendMove(const Arena& a, int r, int c, int& bestDir);

void testone(int n)
{
    StreambufSwitcher sso(cout, cerr);

        switch (n)
        {
                                 default: {
                cout << "Bad argument" << endl;
                        } break; case  1: {
        int k;
        for (k = 0; k < 300; k++)
        {
            Arena a(1, 20);
            a.addPlayer(1, 3);
            Rabbit r(&a, 1, 18);
            assert(r.row() == 1  &&  r.col() == 18);
            r.move(); assert(r.row() == 1);
            if (r.col() != 19)
            {
                assert(r.col() == 17  ||  r.col() == 18);
                continue;
            }
            r.move(); assert(r.row() == 1);
            if (r.col() == 20)
                break;
            assert(r.col() == 18  ||  r.col() == 19);
        }
        assert(k < 300);
                        } break; case  2: {
        int k;
        for (k = 0; k < 600; k++)
        {
            Arena a(1, 20);
            a.addPlayer(1, 3);
            Rabbit r(&a, 1, 19);
            assert(r.row() == 1  &&  r.col() == 19);
            r.move(); assert(r.row() == 1);
            if (r.col() != 19)
            {
                assert(r.col() == 18  ||  r.col() == 20);
                continue;
            }
            r.move(); assert(r.row() == 1);
            if (r.col() != 19)
            {
                assert(r.col() == 18  ||  r.col() == 20);
                continue;
            }
            r.move(); assert(r.row() == 1);
            if (r.col() != 19)
            {
                assert(r.col() == 18  ||  r.col() == 20);
                continue;
            }
            r.move(); assert(r.row() == 1);
            if (r.col() != 19)
            {
                assert(r.col() == 18  ||  r.col() == 20);
                continue;
            }
            r.move(); assert(r.row() == 1);
            if (r.col() == 18  ||  r.col() == 20)
                break;
            assert(r.col() == 19);
        }
        assert(k < 600);
                        } break; case  3: {
        int k;
        for (k = 0; k < 600; k++)
        {
            Arena a(20, 1);
            a.addPlayer(3, 1);
            Rabbit r(&a, 19, 1);
            assert(r.row() == 19  &&  r.col() == 1);
            r.move(); assert(r.col() == 1);
            if (r.row() != 19)
            {
                assert(r.row() == 18  ||  r.row() == 20);
                continue;
            }
            r.move(); assert(r.col() == 1);
            if (r.row() != 19)
            {
                assert(r.row() == 18  ||  r.row() == 20);
                continue;
            }
            r.move(); assert(r.col() == 1);
            if (r.row() != 19)
            {
                assert(r.row() == 18  ||  r.row() == 20);
                continue;
            }
            r.move(); assert(r.col() == 1);
            if (r.row() != 19)
            {
                assert(r.row() == 18  ||  r.row() == 20);
                continue;
            }
            r.move(); assert(r.col() == 1);
            if (r.row() == 18  ||  r.row() == 20)
                break;
            assert(r.row() == 19);
        }
        assert(k < 600);
                        } break; case  4: {
        Arena a(10,20);
        a.addPlayer(9, 19);
        for (int rr = 5-2; rr <= 5+2; rr++)
            for (int cc = 10-2; cc <= 10+2; cc++)
                a.setCellStatus(rr, cc, HAS_POISON);
        Rabbit r(&a, 5, 10);
        r.move();
        assert((r.row() == 5  &&  abs(r.col() - 10) == 1)  ||
               (r.col() == 10  &&  abs(r.row() - 5) == 1));
        int oldr = r.row();
        int oldc = r.col();
        r.move();
        assert(r.row() == oldr  &&  r.col() == oldc);
        r.move();
        assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
               (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
            } break; case  5: {
        Arena a(10,20);
        a.addPlayer(9, 19);
        for (int rr = 5-2; rr <= 5+2; rr++)
            for (int cc = 10-2; cc <= 10+2; cc++)
                if (rr != 5  ||  cc != 10)
                    a.setCellStatus(rr, cc, HAS_POISON);
        Rabbit r(&a, 5, 10);
        assert(!r.isDead());
        r.move();
        assert((r.row() == 5  &&  abs(r.col() - 10) == 1)  ||
               (r.col() == 10  &&  abs(r.row() - 5) == 1));
        int oldr = r.row();
        int oldc = r.col();
        assert(!r.isDead());
        a.setCellStatus(5, 10, HAS_POISON);
        r.move();
        assert(r.row() == oldr  &&  r.col() == oldc);
        assert(!r.isDead());
        r.move();
        assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
               (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
        assert(r.isDead());
            } break; case  6: {
        Arena a(10,20);
        a.addPlayer(9, 19);
        a.setCellStatus(4, 10, HAS_POISON);
        a.setCellStatus(6, 10, HAS_POISON);
        a.setCellStatus(5, 9, HAS_POISON);
        a.setCellStatus(5, 11, HAS_POISON);
        Rabbit r(&a, 5, 10);
        r.move();
        assert((r.row() == 5  &&  abs(r.col() - 10) == 1)  ||
               (r.col() == 10  &&  abs(r.row() - 5) == 1));
        int oldr = r.row();
        int oldc = r.col();
        r.move();
        assert(r.row() == oldr  &&  r.col() == oldc);
        r.move();
        assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
               (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
        oldr = r.row();
        oldc = r.col();
        r.move();
        assert(r.row() == oldr  &&  r.col() == oldc);
        a.setCellStatus(oldr-1, oldc, EMPTY);
        a.setCellStatus(oldr+1, oldc, EMPTY);
        a.setCellStatus(oldr, oldc-1, EMPTY);
        a.setCellStatus(oldr, oldc+1, EMPTY);
        r.move();
        assert((r.row() == oldr  &&  abs(r.col() - oldc) == 1)  ||
               (r.col() == oldc  &&  abs(r.row() - oldr) == 1));
                        } break; case  7: {
        Arena a(1, 20);
        a.addPlayer(1, 3);
        Player* p = a.player();
        assert(p->row() == 1  &&  p->col() == 3);
        p->move(WEST); assert(p->row() == 1  &&  p->col() == 2);
        p->move(WEST); assert(p->row() == 1  &&  p->col() == 1);
                        } break; case  8: {
        Arena a(1, 20);
        a.addPlayer(1, 3);
        Player* p = a.player();
        p->move(WEST); assert(p->row() == 1  &&  p->col() == 2);
        p->move(WEST); assert(p->row() == 1  &&  p->col() == 1);
        p->move(WEST); assert(p->row() == 1  &&  p->col() == 1);
        p->move(NORTH); assert(p->row() == 1  &&  p->col() == 1);
        p->move(SOUTH); assert(p->row() == 1  &&  p->col() == 1);
                        } break; case  9: {
        Arena a(10, 20);
        a.addPlayer(3, 6);
        Player* p = a.player();
        assert( ! p->isDead());
        p->setDead();
        assert(p->isDead());
                        } break; case 10: {
        Arena a(20, 1);
        a.addPlayer(1, 1);
        Player* p = a.player();
        assert(p->move(WEST).find(" stands") != string::npos);
        assert(p->move(EAST).find(" stands") != string::npos);
        assert(p->move(NORTH).find(" stands") != string::npos);
        assert(p->move(SOUTH).find(" south") != string::npos);
                        } break; case 11: {
        Arena a(20, 1);
        a.addPlayer(1, 1);
        Player* p = a.player();
        a.addRabbit(2, 1);
        assert(p->move(SOUTH).find(" died") != string::npos);
                        } break; case 12: {
        Arena a(20, 1);
        a.addPlayer(1, 1);
        Player* p = a.player();
        a.addRabbit(2, 1);
        assert(!p->isDead());
        p->move(SOUTH);
        assert(p->isDead());
                        } break; case 13: {
        Arena a(6, 15);
        assert(a.rows() == 6  &&  a.cols() == 15);
                        } break; case 14: {
        Arena a(10, 20);
        a.addPlayer(3, 6);
        a.addRabbit(7, 5);
        assert(a.numberOfRabbitsAt(7, 5) == 1  &&  a.rabbitCount() == 1);
                        } break; case 15: {
        Arena a(10, 20);
        a.addPlayer(3, 6);
        a.addRabbit(7, 5);
        a.addRabbit(4, 7);
        a.addRabbit(7, 5);
        assert(a.numberOfRabbitsAt(7, 5) == 2  &&  a.rabbitCount() == 3);
                        } break; case 16: {
        Arena a(1, 20);
        a.addPlayer(1, 8);
        a.addRabbit(1, 1);
        a.setCellStatus(1, 2, HAS_POISON);
        a.setCellStatus(1, 3, HAS_POISON);
        a.addRabbit(1, 16);
        a.setCellStatus(1, 14, HAS_POISON);
        a.setCellStatus(1, 15, HAS_POISON);
        a.setCellStatus(1, 17, HAS_POISON);
        a.setCellStatus(1, 18, HAS_POISON);
        assert(a.rabbitCount() == 2);
        int k;
        for (k = 0; k < 200; k++)
        {
            a.moveRabbits();
            int nb1 = (a.getCellStatus(1, 2) == HAS_POISON) +
                  (a.getCellStatus(1, 3) == HAS_POISON);
            int nb2 = (a.getCellStatus(1, 14) == HAS_POISON) +
                  (a.getCellStatus(1, 15) == HAS_POISON) +
                  (a.getCellStatus(1, 17) == HAS_POISON) +
                  (a.getCellStatus(1, 18) == HAS_POISON);
            assert(a.rabbitCount() == (nb1 > 0) + (nb2 > 2));
            if (a.rabbitCount() == 0)
                break;
        }
        assert(k < 200);
                        } break; case 17: {
        Arena a(1, 3);
        a.addPlayer(1, 1);
        Player* p = a.player();
        for (int j = 0; j < 10; j++)
            a.addRabbit(1, 3);
        assert(!p->isDead());
        a.moveRabbits();
        int k;
        for (k = 0; k < 100; k++)
        {
            assert(!p->isDead());
            a.moveRabbits();
            if (a.numberOfRabbitsAt(1, 1) > 0)
            {
                assert(p->isDead());
                break;
            }
        }
        assert(k < 100);
                        } break; case 18: {
        ostringstream oss;
        StreambufSwitcher sso2(cout, oss);
        Arena a(2, 3);
        a.addPlayer(2, 3);
        a.addRabbit(2, 1);
        a.addRabbit(2, 1);
        a.addRabbit(2, 2);
        a.display("");
        assert(oss.str().find("2R@") != string::npos);
                        } break; case 19: {
        ostringstream oss;
        StreambufSwitcher sso2(cout, oss);
        Arena a(2, 3);
        a.addPlayer(2, 3);
        for (int k = 1; k <= 20; k++)
            a.addRabbit(2, 1);
        a.display("");
        assert(oss.str().find("9.@") != string::npos);
                        } break; case 20: {
        recordaddrs = true;
        int n = allocMap.size();
        {
            Arena a(20, 20);
            for (int r = 1; r <= 5; r++)
                for (int c = 11; c <= 20; c++)
                    a.setCellStatus(r, c, HAS_POISON);
            for (int r = 16; r <= 20; r++)
                for (int c = 15; c <= 20; c++)
                    a.setCellStatus(r, c, HAS_POISON);
            a.addPlayer(19, 19);
            int n2 = allocMap.size();
            a.setCellStatus(3, 13, EMPTY);
            a.setCellStatus(3, 18, EMPTY);
            a.addRabbit(3, 13);
            a.addRabbit(3, 18);
            for (int k = 0; k < 4; k++)
            {
                a.addRabbit(1, 1);
                a.addRabbit(1, 4);
                a.addRabbit(4, 1);
                a.addRabbit(4, 4);
            }
            assert(allocMap.size() >= n2 + 18);
            a.moveRabbits();
            a.setCellStatus(3, 13, HAS_POISON);
            a.setCellStatus(3, 18, HAS_POISON);
            a.moveRabbits();
            a.moveRabbits();
            assert(a.rabbitCount() == 18-2);
            for (int k = a.rabbitCount(); k < MAXRABBITS; k++)
                assert(a.addRabbit(1, 1));
            int j;
            for (j = 0; j < 1000  &&  a.rabbitCount() > 20; j++)
            {
                for (int r = 1; r <= 20; r++)
                    for (int c = 1; c <= 20; c++)
                        if (a.numberOfRabbitsAt(r, c) == 0  &&  !(r == 19 && c == 19))
                            a.setCellStatus(r, c, HAS_POISON);
                a.moveRabbits();
            }
            assert(j < 1000);
            a.setCellStatus(1, 1, EMPTY);
            for (int k = a.rabbitCount(); k < MAXRABBITS; k++)
                assert(a.addRabbit(1, 1));
            assert(allocMap.size() >= n2 + MAXRABBITS);
        }
        assert(allocMap.size() == n);
        recordaddrs = false;
                        } break; case 21: {
        Arena a(20, 20);
        a.addPlayer(19, 19);
        for (int r = 1; r < 19; r++)
            for (int c = 1; c < 19; c++)
                if (r != 10  ||  c != 10)
                    a.setCellStatus(r, c, HAS_POISON);
        for (int k = 0; k < 100; k++)
            a.addRabbit(10, 10);
        assert(a.rabbitCount() == 100  &&  a.numberOfRabbitsAt(10, 10) == 100);
        int nr[1+20][1+20];
        a.moveRabbits();
        int tot = 0;
        for (int r = 1; r < 19; r++)
        {
            for (int c = 1; c < 19; c++)
            {
                nr[r][c] = a.numberOfRabbitsAt(r, c);
                tot += nr[r][c];
                assert((r == 10  &&  c >= 9 && c <= 11) ||
                       (c == 10  &&  r >= 9 && r <= 11) ||
                       nr[r][c] == 0);
            }
        }
        assert(nr[10][10] == 0  &&  tot == a.rabbitCount());
        assert(nr[9][10] == 0  ||  a.getCellStatus(9, 10) == EMPTY);
        assert(nr[11][10] == 0  ||  a.getCellStatus(11, 10) == EMPTY);
        assert(nr[10][9] == 0  ||  a.getCellStatus(10, 9) == EMPTY);
        assert(nr[10][11] == 0  ||  a.getCellStatus(10, 11) == EMPTY);
        a.setCellStatus(10, 10, HAS_POISON);
        a.moveRabbits();
        assert(a.numberOfRabbitsAt(9, 10) == (nr[9][10] == 0 ? 0 : 1));
        assert(a.numberOfRabbitsAt(11, 10) == (nr[11][10] == 0 ? 0 : 1));
        assert(a.numberOfRabbitsAt(10, 9) == (nr[10][9] == 0 ? 0 : 1));
        assert(a.numberOfRabbitsAt(10, 11) == (nr[10][11] == 0 ? 0 : 1));
        for (int k = 0; k < 17; k++)
        {
            for (int r = 1; r < 19; r++)
                for (int c = 1; c < 19; c++)
                    if (a.numberOfRabbitsAt(r, c) == 0)
                        a.setCellStatus(r, c, HAS_POISON);
            a.moveRabbits();
        }
        tot = 0;
        for (int r = 1; r < 19; r++)
            for (int c = 1; c < 19; c++)
                tot += a.numberOfRabbitsAt(r, c);
        assert(a.rabbitCount() == tot  &&  tot < 100);
                        } break; case 22: {
        Arena a(4, 2);
        a.addPlayer(1, 1);
        Player* p = a.player();
        a.addRabbit(4, 2);
        for (int k = 0; k < 10000 &&  ! a.player()->isDead()  &&
                         a.rabbitCount() != 0; k++)
        {
            int dir;
            if (recommendMove(a, p->row(), p->col(), dir))
                p->move(dir);
            else
                p->dropPoisonedCarrot();
            a.moveRabbits();
        }
        assert(! a.player()->isDead()  &&  a.rabbitCount() == 0);
                        } break; case 23: {
        Arena a(10, 10);
        a.addPlayer(6, 6);
        a.addRabbit(5, 6);
        a.addRabbit(7, 6);
        a.addRabbit(6, 7);
        int dir;
        assert(recommendMove(a, 6, 6, dir)  &&  dir == WEST);
                        } break; case 24: {
        Arena a(10, 10);
        a.addPlayer(6, 6);
        a.addRabbit(4, 6);
        a.addRabbit(5, 7);
        a.addRabbit(6, 8);
        a.addRabbit(7, 7);
        a.addRabbit(8, 6);
        a.addRabbit(7, 5);
        a.addRabbit(6, 4);
        a.addRabbit(5, 5);
        int dir;
        assert(!recommendMove(a, 6, 6, dir));
                        } break; case 25: {
        Arena a(2, 3);
        a.addPlayer(1, 2);
        a.addRabbit(1, 1);
        for (int k = 0; k < 10; k++)
            a.addRabbit(2, 3);
        int dir;
        assert(!recommendMove(a, 1, 2, dir));
                        } break; case 26: {
        Arena a(3, 2);
        a.addPlayer(3, 1);
        a.addRabbit(1, 1);
        for (int k = 0; k < 10; k++)
            a.addRabbit(3, 2);
        int dir;
        assert(recommendMove(a, 3, 1, dir)  &&  dir == NORTH);
                        } break;
    }
}

int main()
{
    cout << "Enter test number (1-26): ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed!" << endl;
}
