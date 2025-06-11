#include <iostream>
#include <cstdio>
#include "dir_checker.h"
#include "encryptor.h"
#include "cipher.h"

Encryptor& Encryptor::Instance() {
    static Encryptor e;
    return e;
}

void Encryptor::setKey(const std::string& new_key) {
    key = new_key;
}

void Encryptor::encrypt(const std::string& path) {
    std::vector<std::string> files = dir_checker::get_files(path);
    for (const std::string& file: files) { 
        std::cout << "Encrypting: " << file << '\n';
        if (!(cipher::encrypt(file, key))) std::cout << path << " encryption failed\n";
    }
}

void Encryptor::decrypt(const std::string& path) { 
    std::vector<std::string> files = dir_checker::get_files(path);
    for (const std::string& file: files) { 
        std::cout << "Decrypting: " << file << '\n';
        if (!(cipher::decrypt(file, key))) std::cout << path << " wasn't encrypted with AES256\n";
    }
}
