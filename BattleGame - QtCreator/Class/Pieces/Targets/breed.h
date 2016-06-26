#ifndef BREED_H
#define BREED_H

#include "Class/Pieces/target.h"
#include <string>
#include <vector>


using std::string;
using std::vector;

typedef unsigned short WORD;

class OneHandedItem;
class Potion;
class Action;
class Game;
class QWidget;

class Breed : public Target
{
private:

    string name;

protected:

    WORD hp;
    WORD hpMax;

    float strength;
    float dexterity;

    WORD potions;
    WORD potionsMax;

    OneHandedItem *rightHand;
    OneHandedItem *leftHand;

    char direction;

    bool is_Defending;

    bool is_Alive;

public:

    Game *game;
    Breed(Game *game, float x, float y);

    void attack(char hand);

    void block();

    void usePotion();

    void openChest();

    void move(char direction);

    void beingHit(OneHandedItem *item);

    void setName(string name);

    string getName();

    WORD getHp();

    WORD getMaxHp();

    float getStrength();

    float getDexterity();    

    string getRightHandType();

    string getLeftHandType();

    char getDirection();

    bool isAlive();

    WORD getPotions();

    WORD getPotionsMax();

    bool isDefending();

    void setRightHand(OneHandedItem *item);

    OneHandedItem* getLeftHand();

    void setLeftHand(OneHandedItem *item);

    OneHandedItem* getRightHand();
};


#endif // BREED_H
