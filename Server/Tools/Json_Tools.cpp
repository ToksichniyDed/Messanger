#include "Json_Tools.h"

std::string Pack_Json(const std::string& type, const std::string& data) {
    try {
        boost::property_tree::ptree incoming_data_pt;
        incoming_data_pt.put("type", type);
        incoming_data_pt.put("data", data);

        std::stringstream ss;
        boost::property_tree::write_json(ss, incoming_data_pt);
        std::string returned_str = ss.str();

        return returned_str;
    } catch (const boost::property_tree::json_parser_error& e) {
        // Обработка ошибки при работе с JSON
        std::cerr << "JSON parser error: " << e.what() << std::endl;
        // Возвращаем строку с сообщением об ошибке или выбрасываем исключение
        return "Error during JSON serialization";
    }
}


std::string Unpack_Json(const std::string& type_of_variable, const std::string& data) {
    try {
        boost::property_tree::ptree incoming_data_pt;
        std::istringstream iss(data);
        boost::property_tree::read_json(iss, incoming_data_pt);

        auto optional_value = incoming_data_pt.get_optional<std::string>(type_of_variable);

        if (optional_value) {
            return optional_value.get();  // Возвращаем значение, если ключ найден
        } else {
            // Обработка отсутствия ключа
            std::cerr << "Key not found: " << type_of_variable << std::endl;
            // Возвращаем строку с сообщением об ошибке или выбрасываем исключение
            return "Key not found";
        }
    } catch (const boost::property_tree::ptree_bad_path& e) {
        // Обработка ошибки отсутствия ключа в JSON
        std::cerr << "Error accessing key in JSON: " << e.what() << std::endl;
        // Возвращаем строку с сообщением об ошибке или выбрасываем исключение
        return "Error accessing key in JSON";
    } catch (const boost::property_tree::json_parser_error& e) {
        // Обработка ошибки при работе с JSON
        std::cerr << "JSON parser error: " << e.what() << std::endl;
        // Возвращаем строку с сообщением об ошибке или выбрасываем исключение
        return "Error during JSON deserialization";
    }
}

