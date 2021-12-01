#include "Group.h"
#include <iostream>

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