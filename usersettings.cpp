#include "usersettings.h"

using PathType = std::filesystem::path;

UserSettings::UserSettings()
{
}


void UserSettings::setUserSettings(int argc, char* argv[])
{
  std::string argv_input[10];
  for(int i{}; i < argc; ++i)
  {
    argv_input[i] = argv[i];
  }
  int count = 1;
  while(count <= argc)
  {
    if(count == 1)
      userTarget = argv_input[count];
    if(argv_input[count] == "d" || argv_input[count] == "--dir")
    {
      if(argv_input[count + 1] != "")
      {
        default_dir = PathType(argv_input[++count]);
        count++;
      }
    }
    else if(argv_input[count] == "-l" || argv_input[count] == "--log_file")
    {
      logFileName = argv_input[++count] + ".log";
      count++;
    }
    else if(argv_input[count] == "-r" || argv_input[count] == "--result_file")
    {
      resultFileName = argv_input[++count] + ".txt";
      count++;
    }
    else if(argv_input[count] == "-t" || argv_input[count] == "--therads")
    {
      threadsCount = std::stoi(argv_input[++count]);
      count++;
    }
    else
      count++;
  }
}
