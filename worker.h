#ifndef WORKER_H
#define WORKER_H
#include "task.h"
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <list>
#include <optional>
#include <thread>

class Worker
{
public:
  using TaskType = std::filesystem::path;

  Worker(int id, const std::string& name);
  ~Worker() noexcept;

  void process();
  void doTask(Task task);
  void doWork(Task task);

  void setTaskTaker(const std::optional<Task>& newTaskTaker);
  std::vector<std::string>& getTaskResultData();

private:
  void setListOfFilesToSearchTargetInGivenPath(TaskType start_path);
  void processInputFile(TaskType filepath, std::string target);

private:
  int id;
  std::string name;
  std::list<TaskType> filesList;
  std::vector<std::string> taskResultsData;
  std::vector<std::string> taskLogData;
  std::optional<Task> taskTaker{std::nullopt};
  std::atomic<bool> stopProcessing;
  std::future<void> future;
};

#endif // WORKER_H
