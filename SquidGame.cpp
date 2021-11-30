#include "SquidGame.h"

SquidGame::SquidGame() {}

SquidGame::~SquidGame() {}

void SquidGame::AddPlayerToGroup(int GroupID,int playerID,int Level) {
    if(PlayersID.Find(playerID) || !AllGroups.Find(GroupID)) throw FailureException();
    Group* g1 = (AllGroups.Find(GroupID));
    Player player1 = Player(playerID, Level, g1);
    PlayersID.insert(playerID,&player1);
    Players.insert(player1,0);
    if (AllGroups.Find(GroupID)->GetSize() == 0){
        UsedGroups.insert(GroupID,g1);
    }
    UsedGroups.Find(GroupID)->AddPlayerToGroup(player1);
    AllGroups.Find(GroupID)->AddPlayerToGroup(player1);
    TotalPlayers++;
}

void SquidGame::RemovePlayerFromGroup(int GroupID, int playerID) {
    if(!PlayersID.Find(playerID))  throw FailureException();
    Player* p1 = PlayersID.Find(playerID);
    Group* g1 = p1->GetAllGroup();
    g1->RemovePlayer(*p1);
    UsedGroups.Find(GroupID)->RemovePlayer(*p1);
    if(UsedGroups.Find(GroupID)->GetSize() == 0){
        UsedGroups.remove(GroupID);
    }
    Players.remove(*p1);
    PlayersID.remove(playerID);
    TotalPlayers--;
}

void SquidGame::AddEmptyGroup(int GroupID) {
    if(AllGroups.Find(GroupID)) throw FailureException();
    Group g1 = Group();
    AllGroups.insert(GroupID,&g1);
}

void SquidGame::ReplaceGroup(int MainGroup, int SecondaryGroup) {}

void SquidGame::IncreasePlayerLevel(int PlayerID, int Level) {}

int SquidGame::GetHighestLevel(int GroupID) {}

int SquidGame::GetAllPlayersByLevel(int GroupID, int **Players) {}

int **SquidGame::GetGroupsHighestLevel(int NumOfGroups) {}