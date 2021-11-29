#include "Group.h"

Group::Group():MaxLevelId(-1),MaxLevel(-1) {}

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
    
}

void Group::GincreasePlayerLevel(Player player, int level) {}

int Group::GetHighestLevelID() {}

int Group::GetAllByLevel(int **players) {}