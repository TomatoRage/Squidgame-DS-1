#ifndef SQUIDGAMEDS1_SQUIDGAME_H
#define SQUIDGAMEDS1_SQUIDGAME_H

#include "BinarySearchTree.h"
#include "Group.h"

class SquidGame {

    BST<int,Player*> PlayersID;
    BST<Player,int> Players;
    BST<int,Group*> AllGroups;
    BST<int,Group*> UsedGroups;
    int TotalPlayers;
public:
    SquidGame();
    ~SquidGame();
    void AddPlayerToGroup(int GroupID,int playerID);
    void RemovePlayerFromGroup(int GroupID,int PlayerID);
    void AddEmptyGroup(int GroupID);
    void ReplaceGroup(int MainGroup,int SecondaryGroup);
    void IncreasePlayerLevel(int PlayerID,int Level);
    int GetHighestLevel(int GroupID);
    int GetAllPlayersByLevel(int GroupID,int** Players);
    int** GetGroupsHighestLevel(int NumOfGroups);

    class FailureException{};
    //TODO:Implement Methods
};


#endif //SQUIDGAMEDS1_SQUIDGAME_H
