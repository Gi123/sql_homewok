#pragma once 
#include "Commands.h"

#include <functional>
#include <memory>

using CommandPtr = std::unique_ptr<ICommand>;
class CommandCreator
{
public:
    CommandPtr create(std::string& command, std::string & parameters);
private:
    std::map<std::string, std::function<CommandPtr(std::string &)>> mCommandCreators = {
        {"INSERT", std::bind(&CommandCreator::createInsertCommand, this, std::placeholders::_1)},
        {"TRUNCATE", std::bind(&CommandCreator::createTruncateCommand, this, std::placeholders::_1)},
        {"INTERSECTION", std::bind(&CommandCreator::createIntersectionCommand, this, std::placeholders::_1)},
        {"SYMMETRIC_DIFFERENCE", std::bind(&CommandCreator::createSymmetricDifferenceCommand, this, std::placeholders::_1)}
    };
    CommandPtr createInsertCommand(std::string & string);
    CommandPtr createTruncateCommand(std::string & string);
    CommandPtr createIntersectionCommand(std::string & str);
    CommandPtr createSymmetricDifferenceCommand(std::string & str);
    
};
