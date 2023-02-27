#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "task.h"
#include "worker.h"
#include <chrono>
#include <future>
#include <string>
#include <vector>
#include <list>

class Threadpool
{
public:

  Threadpool(int threadsCount);
  ~Threadpool();

  void addTask(const Task& task);

private:
  void initWorkers(int workersCount);
  void initCallbackForWorkers();
  bool isThereAnyTask() const;
  std::optional<Task> takeNextTask();


private:
  std::list<Task> tasksQueue;

  mutable std::mutex tasksAccessLock;
  std::vector<std::shared_ptr<Worker>> workers;
};

#endif // THREADPOOL_H
