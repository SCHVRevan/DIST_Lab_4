#include <openssl/aes.h>
#include <fstream>
#include <vector>
#include "dir_checker.cpp"
using namespace std;

bool encrypt(const string& file, const string& key) {
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

bool decrypt(const string& file, const string& key) {
    ifstream infile(file, ios::binary);
    vector<unsigned char> data((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
    
    AES_KEY aesKey;
    // reinterpret_cast может быть небезопасным (его поведение зависит от реализации компилятора)
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 256, &aesKey);
    
    unsigned char iv[AES_BLOCK_SIZE] = {0};
    vector<unsigned char> out(data.size());
    AES_cbc_encrypt(data.data(), out.data(), data.size(), &aesKey, iv, AES_DECRYPT);

    ofstream ofs(file, ios::binary);
    ofs.write(reinterpret_cast<char*>(out.data()), out.size());

    return 1;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage:\n" << argv[0] << " <path> <mode (enc/dec)> <key>\n";
        return 1;
    }

    string key = argv[3];
    vector<string> f;
    f = get_files(argv[1]);
    bool check;

    if (argv[2] == "enc") {
        check = encrypt(f[0], key);
    }
    else if (argv[2] == "dec") {
        check = decrypt(f[0], key);
    }
    else {
        cout << "Usage:\n" << argv[0] << " <path> <mode (enc/dec)> <key>\n";
        return 1;
    }

    return 0;
}
