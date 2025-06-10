#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H
#include <string>

// Signelton
class Encryptor {
    Encryptor() {};
    ~Encryptor() {};
    Encryptor(Encryptor const&);
    Encryptor& operator=(Encryptor const&);
    std::string key;
    public:
        static Encryptor& Instance();
        void setKey(const std::string&);
        void encrypt(const std::string&);
        void decrypt(const std::string&);
};

#endif
