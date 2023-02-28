#ifndef TASK_H
#define TASK_H
#include <functional>
#include <filesystem>
#include <iostream>
#include <list>
#include "metadata.h"

using PathType = std::filesystem::path;

class Task
{
public:
  Task(int id, PathType path);

  int getId() const { return id; };
  PathType getTaskPath() const { return taskPath; };

  void doWork(Metadata& metadata);

  void setListOfFilesToSearchTargetInGivenPath(PathType path);

private:
  int id;
  PathType taskPath;
  std::list<PathType> filesToSearchList;
};

#endif // TASK_H


