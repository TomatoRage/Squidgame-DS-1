#include "SquidGame.h"
#include "iostream"

SquidGame::SquidGame():TotalPlayers(0) {}

void SquidGame::AddPlayerToGroup(int GroupID,int playerID,int Salary,int Level) {
    AllGroups.Find(GroupID);
    try {
        PlayersID.Find(playerID);
    }catch (...){
        Group* g1 = (AllGroups.Find(GroupID));
        auto* player1 = new Player(playerID, Salary,Level, g1);
        PlayersID.insert(playerID,player1);
        Players.insert(*player1,Salary);
        if (AllGroups.Find(GroupID)->GetSize() == 0){
            Group* Temp = new Group(GroupID,g1->GetValue());
            memcpy(Temp,g1,sizeof(*g1));
            UsedGroups.insert(GroupID,Temp);
        }
        player1->UpdateUsedGroup(UsedGroups.Find(GroupID));
        AllGroups.Find(GroupID)->AddPlayerToGroup(*player1);
        UsedGroups.Find(GroupID)->AddPlayerToGroup(*player1);
        TotalPlayers++;
        return;
    }
    throw FailureException();
}

void SquidGame::RemovePlayerFromGroup(int playerID) {
    if(!PlayersID.Find(playerID)) throw FailureException();
    Player* p1 = PlayersID.Find(playerID);
    Group* g1 = p1->GetAllGroup();
    g1->RemovePlayer(*p1);
    Group* AG = (PlayersID.Find(playerID)->GetUsedGroup());
    AG->RemovePlayer(*p1);
    if(AG->GetSize() == 0){
        UsedGroups.remove(AG->GetGeroupID());
        delete AG;
    }
    Players.remove(*p1);
    PlayersID.remove(playerID);
    TotalPlayers--;
    delete p1;
}

void SquidGame::AddEmptyGroup(int GroupID,int Value) {
    try {
        AllGroups.Find(GroupID);
    }catch (...){
        auto* g1 = new Group(GroupID,Value);
        AllGroups.insert(GroupID,g1);
        return;
    }
    throw FailureException();
}

void SquidGame::RemoveGroup(int GroupID) {
    Group* G = AllGroups.Find(GroupID);
    if(G->GetSize() != 0){
        throw FailureException();
    }
    AllGroups.remove(GroupID);
}

void SquidGame::GetGroupInfo(int GroupID,int* Value,int* NumOfEmployees){
    Group* G = AllGroups.Find(GroupID);
    *Value = G->GetValue();
    *NumOfEmployees = G->GetSize();
}

void SquidGame::GetPlayerInfo(int PlayerID,int* CompanyID,int* Salary,int* Grade){
    Player* P = PlayersID.Find(PlayerID);
    *CompanyID = P->GetAllGroup()->GetGeroupID();
    *Salary = P->GetSalary();
    *Grade = P->GetGrade();
}

void SquidGame::IncreaseCompanyValue(int CompanyID,int Value){
    Group* G = AllGroups.Find(CompanyID);
    G->IncreaseValue(Value);
}


void SquidGame::TransferPlayer(int PlayerID,int NewGroupID){
    Player* P = PlayersID.Find(PlayerID);
    Group* NewGroup = AllGroups.Find(NewGroupID);
    Players.remove(*P);
    P->GetAllGroup()->RemovePlayer(PlayerID);
    P->GetUsedGroup()->RemovePlayer(PlayerID);
    if(P->GetAllGroup()->GetSize() == 0) {
        UsedGroups.remove(P->GetUsedGroup()->GetGeroupID());
        P->UpdateUsedGroup(nullptr);
    }
    if(NewGroup->GetSize() == 0){
        Group* UG = new Group(NewGroupID,NewGroup->GetValue());
        P->UpdateAllGroup(NewGroup);
        P->UpdateUsedGroup(UG);
        memcpy(UG,NewGroup,sizeof(*NewGroup));
        UsedGroups.insert(NewGroupID,UG);
    }
    NewGroup->AddPlayerToGroup(*P);
    UsedGroups.Find(NewGroupID)->AddPlayerToGroup(*P);
    P->UpdateAllGroup(NewGroup);
    P->UpdateUsedGroup(UsedGroups.Find(NewGroupID));
    Players.insert(*P,P->GetSalary());
    /*
         AllGroups.Find(GroupID);
    try {
        PlayersID.Find(playerID);
    }catch (...){
        Group* g1 = (AllGroups.Find(GroupID));
        auto* player1 = new Player(playerID, Salary,Level, g1);
        PlayersID.insert(playerID,player1);
        Players.insert(*player1,Salary);
        if (AllGroups.Find(GroupID)->GetSize() == 0){
            Group* Temp = new Group(GroupID,g1->GetValue());
            memcpy(Temp,g1,sizeof(*g1));
            UsedGroups.insert(GroupID,Temp);
        }
        player1->UpdateUsedGroup(UsedGroups.Find(GroupID));
        AllGroups.Find(GroupID)->AddPlayerToGroup(*player1);
        UsedGroups.Find(GroupID)->AddPlayerToGroup(*player1);
        TotalPlayers++;
     */
}

void SquidGame::IncreasePlayerLevel(int PlayerID, int Salary,int Level) {
    Player* p = PlayersID.Find(PlayerID);
    Player* p1 = new Player();
    memcpy(p1,p,sizeof(*p));
    Group* ag = p->GetAllGroup();
    Group* ug = p->GetUsedGroup();
    PlayersID.remove(PlayerID);
    Players.remove(*p);
    ag->RemovePlayer(*p);
    ug->RemovePlayer(*p);
    if(Level > 0) {
        p1->Promote(Salary);
    }else{
        p1->UpdateLevel(Salary);
    }
    ag->AddPlayerToGroup(*p1);
    ug->AddPlayerToGroup(*p1);
    PlayersID.insert(PlayerID,p1);
    Players.insert(*p1,Salary);
    ///Players.insert(*p1,0);
    delete p;
}

void SquidGame::ReplaceGroup(int MainGroup, int SecondaryGroup,double Factor) {
    Group* GM = AllGroups.Find(MainGroup);
    Group* GS = AllGroups.Find(SecondaryGroup);
    Group* Temp = GS;
    if(GM->GetValue() < GS->GetValue()*10)
        throw FailureException();
    PlayersID.ResetIterator();
    int k;
    int* p= &k;
    Player* player;
    for (int i = 0; i < PlayersID.GetSize(); i++) {
        player = PlayersID.NextIteration(&p);
        if(player->GetAllGroup() == GS){
            player->UpdateAllGroup(GM);
        }
    }

    Group* temp;
    if(GS->GetSize() == 0 && GM->GetSize() == 0)
        temp = nullptr;
    else if(GM->GetSize() == 0)
        temp = UsedGroups.Find(SecondaryGroup);
    else
        temp = UsedGroups.Find(MainGroup);

    GM->MergeGroup(GS,temp,true,Factor);
    AllGroups.remove(SecondaryGroup);

    try {
        GS = UsedGroups.Find(SecondaryGroup);
    }catch (...){
        delete Temp;
        return;
    }
    try {
        GM = UsedGroups.Find(MainGroup);
    }catch(...){
        UsedGroups.remove(GS->GetGeroupID());
        GS->SetGroupID(MainGroup);
        UsedGroups.insert(MainGroup,GS);
        delete Temp;
        return;
    }
    PlayersID.ResetIterator();
    for (int i = 0; i < PlayersID.GetSize(); i++) {
        player = PlayersID.NextIteration(&p);
        if(player->GetUsedGroup() == GS){
            player->UpdateUsedGroup(GM);
        }
    }
    GM->MergeGroup(GS,AllGroups.Find(MainGroup),false,Factor);
    UsedGroups.remove(SecondaryGroup);

    delete GS;
    delete Temp;
}

int SquidGame::GetHighestLevel(int GroupID) {

    if(GroupID < 0) {
        if(Players.GetSize() == 0)
            return -1;
        Player p;
        Players.GetMax(&p);
        return p.GetID();
    }else{
        Group* G;
        G = AllGroups.Find(GroupID);
        if(G->GetSize() == 0)
            return -1;
        return G->GetHighestLevelID();
    }

}

int SquidGame::GetAllPlayersByLevel(int GroupID, int **Players) {
    if(GroupID < 0){

        int *players = (int*) malloc(sizeof(int)*TotalPlayers);
        if(players == nullptr)
            throw std::bad_alloc();
        Player player,*p = &player;
        this->Players.ResetIterator();
        for (int i = TotalPlayers-1; i >= 0; i--) {
            this->Players.NextIteration(&p);
            players[i] = p->GetID();
        }
        *Players = players;
        return TotalPlayers;
    }else {
        Group* G = AllGroups.Find(GroupID);
        return G->GetAllByLevel(Players);
    }

}

void SquidGame::GetGroupsHighestLevel(int NumOfGroups,int** Players) {

    int Temp;
    int* ID = &Temp;
    Group* G;

    if(UsedGroups.GetSize() < NumOfGroups)
        throw FailureException();

    int *players = (int*) malloc(sizeof(int)*NumOfGroups);

    if(players == nullptr)
        throw std::bad_alloc();
    UsedGroups.ResetIterator();
    for (int i = 0; i < NumOfGroups; ++i) {
        G = UsedGroups.NextIteration(&ID);
        players[i] = G->GetHighestLevelID();
    }

    *Players=players;
}

void SquidGame::GetMatchingPlayers(int CompanyID,int MinEmployeeID,int MaxEmployeeID,
                        int MinSalary,int MinGrade,int* TotalNumOfEmployees,int* NumOfEmployees){
    if(CompanyID < 0){

        int Employees = 0,SubEmployees = 0;
        int k,*p = &k;
        Player* player;
        PlayersID.ResetIterator();
        for(int i = 0; i < PlayersID.GetSize(); i++){
            player = PlayersID.NextIteration(&p);
            if(player->GetID() > MaxEmployeeID)
                break;
            else if(player->GetID() > MinEmployeeID){
                Employees++;
                if(player->GetSalary() >= MinSalary && player->GetGrade() >= MinGrade)
                    SubEmployees++;
            }
        }
        *TotalNumOfEmployees = Employees;
        *NumOfEmployees = SubEmployees;

    }else{
        Group* G = AllGroups.Find(CompanyID);
        if(G->GetSize() == 0)
            throw FailureException();
        G->GetMatchingPlayers(MinEmployeeID,MaxEmployeeID,MinSalary,MinGrade,TotalNumOfEmployees,NumOfEmployees);
    }
}

void SquidGame::Clear() {
    int key;
    int* key_ptr = &key;
    PlayersID.ResetIterator();
    for (int i = 0; i < PlayersID.GetSize(); i++) {
        Player* P = PlayersID.NextIteration(&key_ptr);
        delete P;
    }
    AllGroups.ResetIterator();
    for(int i = 0; i < AllGroups.GetSize(); i++){
        Group* G = AllGroups.NextIteration(&key_ptr);
        delete G;
    }
    UsedGroups.ResetIterator();
    for(int i = 0; i < UsedGroups.GetSize(); i++){
        Group* G = UsedGroups.NextIteration(&key_ptr);
        delete G;
    }
}

