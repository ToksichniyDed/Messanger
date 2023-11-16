#include "Json_Tools.h"

std::string Pack_Json(const std::string& type, const std::string& data){
    boost::property_tree::ptree incoming_data_pt;
    incoming_data_pt.put("type", type);
    incoming_data_pt.put("data", data);

    std::stringstream ss;
    boost::property_tree::write_json(ss, incoming_data_pt);
    std::string returned_str = ss.str();

    return returned_str;
}

std::string Unpack_Json(const std::string& type_of_variable, const std::string& data){
    boost::property_tree::ptree incoming_data_pt;
    std::istringstream iss(data);
    boost::property_tree::read_json(iss, incoming_data_pt);

    auto returned_str = incoming_data_pt.get<std::string>(type_of_variable);
    return returned_str;
}
