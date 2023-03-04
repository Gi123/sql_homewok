#include "Database.h"

#include <utility>
#include <sstream>

Database::Database(){};

std::string Database::Insert(const std::string& name_table, int& new_id, const std::string& name) {
    auto table = List.find(name_table);
    if(table == List.end())
        return "TABLE NOT FOUND!";
    if(table->second.find(new_id) != table->second.end())
        return "DUPLICATE ID!";
    StructElem new_elem = {new_id, name};
    table->second.emplace(new_id, std::move(new_elem));
    return "OK";
}

std::string Database::Clear(const std::string& name_table) {
    auto table = List.find(name_table);
    if(table == List.end())
        return "TABLE NOT FOUND!";
    table->second.clear();
    return "OK";
}
std::string Database::InsertSection() {
    std::stringstream result;
    auto table_A = List.find("A");
    if(table_A == List.end())
        return "TABLE A NOT FOUND!";
    auto table_B = List.find("B");
    if(table_B == List.end())
        return "TABLE B NOT FOUND!";
    for(const auto& [key, value]: table_A->second) {
        auto table_value = table_B->second.find(key);
        if(table_value != table_B->second.end())
            result << key << ", " << value.name << ", " << table_value->second.name << std::endl;
    }
    return result.str();

}

std::string Database::Difference() {
    std::stringstream result;
        auto table_A = List.find("A");
    if(table_A == List.end())
        return "TABLE A NOT FOUND!";
    auto table_B = List.find("B");
    if(table_B == List.end())
        return "TABLE B NOT FOUND!";
    auto it_A = table_A->second.begin();
    auto it_B = table_B->second.begin();
    while (it_A != table_A->second.end() && it_B != table_B->second.end()) {
        if(it_A->first == it_B->first)
            ++it_A, ++it_B;
        else if(it_A->first < it_B->first) {
            result << it_A->first << ", " << it_A->second.name << ", " << std::endl;
            ++it_A;
        } else if(it_A->first > it_B->first) {
            result << it_B->first << ", " << it_B->second.name << ", " << std::endl;
            ++it_B;
        }
    }
    for(it_A; it_A != table_A->second.end(); ++it_A)
        result << it_A->first << ", " << it_A->second.name << ", " << std::endl;
    for(it_B; it_B != table_B->second.end(); ++it_B)
        result << it_B->first << ", " << it_B->second.name << ", " << std::endl;

    return result.str();
    
}