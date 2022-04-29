#include "Group.h"

bool operator>(const Player& p1, const Player& p2){
    if(p1.Salary == p2.Salary){
        return p1.ID < p2.ID;
    }
    return p1.Salary > p2.Salary;
}
bool operator<(const Player& p1, const Player& p2){
    return !(p1>p2) && !(p1 == p2);
}

bool operator==(const Player& p1, const Player& p2){
    return (p1.ID == p2.ID);
}


