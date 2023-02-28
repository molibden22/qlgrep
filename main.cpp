#include "printer.h"
#include "stopwatch.h"
#include "threadpool.h"
#include "usersettings.h"
#include "taskfinder.h"
#include <iostream>

int main(int argc, char* argv[])
{
  Stopwatch stopwatch;
  UserSettings usersettings(argc, argv);
  Taskfinder taskfinder;
  taskfinder.setListOfDirectoriesToSearchFor(usersettings.getStartPath());
  Metadata AppResultData;
  Printer printer;

  Threadpool threadpool(usersettings.threadsCount);
  for(int i = 1; i < 6; ++i)
  {
    threadpool.addTask({i, taskfinder.getDirectoryToSearch()});
  }

  return 0;
}
