#ifndef SQUIDGAMEDS1_GROUP_H
#define SQUIDGAMEDS1_GROUP_H

#include "Player.h"
#include "BinarySearchTree.h"

class Group {

    int MaxLevelId;
    int MaxLevel;
    int GroupID;
    BST<Player,int> GroupPlayers;

public:
    Group(int ID);
    ~Group();
    void AddPlayerToGroup(Player& player);
    void RemovePlayer(Player player);
    int GetSize();
    void MergeGroup(Group* ToMerge);
    void GincreasePlayerLevel(Player player,int level);
    int GetHighestLevelID() const;
    int GetAllByLevel(int** players);
    int GetGeroupID() const;
    class FailureException{};
    //TODO:Implement Methods
};


#endif //SQUIDGAMEDS1_GROUP_H
