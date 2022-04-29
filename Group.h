#ifndef SQUIDGAMEDS1_GROUP_H
#define SQUIDGAMEDS1_GROUP_H

#include "BinarySearchTree.h"
#include <stdlib.h>
#include "cstring"
class Player;

class Group {

    int MaxLevelId;
    int MaxLevel;
    int GroupID;
    BST<Player,int> GroupPlayers;
    double Value;

public:
    Group(int ID,int Value);
    ~Group() = default;
    void AddPlayerToGroup(Player& player);
    void RemovePlayer(Player player);
    int GetSize();
    void MergeGroup(Group* ToMerge ,Group* SecGroup,bool type,double Factor);
    void GincreasePlayerLevel(Player player,int level);
    int GetHighestLevelID() const;
    int GetAllByLevel(int** players);
    int GetGeroupID() const;
    void SetGroupID(int ID);
    void IncreaseValue(int newValue);
    void SetValue(int newValue);
    void GetMatchingPlayers(int MinID,int MaxID,int MinSalary,int MinGrade,int* TotalEmployees,int* NumOfEmployees);
    int GetValue() const;

    class FailureException{};

};
class Player {

    int ID;
    int Level;
    int Salary;
    Group* AllGroupsptr;
    Group* UsedGroupsptr;

public:

    Player(int PlayerId,int Salary,int Lvl,Group* g) : ID(PlayerId) , Salary(Salary) , Level(Lvl) , AllGroupsptr(g) , UsedGroupsptr(nullptr) {}
    Player():ID(0),Level(0),AllGroupsptr(nullptr),UsedGroupsptr(nullptr),Salary(0){}
    Player(int Id) : ID(Id) , Level(0), AllGroupsptr(nullptr) , UsedGroupsptr(nullptr) {}
    ~Player() = default;
    void UpdateAllGroup(Group* Group){
        AllGroupsptr = Group;
    }
    void UpdateUsedGroup(Group* Group){
        UsedGroupsptr = Group;
    }
    void UpdateLevel(int Level_inc) {
        Salary += Level_inc;
    }

    void Promote(int salary){
        Salary += salary;
        Level++;
    }

    int GetLevel() const {
        return Salary;
    }

    int GetID() const {
        return ID;
    }

    int GetGrade() const {
        return Level;
    }

    int GetSalary() const {
        return Salary;
    }
    Group* GetAllGroup(){
        return AllGroupsptr;
    }

    Group* GetUsedGroup() const {
        return UsedGroupsptr;
    }


    friend bool operator>(const Player& p1, const Player& p2);
    friend bool operator<(const Player& p1, const Player& p2);
    friend bool operator==(const Player& p1, const Player& p2);
};

Player* ArrMerge(Player p1[], Player p2[], int n, int m);


#endif //SQUIDGAMEDS1_GROUP_H
