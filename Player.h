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
    Player() = default;
    Player(int Id) : ID(Id) , Level(0), AllGroups(NULL) , UsedGroups(NULL) {} ;
    ~Player() = default;
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

    friend bool operator>(const Player& p1, const Player& p2);
    friend bool operator<(const Player& p1, const Player& p2);
    friend bool operator==(const Player& p1, const Player& p2);
};

bool operator>(const Player& p1, const Player& p2){
    if(p1.Level == p2.Level){
        return p1.ID>p2.ID;
    }
    return p1.Level < p2.Level;
}
bool operator<(const Player& p1, const Player& p2){
    return !(p1>p2);
}

bool operator==(const Player& p1, const Player& p2){
    return (p1.ID == p2.ID);
}

Player* ArrMerge(Player p1[], Player p2[], int n, int m){
    int newSize = n + m;
    Player* newPlayers = (Player*) malloc(sizeof (Player) * newSize);
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    while (i < n && j < m) {
        if (p1[i] < p2[j]) {
            newPlayers[k] = p1[i];
            ++k;
            ++i;
        } else {
            newPlayers[k] = p2[j];
            ++k;
            ++j;
        }
    }
    while (i < n) {
        newPlayers[k] = p1[i];
        ++k;
        ++i;
    }
    while (j < m) {
        newPlayers[k] = p2[j];
        ++k;
        ++j;
    }
    return newPlayers;
}


#endif //SQUIDGAMEDS1_PLAYER_H
