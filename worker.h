#ifndef WORKER_H
#define WORKER_H
#include <iostream>
#include <thread>
#include <list>
#include <fstream>
#include <optional>

#include "task.h"

    using TaskType = std::filesystem::path;

class Worker
{
public:
Worker(int id, std::string name);
~Worker();

  void process();

  void doTask();
  void doWork(Task task);

  void setTaskTaker(std::optional<Task> newTaskTaker);

private:
  void setListOfFilesToSearchTargetInGivenPath(TaskType start_path);
  void openFileAndSearchTarget(std::string fileName, std::string target);

private:
    int id;
    std::list<TaskType> filesList;
    std::optional<Task> taskTaker;

public:
    std::string name;

};

#endif // WORKER_H
