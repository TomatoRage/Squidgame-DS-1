#include "SquidGame.h"


SquidGame::SquidGame():TotalPlayers(0) {}

void SquidGame::AddPlayerToGroup(int GroupID,int playerID,int Level) {
    if(PlayersID.Find(playerID) || !AllGroups.Find(GroupID)) throw FailureException();
    Group* g1 = (AllGroups.Find(GroupID));
    Player player1 = Player(playerID, Level, g1);
    PlayersID.insert(playerID,&player1);
    Players.insert(player1,0);
    if (AllGroups.Find(GroupID)->GetSize() == 0){
        Group Temp = Group(GroupID);
        memcpy(&Temp,g1,sizeof(*g1));
        UsedGroups.insert(GroupID,&Temp);
    }
    AllGroups.Find(GroupID)->AddPlayerToGroup(player1);
    TotalPlayers++;
}

void SquidGame::RemovePlayerFromGroup(int playerID) {
    if(!PlayersID.Find(playerID))  throw FailureException();
    Player* p1 = PlayersID.Find(playerID);
    Group* g1 = p1->GetAllGroup();
    g1->RemovePlayer(*p1);
    Group* AG = (PlayersID.Find(playerID)->GetAllGroup());
    AG->RemovePlayer(*p1);
    if(AG->GetSize() == 0){
        UsedGroups.remove(AG->GetGeroupID());
    }
    Players.remove(*p1);
    PlayersID.remove(playerID);
    TotalPlayers--;
}

void SquidGame::AddEmptyGroup(int GroupID) {
    if(AllGroups.Find(GroupID)) throw FailureException();
    auto* g1 = new Group(GroupID);
    AllGroups.insert(GroupID,g1);
}

void SquidGame::ReplaceGroup(int MainGroup, int SecondaryGroup) {
    Group* GM = AllGroups.Find(MainGroup);
    Group* GS = AllGroups.Find(SecondaryGroup);
    Group* Temp = GS;
    GM->MergeGroup(GS);
    AllGroups.remove(SecondaryGroup);

    GM = UsedGroups.Find(MainGroup);
    GS = UsedGroups.Find(SecondaryGroup);
    GM->MergeGroup(GS);
    UsedGroups.remove(SecondaryGroup);

    delete GS;
    delete Temp;
}

void SquidGame::IncreasePlayerLevel(int PlayerID, int Level) {
    Player* p = PlayersID.Find(PlayerID);
    p->UpdateLevel(Level);
    p->GetAllGroup()->GincreasePlayerLevel(*p,Level);
    p->GetUsedGroup()->GincreasePlayerLevel(*p,Level);
}

int SquidGame::GetHighestLevel(int GroupID) {

    if(GroupID == -1) {
        Player* p;
        Players.GetMax(p);
        return p->GetID();
    }else{
        Group* G;
        G = AllGroups.Find(GroupID);
        if(G->GetSize() == 0)
            return -1;
        return G->GetHighestLevelID();
    }

}

int SquidGame::GetAllPlayersByLevel(int GroupID, int **Players) {
    if(GroupID == -1){
        int* players = (int*) malloc(sizeof(int)*TotalPlayers);
        if(players == nullptr)
            throw std::bad_alloc();
        Player* p;
        this->Players.ResetIterator();
        for (int i = 0; i < TotalPlayers; i++) {
            this->Players.NextIteration(&p);
            players[i] = p->GetLevel();
        }
        return TotalPlayers;
    }else {
        Group* G = AllGroups.Find(GroupID);
        return G->GetAllByLevel(Players);
    }

}

int **SquidGame::GetGroupsHighestLevel(int NumOfGroups) {

    int* Temp;
    int** ID = &Temp;
    Group* G;

    if(UsedGroups.GetSize() < NumOfGroups)
        throw FailureException();

    int *players = (int*) malloc(sizeof(int)*NumOfGroups);

    if(players == nullptr)
        throw std::bad_alloc();

    UsedGroups.ResetIterator();
    for (int i = 0; i < NumOfGroups; ++i) {
        G = UsedGroups.NextIteration(ID);
        players[i] = G->GetHighestLevelID();
    }

    return &players;
}

void SquidGame::Clear() {
    int key;
    int* key_ptr = &key;
    PlayersID.ResetIterator();
    for (int i = 0; i < PlayersID.GetSize(); i++) {
        Player* P = PlayersID.NextIteration(&key_ptr);
        delete P;
    }
    Players.ResetIterator();
    for (int i = 0; i < Players.GetSize(); i++) {
        Player* P;
        Players.NextIteration(&P);
        delete P;
    }
    AllGroups.ResetIterator();
    for (int i = 0; i < AllGroups.GetSize(); i++) {
        Group* G;
        G = AllGroups.NextIteration(&key_ptr);
        delete G;
    }
    UsedGroups.ResetIterator();
    for (int i = 0; i < UsedGroups.GetSize(); i++) {
        Group* G;
        G = UsedGroups.NextIteration(&key_ptr);
        delete G;
    }
}