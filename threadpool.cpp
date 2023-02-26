#include "threadpool.h"

Threadpool::Threadpool(int workersCount)
{
  std::cout << "Threadpool workers count: " << workersCount << std::endl;
}

void Threadpool::initWorkers(sizeType workersCount)
{
  for(sizeType i = 0; i < workersCount; ++i)
  {
    workers.push_back(Worker(i, "[Worker: " + std::to_string(i) + "]"));
    std::cout << workers.at(i).name << std::endl;
  }
}

void Threadpool::addTask(Task task)
{
    tasksQueue.push(task);
}
