#include "printer.h"
#include "stopwatch.h"
#include "taskfinder.h"
#include "threadpool.h"
#include "usersettings.h"
#include <iostream>

int main(int argc, char* argv[])
{
  Stopwatch stopwatch;
  Printer printer;
  if(argc == 1)
  {
    std::cout << "Program needs oligatory parameter PATTERN to run." <<std::endl;
    printer.printManual();
  }
  else if(argc > 10)
  {
    std::cout << "Too many parameters." << std::endl;
    printer.printManual();
  }
  else
  {
    UserSettings usersettings(argc, argv);
    Taskfinder taskFinder;
    taskFinder.setListOfDirectoriesToSearchFor(usersettings.getStartPath());
    Metadata appResultData;
    {
      Threadpool threadpool(usersettings.getThreadsCount());
      appResultData.setPtrToResluts(threadpool.getPtrToVecResultsWorkers());
      int i = 1;
      while(!taskFinder.isDirectoryToSerachEmpty())
      {
        threadpool.addTask({i++, taskFinder.getDirectoryToSearch(), usersettings.getUserTarget()});
      }
    }
    appResultData.parseFinalData();
    printer.getResults(appResultData, usersettings);
    printer.writeDataToLogFile(appResultData);
    printer.writeDataToResultFile(appResultData);
    printer.printConsoleOutput();
  }
  return 0;
}
