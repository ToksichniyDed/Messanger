//
// Created by super on 27.11.2023.
//

#include "OpenSSL_Tools.h"


std::string Create_Hash_With_Salt(const std::string& password, const std::string& salt) {
    const int iterations = 1000;
    const int keyLength = 64;

    unsigned char key[keyLength];
    PKCS5_PBKDF2_HMAC_SHA1(
            password.c_str(), password.length(),
            reinterpret_cast<const unsigned char*>(salt.c_str()), salt.length(),
            iterations, keyLength, key
    );

    std::string hash;
    for (unsigned char i : key) {
        char hex[3];
        snprintf(hex, sizeof(hex), "%02x", i);
        hash += hex;
    }
    return hash;
}

std::string Generate_Salt() {
    const int saltLength = 16;

    unsigned char salt[saltLength];
    RAND_bytes(salt, saltLength);

    std::string saltStr;
    for (unsigned char i : salt) {
        char hex[3];
        snprintf(hex, sizeof(hex), "%02x", i);
        saltStr += hex;
    }
    return saltStr;
}