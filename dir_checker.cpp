#include <sys/types.h> //только для Linux
#include <dirent.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/stat.h>
using namespace std;

void recurse(const string& path, vector<string>& files) {
    DIR *dir;
    struct dirent *entry;
    dir = opendir(path.c_str());

    if (!dir) return;

    while ((entry = readdir(dir)) != NULL) {
        string file_path = path + entry->d_name;

        struct stat st; // возвращает информацию о файле или директории
        if (stat(file_path.c_str(), &st) == -1) continue;

        // логический макрос для проверки значения поля
        if (S_ISDIR(st.st_mode)) {
            recurse(file_path, files);
        }
        //  ISFIFO? ISSOCK?
        else if (S_ISREG(st.st_mode)) {
            files.push_back(file_path);
        }
    }
    closedir(dir);
}

vector<string> get_files(const string& path) {
    vector<string> files;
    recurse(path, files);
    return files;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:\n" << argv[0] << " <path>\n";
        return 1;
    }

    vector<string> f;
    f = get_files(argv[1]);

    for (int i = 0; i < size(f); i++) {
        cout << f[i] << "\n";
    }

    return 0;
}
