#include <iostream>


#include "threadpool.h"


int main(int argc, char* argv[])
{
  int count{4};
  Threadpool threadpool(count);
  threadpool.initWorkers(count);


  return 0;
}
