#include <iostream> 
#include <string>
#include "dir_checker.h"
#include "cipher.h"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage:\n" << argv[0] << " <path> <mode (enc/dec)> <key>\n";
        return 1;
    }

    std::string key = argv[3];
    std::vector<std::string> f;
    f = dir_checker::get_files(argv[1]);
    
    if (static_cast<std::string>(argv[2]) == "enc") {
        cipher::encrypt(f[0], key);
    }
    else if (static_cast<std::string>(argv[2]) == "dec") {
        if (!(cipher::decrypt(f[0], key))) {
            std::cout << f[0] << " wasn't encrypted with AES256\n";
        }
    }
    else {
        std::cout << "Usage:\n" << argv[0] << " <path> <mode (enc/dec)> <key>\n";
        return 1;
    }

    return 0;
}
