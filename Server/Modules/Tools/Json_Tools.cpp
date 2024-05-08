#include "Json_Tools.h"

std::string Pack_Json(const std::string& type, const std::string& data) {
    try {
        boost::json::object obj;
        obj["type"] = type;
        obj["data"] = data;

        std::stringstream ss;
        ss << obj;
        return ss.str();
    } catch (const std::exception& e) {
        std::cerr << "Error during JSON serialization: " << e.what() << std::endl;
        return "Error during JSON serialization";
    }
}


std::string Unpack_Json(const std::string& type_of_variable, const std::string& data) {
    try {
        boost::json::value json_value = boost::json::parse(data);
        auto obj = json_value.as_object();

        auto it = obj.find(type_of_variable);
        if (it != obj.end()) {
            return it->value().as_string().c_str();
        } else {
            std::cerr << "Key not found: " << type_of_variable << std::endl;
            return "Key not found";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error during JSON deserialization: " << e.what() << std::endl;
        return "Error during JSON deserialization";
    }
}

std::map<std::string, std::string> JSONToMap(const std::string& json_str) {
    std::map<std::string, std::string> result_map;

    try {
        auto json = boost::json::parse(json_str);
        for (const auto& item : json.as_object()) {
            result_map[item.key()] = item.value().as_string().c_str();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error during JSON deserialization: " << e.what() << std::endl;
    }

    return result_map;
}

std::string MapToJSON(const std::map<std::string, std::string>& data) {
    boost::json::object json_obj;
    for (const auto& pair : data) {
        json_obj[pair.first] = pair.second;
    }
    std::stringstream ss;
    ss << json_obj;
    return ss.str();
}