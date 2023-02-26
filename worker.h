#ifndef WORKER_H
#define WORKER_H
#include <iostream>
#include <thread>
#include <list>
#include <fstream>

#include "task.h"

    using TaskType = std::filesystem::path;


class Worker
{
public:
Worker(int id, std::string name);
~Worker();

  void process();
  void doTask(Task task);

  void doWork(Task task);


private:
  void setListOfFilesToSearchTargetInGivenPath(TaskType start_path);
  void openFileAndSearchTarget(std::string fileName, std::string target);

private:
    int id;
    std::list<TaskType> filesList;

public:
    std::string name;

};


#endif // WORKER_H
