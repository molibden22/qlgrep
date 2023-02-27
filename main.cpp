#include "threadpool.h"
#include "stopwatch.h"
#include "usersettings.h"
#include <iostream>

int main(int argc, char* argv[])
{
  Stopwatch stopwatch;
  UserSettings usersettings;

  Threadpool threadpool(usersettings.threadsCount);
  for( int i = 1 ; i < 6 ; ++i)
  {
      threadpool.addTask({i,std::filesystem::current_path()});
  }


  return 0;
}
