#include <dirent.h>
#include <iostream>
#include <sys/stat.h>
#include "dir_checker.h"
using namespace std;

void dir_checker::recurse(const string& path, vector<string>& files) {
    DIR *dir;
    dir = opendir(path.c_str());
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        //cout << "Watching: " << entry->d_name << "\n";
        if (string(entry->d_name) == "." || string(entry->d_name) == "..") continue;
        
        string file_path = path + "/" + entry->d_name;

        struct stat st; // возвращает информацию о файле или директории
        // случаи несуществующего пути или отсутствия у процесса прав на чтение
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

vector<string> dir_checker::get_files(const string& path) {
    vector<string> files;
    recurse(path, files);
    return files;
}
