#include "threadpool.h"
#include <iostream>

int main(int argc, char* argv[])
{
  Threadpool threadpool(argc, argv);

  std::cout << "end" << std::endl;

  return 0;
}
