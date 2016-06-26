#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>

using std::vector;
using std::string;

typedef unsigned long DWORD;

class Breed;

class Chest;

class Rock;

class Piece;

enum Character
{
    TROLL,
    URUKHAI,
    ROGUE,
    BARBARIAN
};

class Game
{

private:

    Game(DWORD x, DWORD y, DWORD rocks, DWORD chests, string name, Character player1, string name2, Character player2);

protected:

    DWORD x;
    DWORD y;



    static Game *game;

public:

    Breed *player[2];
    Piece ***board;

    DWORD getX();
    DWORD getY();


    static Game* getGame();
    static void newGame(DWORD x, DWORD y, DWORD rocks, DWORD chests, string name, Character player1, string name2, Character player2);

    virtual ~Game();
};

#endif // GAME_H
