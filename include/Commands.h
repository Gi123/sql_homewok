#pragma once 
#include "ICommand.h"
#include "Database.h"

class InsertCommand : public ICommand
{
    std::string mTableName;
    std::string mValue;
    int mID = 0;
public:
    InsertCommand(const std::string & table, int id, const std::string & value) : mTableName(table), mValue(value), mID(id) {}
    std::string execute(Database & db) { return db.Insert(mTableName, mID, mValue);}

};

class TruncateCommand : public ICommand
{
    std::string mTableName;
public:
    TruncateCommand(const std::string & table) : mTableName(table){}
    std::string execute(Database & db) {return db.Clear(mTableName);}
};

class IntersectionCommand : public ICommand
{
public:
    IntersectionCommand() {}
    std::string execute(Database & db) { return db.InsertSection();}
};

class SymmetricDifferenceCommand : public ICommand
{
public:
    SymmetricDifferenceCommand() {}
    std::string execute(Database & db) {return db.Difference();}
};

class UnknownCommand : public ICommand
{
public:
    UnknownCommand() {}
    std::string execute(Database & db) { return "ERROR: Unknown Command";}
};

class ErrorCommand : public ICommand
{
    std::string mError;
public:
    ErrorCommand(const std::string & command) : mError(command) {} 
    std::string execute(Database & db) { return mError;}
};