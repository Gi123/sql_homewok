#include "CommandCreator.h"

#include <iostream>

CommandPtr CommandCreator::create(std::string& command, std::string & parameters) {
    auto it = mCommandCreators.find(command);
    if(it == mCommandCreators.end())
    {
        std::cout << command << "   " << parameters << std::endl;
        return std::make_unique<UnknownCommand>();
    }
    return it->second(parameters);
}

CommandPtr CommandCreator::createInsertCommand(std::string & string) {
    std::string::size_type pos = string.find(" ");
    if(pos == std::string::npos)
        return std::make_unique<ErrorCommand>(std::string("ERROR:INSERT [TableName] [id] [value]"));
    std::string table_name = string.substr(0, pos);
    std::string token  = string.substr(pos+1);
    pos = token.find(" ");
    if(pos == std::string::npos)
        return std::make_unique<ErrorCommand>(std::string("ERROR:INSERT [TableName] [id] [value]"));
    std::string id = token.substr(0, pos);
    std::string value  = token.substr(pos+1);    
    return std::make_unique<InsertCommand>(table_name, std::atoi(id.c_str()), value);
}
CommandPtr CommandCreator::createTruncateCommand(std::string & string) {
    return std::make_unique<TruncateCommand>(string);
}

CommandPtr CommandCreator::createIntersectionCommand(std::string & str) {
    return std::make_unique<IntersectionCommand>();
}

CommandPtr CommandCreator::createSymmetricDifferenceCommand(std::string & str) {
    return std::make_unique<SymmetricDifferenceCommand>();
}