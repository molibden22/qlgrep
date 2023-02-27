#include "threadpool.h"
#include "stopwatch.h"
#include <iostream>

int main(int argc, char* argv[])
{
  Stopwatch stopwatch;

  Threadpool threadpool(argc, argv);


  std::cout << "end" << std::endl;
  return 0;
}
