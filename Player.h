#ifndef SQUIDGAMEDS1_PLAYER_H
#define SQUIDGAMEDS1_PLAYER_H

#include "BinarySearchTree.h"

class Group;

class Player {

    int ID;
    int Level;
    Group* AllGroups;
    Group* UsedGroups;

public:

    Player(int Id,int Lvl) : Id(ID) , lvl(Level)  {};
    Player(int Id) ;
    ~Player();
    void UpdateAllGroup(Group* Group);
    void UpdateUsedGroup(Group* Group);
    void UpdateLevel(int Level_inc) {
        Level += Level_inc;
    }
    int GetLevel() {
        return Level;
    }
    int GetID() {
        return ID;
    }
    //TODO:Implement Methods
};


#endif //SQUIDGAMEDS1_PLAYER_H
