#include <sys/types.h> //только для Linux
#include <dirent.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<string> get_files(const string& path) {
    vector<string> files;
    DIR *dir;
    struct dirent *entry;
    dir = opendir(path.c_str());
    if (!dir) {
        perror("diropen");
        return files;
    }
    while ((entry = readdir(dir)) != NULL) {
        files.push_back(path + entry->d_name);
    }
    closedir(dir);
    return files;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:\n" << argv[0] << " <path>\n";
        return 1;
    }
    vector<string> files;
    files = get_files(argv[1]);
    for (int i = 0; i < size(files); i++) {
        cout << files[i] << "\n";
    }

    return 0;
}
