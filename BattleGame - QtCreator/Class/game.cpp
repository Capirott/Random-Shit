#include "game.h"
#include "piece.h"
#include <cstdlib>

#include "Class/Pieces/Targets/Breeds/Orc/urukhai.h"
#include "Class/Pieces/Targets/Breeds/Orc/troll.h"

#include "Class/Pieces/Targets/Breeds/Human/barbarian.h"
#include "Class/Pieces/Targets/Breeds/Human/rogue.h"

#include "Class/Pieces/Targets/rock.h"
#include "Class/Pieces/chest.h"
#include <iostream>
#include <typeinfo>

Game* Game::game = 0;

Game::Game(DWORD x, DWORD y, DWORD rocks, DWORD chests, string name, Character player1, string name2, Character player2)
{
    this->x = x;
    this->y = y;

    board = new Piece**[x];
    for (DWORD i = 0; i < x; ++i)
    {
        board[i] = new Piece*[y]();
    }
    switch (player1)
    {
    case TROLL:
        player[0] = new Troll(this, 0, 0);
        break;
    case URUKHAI:
        player[0] = new UrukHai(this, 0, 0);
        break;
    case ROGUE:
        player[0] = new Rogue(this, 0, 0);
        break;
    case BARBARIAN:
        player[0] = new Barbarian(this, 0, 0);
        break;
    default:
        break;
    }
    switch (player2)
    {
    case TROLL:
        player[1] = new Troll(this, x - 1, y - 1);
        break;
    case URUKHAI:
        player[1] = new UrukHai(this, x - 1, y - 1);
        break;
    case ROGUE:
        player[1] = new Rogue(this, x - 1, y - 1);
        break;
    case BARBARIAN:
        player[1] = new Barbarian(this, x - 1, y - 1);
        break;
    default:
        break;
    }
    player[0]->setName(name);
    player[1]->setName(name2);
    for (DWORD i = 0; i < chests;   )
    {
        DWORD x = rand() % this->x;
        DWORD y = rand() % this->y;
        Piece piece(x, y);
        if (!board[x][y] && *player[0] != piece && *player[1] != piece)
        {
            board[x][y] = new Chest(x, y);
            ++i;
        }
    }
    for (DWORD i = 0; i < rocks;   )
    {
        DWORD x = rand() % this->x;
        DWORD y = rand() % this->y;
        Piece piece(x, y);
        if (!board[x][y] && *player[0] != piece && *player[1] != piece)
        {
            board[x][y] = Rock::newRock(this, x, y);
            ++i;
        }
    }
}

Game::~Game()
{
    for (DWORD i = 0; i < x; ++i)
    {
        for (DWORD j = 0; j < y; ++j)
        {
            delete board[i][j];
        }
        delete[] board[i];
    }
    delete board;
}

void Game::newGame(DWORD x, DWORD y, DWORD rocks, DWORD chests, string name, Character player1, string name2, Character player2)
{
    delete game;
    game = new Game(x, y, rocks, chests, name, player1, name2, player2);
}

Game* Game::getGame()
{
    return game;
}

DWORD Game::getX()
{
    return x;
}

DWORD Game::getY()
{
    return y;
}
