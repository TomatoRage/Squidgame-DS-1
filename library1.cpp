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

StatusType AddCompany(void *DS, int GroupID,int Value){
    if(!DS || GroupID <= 0 || Value <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->AddEmptyGroup(GroupID,Value);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddEmployee(void *DS, int PlayerID, int GroupID, int Salary,int Level){
    if(!DS || GroupID <= 0 || Level < 0 || PlayerID <= 0 || Salary <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->AddPlayerToGroup(GroupID,PlayerID,Salary,Level);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveEmployee(void *DS, int PlayerID){
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

StatusType RemoveCompany(void *DS, int CompanyID){
    if(!DS || CompanyID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->RemoveGroup(CompanyID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees){

    if(!DS || CompanyID <= 0 || !Value || !NumEmployees)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->GetGroupInfo(CompanyID,Value,NumEmployees);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    if(!DS || EmployeeID <= 0 || !EmployerID || !Salary || !Grade)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->GetPlayerInfo(EmployeeID,EmployerID,Salary,Grade);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease){
    if(!DS || CompanyID <= 0 || ValueIncrease <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->IncreaseCompanyValue(CompanyID,ValueIncrease);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade){
    if(!DS || SalaryIncrease <= 0 || EmployeeID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->IncreasePlayerLevel(EmployeeID, SalaryIncrease,BumpGrade);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID){

    if(!DS || NewCompanyID <= 0 || EmployeeID <= 0)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->TransferPlayer(EmployeeID,NewCompanyID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;

}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor){
    if(!DS || AcquirerID <= 0 ||  TargetID <= 0 || TargetID == AcquirerID || Factor < 1)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->ReplaceGroup(AcquirerID,TargetID,Factor);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID){
    if(!DS || CompanyID == 0 || !EmployeeID)
        return INVALID_INPUT;
    try{
       *EmployeeID = ((SquidGame*)DS)->GetHighestLevel(CompanyID);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees){
    if(!DS || CompanyID == 0 || !Employees || !NumOfEmployees)
        return INVALID_INPUT;
    try{
        *NumOfEmployees = ((SquidGame*)DS)->GetAllPlayersByLevel(CompanyID,Employees);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees){

    if(!DS || NumOfCompanies < 1 || !Employees)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->GetGroupsHighestLevel(NumOfCompanies,Employees);
    }catch(std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;

}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){
    if(!DS || !TotalNumOfEmployees || !NumOfEmployees || CompanyID == 0 || MinEmployeeID < 0 || MaxEmployeeId < 0 ||
        MinSalary < 0 || MinGrade < 0 || MinEmployeeID > MaxEmployeeId)
        return INVALID_INPUT;
    try{
        ((SquidGame*)DS)->GetMatchingPlayers(CompanyID,MinEmployeeID,MaxEmployeeId,
                                             MinSalary,MinGrade,TotalNumOfEmployees,NumOfEmployees);
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
