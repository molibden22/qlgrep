#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "task.h"
#include "worker.h"
#include "usersettings.h"
#include <chrono>
#include <future>
#include <list>
#include <optional>
#include <string>
#include <vector>

class Threadpool
{
public:

  using PathType = std::filesystem::path;

  Threadpool(int argc, char* argv[]);
  ~Threadpool();

  void addTask(const Task& task);
  std::optional<Task> takeNextTask();
  bool isThereAnyTask() const;

  void initTasksQueue(PathType userPath);
  void initWorkers(int workersCount);
  void initCallbackForWorkers();


private:
  void setUserSettings(int argc, char* argv[]);
  void setListOfDirectoriesToSearchFor(PathType start_path);


private:
  std::list<Task> tasksQueue;

  mutable std::mutex tasksAccessLock;
  std::vector<std::shared_ptr<Worker>> workers;
};

#endif // THREADPOOL_H
