#ifndef SQUIDGAMEDS1_GROUP_H
#define SQUIDGAMEDS1_GROUP_H

#include "Player.h"
#include "BinarySearchTree.h"

class Group {

    int MaxLevelId;
    BST<int,Player*> GroupPlayers;

public:
    Group();
    ~Group();
    void AddPlayerToGroup(int playerID);
    void RemovePlayer(int playerID);
    int GetMaxID;
    void MergeGroup(Group* ToMerge);
    void GincreasePlayerLevel(int playerID,int level);
    int GetHighestLevelID();
    int GetAllByLevel(int** players);

    class FailureException{};
    //TODO:Implement Methods
};


#endif //SQUIDGAMEDS1_GROUP_H
