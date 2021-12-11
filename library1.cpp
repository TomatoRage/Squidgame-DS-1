#include "library1.h"
#include "SquidGame.h"
#include <iostream>

void *Init(){

    try{
        SquidGame* DS = new SquidGame();
        return (void*)DS;
    }catch(std::bad_alloc& e){
        return nullptr;
    }

}

StatusType AddGroup(void *DS, int GroupID){
    if(!DS || GroupID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->AddEmptyGroup(GroupID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level){
    if(!DS || GroupID <= 0 || Level < 0 || PlayerID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->AddPlayerToGroup(GroupID,PlayerID,Level);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemovePlayer(void *DS, int PlayerID){
    if(!DS || PlayerID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->RemovePlayerFromGroup(PlayerID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID){
    if(!DS || GroupID <= 0 ||  ReplacementID <= 0 || GroupID == ReplacementID)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->ReplaceGroup(ReplacementID,GroupID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease){
    if(!DS || LevelIncrease <= 0 || PlayerID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->IncreasePlayerLevel(PlayerID, LevelIncrease);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID){
    if(!DS || GroupID == 0 || !PlayerID)
        return INVALID_INPUT;
    try{
       *PlayerID = ((SquidGame*)DS)->GetHighestLevel(GroupID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers){
    if(!DS || GroupID == 0 || !Players || !numOfPlayers)
        return INVALID_INPUT;
    try{
        *numOfPlayers = ((SquidGame*)DS)->GetAllPlayersByLevel(GroupID,Players);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players){

    if(!DS || numOfGroups < 1 || !Players)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->GetGroupsHighestLevel(numOfGroups,Players);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;

}

void Quit(void** DS){
    if(!DS)
        return;
    (*(SquidGame**)DS)->Clear();
    delete *(SquidGame**)DS;
    *DS = nullptr;
}
