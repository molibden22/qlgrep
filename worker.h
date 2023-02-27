#ifndef WORKER_H
#define WORKER_H
#include "task.h"
#include <fstream>
#include <future>
#include <iostream>
#include <list>
#include <optional>
#include <thread>

class Worker
{
public:
  using PathType = std::filesystem::path;
  using OptionalTaskType = std::optional<Task>;
  using TaskTakerType = std::function<OptionalTaskType()>;

  Worker(int id, const std::string& name);
  ~Worker() noexcept;

  void process();
  void doTask(Task task);
  //void doWork(Task task);

  void setTaskTaker(const TaskTakerType& newTaskTaker);
  std::vector<std::string>& getTaskResultData();

private:
  void setListOfFilesToSearchTargetInGivenPath(PathType start_path);
  void processInputFile(PathType filepath, std::string target);

private:
  int id;
  std::string name;
  std::list<PathType> filesList;
  std::vector<std::string> taskResultsData;
  std::vector<std::string> taskLogData;
  TaskTakerType taskTaker{ [](){ return std::nullopt;} };
  std::atomic<bool> stopProcessing;
  std::future<void> future;
};

#endif // WORKER_H
