#ifndef SQUIDGAMEDS1_PLAYER_H
#define SQUIDGAMEDS1_PLAYER_H
#include "stdlib.h"
#include "BinarySearchTree.h"

class Group;

class Player {

    int ID;
    int Level;
    Group* AllGroups;
    Group* UsedGroups;

public:

    Player(int PlayerId,int Lvl) : ID(PlayerId) , Level(Lvl) , AllGroups(NULL) , UsedGroups(NULL) {};
    Player(int Id) ;
    ~Player();
    void UpdateAllGroup(Group* Group){
        AllGroups = Group;
    }
    void UpdateUsedGroup(Group* Group){
        UsedGroups = Group;
    }
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

    friend bool operator>(const Player& c1, const Player& c2);
    friend bool operator<(const Player& c1, const Player& c2);
    friend bool operator==(const Player& c1, const Player& c2);
};

bool operator>(const Player& p1, const Player& p2){
    if(p1.Level == p2.Level){
        return p1.ID>p2.ID;
    }
    return p1.Level > p2.Level;
}
bool operator<(const Player& p1, const Player& p2){
    return !(p1>p2);
}

bool operator==(const Player& p1, const Player& p2){
    return (p1.ID == p2.ID);
}



#endif //SQUIDGAMEDS1_PLAYER_H
