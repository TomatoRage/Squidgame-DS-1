#ifndef SQUIDGAMEDS1_GROUP_H
#define SQUIDGAMEDS1_GROUP_H

#include "Player.h"
#include "BinarySearchTree.h"

class Group {

    int MaxLevelId;
    int MaxLevel;
    BST<Player,int> GroupPlayers;

public:
    Group();
    ~Group();
    void AddPlayerToGroup(Player& player);
    void RemovePlayer(Player player);
    int GetMaxID;
    void MergeGroup(Group* ToMerge);
    void GincreasePlayerLevel(Player player,int level);
    int GetHighestLevelID() const;
    int GetAllByLevel(int** players);

    class FailureException{};
    //TODO:Implement Methods
};


#endif //SQUIDGAMEDS1_GROUP_H
