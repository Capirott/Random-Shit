#include "breed.h"

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include "Class/Pieces/Items/onehandeditem.h"
#include "Class/action.h"

#include "Class/Pieces/target.h"
#include "Class/Pieces/chest.h"

#include "Class/Pieces/Items/bomb.h"
#include "Class/Pieces/Items/potion.h"
#include "Class/Pieces/Items/OneHandedWeapons/axe.h"
#include "Class/Pieces/Items/OneHandedWeapons/bow.h"
#include "Class/Pieces/Items/OneHandedWeapons/shield.h"
#include "Class/Pieces/Items/OneHandedWeapons/sword.h"

#include "Class/game.h"
#include "dialog.h"

#define INITIAL_HP              10
#define INITIAL_HP_MAX          10
#define INITIAL_STRENGTH        5
#define INITIAL_DEXTERITY       5
#define INITIAL_POTIONS         0
#define INITIAL_POTIONS_MAX     2



Breed::Breed(Game *game, float x, float y)
    : Target(x, y)
{
    hp              = INITIAL_HP;
    hpMax           = INITIAL_HP_MAX;
    strength        = INITIAL_STRENGTH;
    dexterity       = INITIAL_DEXTERITY;
    potions         = INITIAL_POTIONS;
    potionsMax      = INITIAL_POTIONS_MAX;
    rightHand       = 0;
    leftHand        = 0;
    direction       = '\0';
    this->game      = game;
    is_Defending    = false;
    is_Alive        = true;
}

void Breed::attack(char hand)
{
    is_Defending = false;
    OneHandedItem *weapon = rightHand;

    if (hand == 'L')
    {
        weapon = leftHand;
    }
    if (is_Alive && weapon)
    {
        int x = this->x;
        int y = this->y;

        do
        {
            switch (direction)
            {
            case 'W':
                if (x)
                    --x;
                else
                    return;
                break;
            case 'A':
                if (y)
                    --y;
                else
                    return;
                break;
            case 'S':
                if (x + 1 != int(game->getX()))
                    ++x;
                else
                    return;
                break;
            case 'D':
                if (y + 1 != int(game->getY()))
                    ++y;
                else
                    return;
                break;
            default:
                return;
            }
            if (game->board[x][y] && game->board[x][y]->type() == "Rock")
            {
                ((Target *)game->board[x][y])->beingHit(weapon);
                return;
            }
            else
            {
                Piece piece(x, y);
                if (*game->player[0] == piece && game->player[0]->is_Alive)
                {
                    (game->player[0])->beingHit(weapon);
                       return;
                }
                else
                {
                    if (*game->player[1] == piece && game->player[1]->is_Alive)
                    {
                        (game->player[1])->beingHit(weapon);
                        return;
                    }
                }
            }
        }
        while(weapon->type() == "Bow");
    }
}

void Breed::block()
{
    is_Defending = true;
}


bool Breed::isAlive()
{
    return is_Alive;
}

void Breed::usePotion()
{
    is_Defending = false;
    if (hp == hpMax)
        return;
    if (potions)
    {
        if (is_Alive)
        {
            hp += hpMax / 2;
            if (hp > hpMax)
                hp = hpMax;
        }
        else
        {
            hp = hpMax / 2;
            is_Alive = true;
        }

        --potions;
    }
}

void Breed::beingHit(OneHandedItem *item)
{
    float leftHandDefence   = 0;
    float rightHandDefence  = 0;

    if (is_Defending)
    {
        if (leftHand)
            leftHandDefence = leftHand->getDefence();
        if (rightHand)
            rightHandDefence = rightHand->getDefence();
    }
    WORD hpLost = std::max(0.0, item->getDamage() - (leftHandDefence + rightHandDefence) * (fmod(dexterity * rand(),  2.0) + 1.0));
    if (hpLost >= hp)
    {
        is_Alive = false;
    }
    hp -= hpLost;
}

WORD Breed::getHp()
{
    return this->hp;
}

WORD Breed::getMaxHp()
{
    return this->hpMax;
}

float Breed::getStrength()
{
    return this->strength;
}

float Breed::getDexterity()
{
    return this->dexterity;
}

void Breed::setName(string name)
{
    this->name = name;
}

string Breed::getName()
{
    return this->name;
}

string Breed::getRightHandType()
{
    if (rightHand)
        return rightHand->type();
    return "Nil";
}

string Breed::getLeftHandType()
{
    if (leftHand)
        return leftHand->type();
    return "Nil";
}

void Breed::move(char direction)
{    
    is_Defending = false;
    int x = this->x;
    int y = this->y;
    this->direction = direction;

    switch (direction)
    {
    case 'W':
        if (x)
            --x;
        else
            return;
        break;
    case 'A':
        if (y)
            --y;
        else
            return;
        break;
    case 'S':
        if (x + 1 != int(game->getX()))
            ++x;
        else
            return;
        break;
    case 'D':
        if (y + 1 != int(game->getY()))
            ++y;
        else
            return;
        break;
    }
    Piece piece(x, y);
    if ( (!game->board[x][y] || game->board[x][y]->type() == "Chest")  && (((piece != *game->player[0] || !(game->player[0]->is_Alive))  &&  (piece != *game->player[1] || !(game->player[1]->is_Alive))) || !is_Alive)
            )
    {
        this->x = x;
        this->y = y;
    }

}

char Breed::getDirection()
{
    return direction;
}

WORD Breed::getPotions()
{
    return potions;
}

WORD Breed::getPotionsMax()
{
    return potionsMax;
}

bool Breed::isDefending()
{
    return is_Defending;
}

void Breed::openChest()
{
    if (isAlive())
    {
        Piece *piece = game->board[x][y];
        if (piece && piece->type() == "Chest")
        {
            Chest *chest = (Chest *)piece;
            if (chest->getItemType() == "Potion")
            {
                if (potions != potionsMax)
                {
                    ++potions;
                    delete chest->getItem();
                    chest->setItem(0);
                }
            }
            else
            {
                if (chest->getItemType() == "Bomb")
                {
                    Bomb *bomb = (Bomb *)chest->getItem();
                    if (hp <= bomb->getDamage())
                        is_Alive = false;
                    hp -= bomb->getDamage();
                    delete bomb;
                    chest->setItem(0);
                }
                if (chest->getItemType() != "")
                {
                    Dialog *dialog = new Dialog(this, chest);
                    dialog->exec();
                }
            }
        }
    }
}

void Breed::setLeftHand(OneHandedItem *item)
{
    this->leftHand = item;
}

OneHandedItem* Breed::getLeftHand()
{
    return leftHand;
}

void Breed::setRightHand(OneHandedItem *item)
{
    this->rightHand = item;
}

OneHandedItem* Breed::getRightHand()
{
    return rightHand;
}

#undef INITIAL_HP
#undef INITIAL_HP_MAX
#undef INITIAL_STRENGTH
#undef INITIAL_DEXTERITY
#undef INITIAL_POTIONS
#undef INITIAL_POTIONS_MAX
