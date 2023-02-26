#include <iostream>


#include "threadpool.h"


int main(int argc, char* argv[])
{
  int count{4};
  std::filesystem::path path {std::filesystem::current_path()};

  Threadpool threadpool(count);
  threadpool.initTasksQueue(path);
  threadpool.initWorkers(count);


  return 0;
}
