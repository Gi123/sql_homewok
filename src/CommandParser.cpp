#include "CommandParser.h"

CommandParser::CommandParser(){};

CommandPtr CommandParser::parse(std::string& query) {
        std::string::size_type pos = query.find(" ");
        std::string command = query.substr(0, pos);
        std::string parameters;
        if(pos != std::string::npos)
            parameters = query.substr(pos + 1);
        return Creator.create(command, parameters);
}