#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "task.h"
#include "worker.h"
#include <chrono>
#include <future>
#include <list>
#include <memory>
#include <string>
#include <vector>

class Threadpool
{
public:
  Threadpool(int threadsCount);
  ~Threadpool();

  void addTask(const Task& task);
  std::shared_ptr<std::vector<std::shared_ptr<Metadata>>>& getPtrToVecResultsWorkers() { return ptrToVecResultsWorkers;}

private:
  void initWorkers(int workersCount);
  void initCallbackForWorkers();
  bool isThereAnyTask() const;
  std::optional<Task> takeNextTask();

private:
  std::shared_ptr<std::vector<std::shared_ptr<Metadata>>> ptrToVecResultsWorkers;
  std::list<Task> tasksQueue;
  mutable std::mutex tasksAccessLock;
  std::vector<std::shared_ptr<Worker>> workers;
};

#endif // THREADPOOL_H
