#include "threadpool.h"

Threadpool::Threadpool(int threadsCount)
{
  initWorkers(threadsCount);
  initCallbackForWorkers();
}

Threadpool::~Threadpool()
{
   while(isThereAnyTask()){
       std::this_thread::sleep_for(std::chrono::seconds(1));
   }
}

void Threadpool::addTask(const Task& task)
{
  auto lock = std::lock_guard(tasksAccessLock);
  tasksQueue.push_back(task);
}

void Threadpool::initWorkers(int workersCount)
{
  for(int i = 0; i < workersCount; ++i)
  {
    workers.push_back(std::make_shared<Worker>(i, "[Worker: " + std::to_string(i) + "]"));
  }
}

void Threadpool::initCallbackForWorkers()
{
  for(auto& worker : workers)
  {
    worker->setTaskTaker([this](){return takeNextTask();});
  }
}

bool Threadpool::isThereAnyTask() const
{
  auto lock = std::lock_guard(tasksAccessLock);
  return !tasksQueue.empty();
}

std::optional<Task> Threadpool::takeNextTask()
{
  if(isThereAnyTask())
  {
    auto task = tasksQueue.front();
    tasksQueue.pop_front();
    return task;
  }
  //std::cout << "No more tasks available";
  return std::nullopt;
}
