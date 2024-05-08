//
// Created by super on 08.11.2023.
//

#ifndef CLIENT_JSON_TOOLS_H
#define CLIENT_JSON_TOOLS_H

#include <iostream>
#include <any>
#include <map>
#include <string>
#include <sstream>

#include <boost/json.hpp>

std::string Pack_Json(const std::string& type, const std::string& data);
std::string Unpack_Json(/*Тип вынимаемого сообщения*/ const std::string& type_of_variable,/*Входящая строка*/ const std::string& data);
std::map<std::string, std::string> JSONToMap(const std::string& json_str);
std::string MapToJSON(const std::map<std::string, std::string>& data);


#endif //CLIENT_JSON_TOOLS_H
