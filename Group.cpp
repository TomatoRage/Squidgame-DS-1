#include "Group.h"
#include <iostream>

Player* ArrMerge(Player p1[],Player p2[],int n,int m){
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

Group::Group(int ID):MaxLevelId(-1),MaxLevel(-1),GroupID(ID) {}

void Group::AddPlayerToGroup(Player& player) {
    int zero = 0;
    GroupPlayers.insert(player,zero);
    if(player.GetLevel() > MaxLevel || MaxLevel == player.GetLevel() && player.GetID() < MaxLevelId){
        MaxLevel = player.GetLevel();
        MaxLevelId = player.GetID();
    }
}

void Group::RemovePlayer(Player player) {
    Player p;
    GroupPlayers.remove(player);
    if(player.GetID() == MaxLevelId) {
        GroupPlayers.GetMax(&p);
        MaxLevelId = p.GetID();
        MaxLevel = p.GetLevel();
    }
}

void Group::MergeGroup(Group *ToMerge) {

    Player* p;
    Player* players[GroupPlayers.GetSize()];
    Player* Players2[ToMerge->GroupPlayers.GetSize()];
    GroupPlayers.ResetIterator();
    for(int i = 0; i < GroupPlayers.GetSize();i++){
        GroupPlayers.NextIteration(&p);
        players[i] = p;
    }
    ToMerge->GroupPlayers.ResetIterator();
    for (int i = 0; i < ToMerge->GroupPlayers.GetSize(); i++) {
        ToMerge->GroupPlayers.NextIteration(&p);
        Players2[i] = p;
    }

   p = ArrMerge(*players,*Players2,GroupPlayers.GetSize(),ToMerge->GroupPlayers.GetSize());
    int GSize = GroupPlayers.GetSize() + ToMerge->GroupPlayers.GetSize();
    GroupPlayers.clear();

    for(int i = 0;i < GSize;i++){
        GroupPlayers.insert(p[i],GSize);
    }
}

void Group::GincreasePlayerLevel(Player player, int level) {
    Player& Curr = GroupPlayers.FindKey(player);
    Curr.UpdateLevel(level);
}

int Group::GetHighestLevelID() const {
    return MaxLevelId;
}

int Group::GetAllByLevel(int **players) {

    if(GroupPlayers.GetSize() == 0) {
        players = nullptr;
        return 0;
    }

    int* p = (int*) malloc(sizeof(int)*GroupPlayers.GetSize());
    Player* player;

    if(p == nullptr)
        throw std::bad_alloc();

    GroupPlayers.ResetIterator();
    for(int i = 0; i < GroupPlayers.GetSize(); i++) {
        GroupPlayers.NextIteration(&player);
        p[i] = player->GetID();
    }
    *players = p;
    return GroupPlayers.GetSize();

}

int Group::GetSize() {
    return GroupPlayers.GetSize();
}

int Group::GetGeroupID() const {
    return GroupID;
}