#ifndef WORKER_H
#define WORKER_H
#include "task.h"
#include "metadata.h"
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

  Worker(const int id, const std::string& name);
  ~Worker() noexcept;

  void setTaskTaker(const TaskTakerType& newTaskTaker);
  std::shared_ptr<Metadata>& getPtrToFinalWorkerResult();

private:
  void process();
  void doTask(Task task);

private:
  int id;
  std::string name;
  std::shared_ptr<Metadata> ptrToFinalWorkerResult;
  TaskTakerType taskTaker{ [](){ return std::nullopt;} };
  std::atomic<bool> stopProcessing;
  std::future<void> future;
};

#endif // WORKER_H
