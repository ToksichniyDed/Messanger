//
// Created by super on 27.11.2023.
//

#ifndef SERVER_OPENSSL_TOOLS_H
#define SERVER_OPENSSL_TOOLS_H

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <string>

std::string Create_Hash_With_Salt(const std::string& password, const std::string& salt);//Создание хэша-64 из исходного слова + сгенерированная соль
std::string Generate_Salt();//Генерация соли

#endif //SERVER_OPENSSL_TOOLS_H
