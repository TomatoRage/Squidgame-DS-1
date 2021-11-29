#include "SquidGame.h"

SquidGame::SquidGame() {}

SquidGame::~SquidGame() {}

void SquidGame::AddPlayerToGroup(int GroupID, int playerID) {}

void SquidGame::RemovePlayerFromGroup(int GroupID, int PlayerID) {}

void SquidGame::AddEmptyGroup(int GroupID) {}

void SquidGame::ReplaceGroup(int MainGroup, int SecondaryGroup) {}

void SquidGame::IncreasePlayerLevel(int PlayerID, int Level) {}

int SquidGame::GetHighestLevel(int GroupID) {}

int SquidGame::GetAllPlayersByLevel(int GroupID, int **Players) {}

int **SquidGame::GetGroupsHighestLevel(int NumOfGroups) {}