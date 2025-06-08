#include <sys/types.h> //только для Linux
#include <dirent.h>
#include <string>
#include <iostream>
using namespace std;

void get_files(const string& path) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(path.c_str());
    if (!dir) {
        perror("diropen");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        cout << entry->d_name << "\n";
    }
    closedir(dir);
    return;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:\n" << argv[0] << " <path>\n";
        return 1;
    }

    get_files(argv[1]);

    return 0;
}
