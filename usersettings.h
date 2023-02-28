#ifndef USERSETTINGS_H
#define USERSETTINGS_H
#include <filesystem>

class UserSettings
{
public:
  using PathType = std::filesystem::path;

  UserSettings(int argc, char* argv[]);

  void setUserSettings(int argc, char* argv[]);
  PathType getStartPath() { return default_dir; }
  std::string getUserTarget() { return userTarget; }
  std::string getLogFileName() { return logFileName; }
  std::string getResultFileName() { return resultFileName; }
  int getThreadsCount() { return threadsCount; }

public:
  PathType default_dir{std::filesystem::current_path()};
  std::string userTarget{"ma"};
  std::string logFileName{"QLgrep.log"};
  std::string resultFileName{"QLgrep.txt"};
  int threadsCount{4};
};

#endif // USERSETTINGS_H
