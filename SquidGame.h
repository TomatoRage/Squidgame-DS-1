#ifndef SQUIDGAMEDS1_SQUIDGAME_H
#define SQUIDGAMEDS1_SQUIDGAME_H

#include "BinarySearchTree.h"
#include "Group.h"
#include "library1.h"
#include <iostream>
#include "cstring"

class SquidGame {

    BST<int,Player*> PlayersID;
    BST<Player,int> Players;
    BST<int,Group*> AllGroups;
    BST<int,Group*> UsedGroups;
    int TotalPlayers;
public:
    SquidGame();
    ~SquidGame() = default;
    void AddPlayerToGroup(int GroupID,int playerID,int Salary,int Level);
    void RemovePlayerFromGroup(int PlayerID);
    void AddEmptyGroup(int GroupID,int Value);
    void RemoveGroup(int GroupID);
    void GetGroupInfo(int GroupID,int* Value,int* NumOfEmployees);
    void GetPlayerInfo(int PlayerID,int* CompanyID,int* Salary,int* Grade);
    void IncreaseCompanyValue(int CompanyID,int Value);
    void ReplaceGroup(int MainGroup,int SecondaryGroup,double Factor);
    void IncreasePlayerLevel(int PlayerID,int Salary,int Level);
    void TransferPlayer(int PlayerID,int NewGroupID);
    void GetMatchingPlayers(int CompanyID,int MinEmployeeID,int MaxEmployeeID,int MinSalary,int MinGrade,int* TotalNumOfEmployees,int* NumOfEmployees);
    int GetHighestLevel(int GroupID);
    int GetAllPlayersByLevel(int GroupID,int** Players);
    void GetGroupsHighestLevel(int NumOfGroups,int** Players);
    void Clear();

    class FailureException{};
};

#endif
