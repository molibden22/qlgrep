#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "task.h"
#include "worker.h"
#include <chrono>
#include <future>
#include <list>
#include <optional>
#include <string>
#include <vector>

class Threadpool
{
public:
  using clockType = std::chrono::high_resolution_clock;
  using TaskType = std::filesystem::path;

  Threadpool(int argc, char* argv[]);
  ~Threadpool();

  void addTask(const Task& task);
  std::optional<Task> takeNextTask();
  bool isThereAnyTask() const;

  void initTasksQueue(TaskType userPath);
  void initWorkers(int workersCount);
  void initCallbackForWorkers();

  std::string getUserTarget() const { return userTarget; };

private:
  void setUserSettings(int argc, char* argv[]);
  void setListOfDirectoriesToSearchFor(TaskType start_path);
  void printAplicationRunTime();
  void printManual();
  void printConsoleOutput();

private:
  clockType::time_point start = clockType::now();
  TaskType default_dir{std::filesystem::current_path()};
  std::string userTarget{"ma"};
  std::string logFileName{"QLgrep.log"};
  std::string resultFileName{"QLgrep.txt"};
  int threadsCount{4};
  std::list<Task> tasksQueue;

  mutable std::mutex tasksAccessLock;
  std::vector<std::shared_ptr<Worker>> workers;
};

#endif // THREADPOOL_H
