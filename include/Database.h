#pragma once 
#include "StructElem.h"

#include <map>

class Database
{

public:
    Database();
    //TODO Возвращать текст отстой
    std::string Insert(const std::string& name_table, int& id, const std::string& name);
    //TODO Возвращать текст отстой
    std::string Clear(const std::string& name_table);
    std::string InsertSection();
    std::string Difference();

private:
    using Table = std::map<int,StructElem>;
    std::map<std::string,Table> List = {{"A", Table()}, {"B", Table()}};
};
