#ifndef CIPHER_H
#define CIPHER_H
#include <string>

class cipher {
    public:
        static bool encrypt(const std::string& file, const std::string& key);
        static bool decrypt(const std::string& file, const std::string& key);
};

#endif
