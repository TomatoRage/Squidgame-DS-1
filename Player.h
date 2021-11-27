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

    Player(int ID,int Level);
    Player(int ID);
    ~Player();
    void UpdateAllGroup(Group* Group);
    void UpdateUsedGroup(Group* Group);
    void UpdateLevel(int Level);
    int GetLevel();
    int GetID();
    //TODO:Implement Methods
};


#endif //SQUIDGAMEDS1_PLAYER_H
