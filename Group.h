#ifndef SQUIDGAMEDS1_GROUP_H
#define SQUIDGAMEDS1_GROUP_H

#include "BinarySearchTree.h"
#include "stdlib.h"
#include "cstring"
class Player;

class Group {

    int MaxLevelId;
    int MaxLevel;
    int GroupID;
    BST<Player,int> GroupPlayers;

public:
    Group(int ID);
    ~Group() = default;
    void AddPlayerToGroup(Player& player);
    void RemovePlayer(Player player);
    int GetSize();
    void MergeGroup(Group* ToMerge ,Group* SecGroup,bool type);
    void GincreasePlayerLevel(Player player,int level);
    int GetHighestLevelID() const;
    int GetAllByLevel(int** players);
    int GetGeroupID() const;
    class FailureException{};

};
class Player {

    int ID;
    int Level;
    Group* AllGroupsptr;
    Group* UsedGroupsptr;

public:

    Player(int PlayerId,int Lvl,Group* g) : ID(PlayerId) , Level(Lvl) , AllGroupsptr(g) , UsedGroupsptr(nullptr) {}
    Player():ID(0),Level(0),AllGroupsptr(nullptr),UsedGroupsptr(nullptr){}
    Player(int Id) : ID(Id) , Level(0), AllGroupsptr(nullptr) , UsedGroupsptr(nullptr) {}
    ~Player() = default;
    void UpdateAllGroup(Group* Group){
        AllGroupsptr = Group;
    }
    void UpdateUsedGroup(Group* Group){
        UsedGroupsptr = Group;
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

    Group* GetAllGroup(){
        return AllGroupsptr;
    }

    Group* GetUsedGroup(){
        return UsedGroupsptr;
    }
    //TODO:Implement Methods
    friend bool operator>(const Player& p1, const Player& p2);
    friend bool operator<(const Player& p1, const Player& p2);
    friend bool operator==(const Player& p1, const Player& p2);
};

Player* ArrMerge(Player p1[], Player p2[], int n, int m);


#endif //SQUIDGAMEDS1_GROUP_H
