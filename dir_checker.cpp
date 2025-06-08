#include <stdio.h>
#include <sys/types.h> //только для Linux
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/");
    if (!dir) {
        perror("diropen");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
