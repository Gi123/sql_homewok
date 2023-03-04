#pragma once 

#include "CommandCreator.h"

class CommandParser
{
private:
    CommandCreator Creator;
public:
    CommandParser(/* args */);
    CommandPtr parse(std::string& query);
    
};

