#ifndef USERSETTINGS_H
#define USERSETTINGS_H
#include <filesystem>


class UserSettings
{
public:
    using PathType = std::filesystem::path;
    UserSettings();

void setUserSettings(int argc, char* argv[]);


public:
    PathType default_dir{std::filesystem::current_path()};
    std::string userTarget{"ma"};
    std::string logFileName{"QLgrep.log"};
    std::string resultFileName{"QLgrep.txt"};
    int threadsCount{4};


};

#endif // USERSETTINGS_H
