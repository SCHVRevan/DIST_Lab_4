#include <openssl/aes.h>
#include <fstream>
#include <vector>
#include "dir_checker.h"
#include "cipher.h"
using namespace std;

bool cipher::encrypt(const string& file, const string& key) {
    ifstream infile(file, ios::binary);
    vector<unsigned char> data((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    
    AES_KEY aesKey;
    // reinterpret_cast может быть небезопасным (его поведение зависит от реализации компилятора)
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 256, &aesKey);

    unsigned char iv[AES_BLOCK_SIZE] = {0};
    vector<unsigned char> out(data.size());
    AES_cbc_encrypt(data.data(), out.data(), data.size(), &aesKey, iv, AES_ENCRYPT);

    ofstream ofs(file, ios::binary);
    ofs.write(reinterpret_cast<char*>(out.data()), out.size());

    return 1;
}

bool cipher::decrypt(const string& file, const string& key) {
    ifstream infile(file, ios::binary);
    vector<unsigned char> data((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    
    AES_KEY aesKey;
    // reinterpret_cast может быть небезопасным (его поведение зависит от реализации компилятора)
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 256, &aesKey);
    
    unsigned char iv[AES_BLOCK_SIZE] = {0};
    vector<unsigned char> out(data.size());
    AES_cbc_encrypt(data.data(), out.data(), data.size(), &aesKey, iv, AES_DECRYPT);

    ofstream ofs(file, ios::binary);
    ofs.write(reinterpret_cast<char*>(out.data()), out.size());

    return 1;
}
