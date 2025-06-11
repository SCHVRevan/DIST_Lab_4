#include <iostream>
#include <iomanip>
#include "dir_checker.h"
#include "encryptor.h"
#include "cipher.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage:\n" << argv[0] << " <path> <mode (enc/dec)> <key>\n";
        return 1;
    }

    std::string key = argv[3];
    std::string mode = argv[2];
    std::string f = argv[1];

    Encryptor& e = Encryptor::Instance();
    e.setKey(key);
    
    if (mode == "enc") e.encrypt(f);
    else if (mode == "dec") e.decrypt(f);
    else {
        std::cout << "Typo in:\n" << argv[0] << " <path> <enc/dec> <key>\n";
        std::cout << std::setfill(' ') << std::setw(22) << "↑\n" << std::setfill(' ') << std::setw(18 - (mode.length())/2) << "but got " << mode << "\n";
        return 1;
    }

    return 0;
}
