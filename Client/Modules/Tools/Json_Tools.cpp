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