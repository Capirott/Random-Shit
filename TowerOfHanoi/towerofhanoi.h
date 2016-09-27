#ifndef TOWEROFHANOI_H
#define TOWEROFHANOI_H

#include "stack.h"
#include <string>

class TowerOfHanoi
{
private:
    const int n_Disk;
    int n_Moves;
    capiroto::Stack<char> tower[3];
    capiroto::Stack<char> undo_Stack, redo_Stack;
    char* getTower(int, char*);
    public:
    TowerOfHanoi(int);
    bool moveDisk(int,int);
    int getN_Moves() { return n_Moves; }
    int getN_Disk() { return n_Disk; }
    bool tower3IsComplete() { return tower[2].size() == n_Disk; }
    bool is_undoStackEmpty() { return undo_Stack.is_Empty(); }
    bool is_redoStackEmpty() { return redo_Stack.is_Empty(); }
    bool is_TowerEmpty(int i) { return tower[i].is_Empty(); }
    char getTopTower(int i) { return tower[i].get_Top(); }
    int getTowerNDisk(int i){ return tower[i].size(); }
    char* getTower(int, int&);
    void undo();
    void redo();
};

#endif // TOWEROFHANOI_H
