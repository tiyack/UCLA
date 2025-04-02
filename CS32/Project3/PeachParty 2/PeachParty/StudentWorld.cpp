#include "StudentWorld.h"
#include "GameConstants.h"
#include "Board.h"
#include <string>
#include <vector>

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    loadBoard();
	startCountdownTimer(99);  // this placeholder causes timeout after 99 seconds
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit ESC.
    // Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

    setGameStatText("Game will end in a few seconds");
    m_player[0]->doSomething();
    
    if (timeRemaining() <= 0)
		return GWSTATUS_NOT_IMPLEMENTED;
    
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (size_t i = 0; i < m_container.size(); i++)
    {
        delete m_container.at(i);
    }
    for (size_t i = 0; i < m_player.size(); i++)
    {
        delete m_player.at(i);
    }
}

//destructor
StudentWorld::~StudentWorld()
{
    cleanUp();
}


//helper functions

bool StudentWorld::loadBoard()
{
    Board bd;
    string board_file = assetPath() + "board0" + to_string(getBoardNumber()) + ".txt";
    Board::LoadResult result = bd.loadBoard(board_file);
    if (result == Board::load_fail_file_not_found) {
        cerr << "Could not find board01.txt data file\n";
        return false;
    }
    else if (result == Board::load_fail_bad_format){
        cerr << "Your board was improperly formatted\n";
        return false;
    }
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";
        
        for(int c = 0; c < BOARD_HEIGHT; c++)
        {
            for(int r = 0; r < BOARD_WIDTH; r++)
            {
                Board::GridEntry ge = bd.getContentsOf(c, r);
                switch (ge) {
                    case Board::empty:
                        cerr << "Location " << c << ", " << r << " is empty\n";
                        break;
                    case Board::boo:
                        m_container.push_back(new Baddie(this, IID_BOO, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        m_container.push_back(new Square(this, IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::bowser:
                        m_container.push_back(new Baddie(this, IID_BOWSER, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        m_container.push_back(new Square(this, IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::player:
                        cerr << "Location " << c << ", " << r << " has Peach1\n";
                        m_player.push_back(new Player(this, IID_PEACH, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        m_container.push_back(new Square(this, IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::blue_coin_square:
                        cerr << "Location " << c << ", " << r << " has a blue coin\n";
                        m_container.push_back(new Square(this, IID_BLUE_COIN_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::red_coin_square:
                        m_container.push_back(new Square(this, IID_RED_COIN_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::up_dir_square:
                        m_container.push_back(new Square(this, IID_DIR_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::down_dir_square:
                        m_container.push_back(new Square(this, IID_DIR_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::left_dir_square:
                        m_container.push_back(new Square(this, IID_DIR_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::right_dir_square:
                        m_container.push_back(new Square(this, IID_DIR_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::event_square:
                        m_container.push_back(new Square(this, IID_EVENT_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::bank_square:
                        m_container.push_back(new Square(this, IID_BANK_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                    
                    case Board::star_square:
                        m_container.push_back(new Square(this, IID_STAR_SQUARE, SPRITE_WIDTH * c, SPRITE_HEIGHT * r));
                        break;
                }
            }
        }
    }
    return true;
}



bool StudentWorld::squareExists(const int& x1, const int& y1)
{
    vector<Actor*>::iterator p;
    for (p = m_container.begin(); p != m_container.end(); p++)
    {
        int x2 = p[0]->getX();
        int y2 = p[0]->getY();
        if (x1 == x2 && y1 == y2)
        {
            cerr << "Square exists !" << endl;
            return true;
        }
    }
    return false;
}

bool StudentWorld::landed(int x, int y)
{
    vector<Player*>::iterator p;
    for (p = m_player.begin(); p != m_player.end(); p++)
    {
        int x1 = p[0]->getX();
        int y1 = p[0]->getY();
        if (x == x1 && y == y1)
        {
            cerr << "Player on coordinates !" << endl;
            return true;
        }
    }
    return false;
}


