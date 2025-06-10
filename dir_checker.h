#ifndef DIR_CHECKER_H
#define DIR_CHECKER_H
#include <string>
#include <vector>

class dir_checker {
    static void recurse(const std::string& path, std::vector<std::string>& files);
    public:
        static std::vector<std::string> get_files(const std::string& path);
};

#endif
