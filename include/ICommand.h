#pragma once 

#include <string>
#include "Database.h"

class ICommand
{
public:
    ICommand(){}
    virtual std::string execute(Database& db) = 0;
};

