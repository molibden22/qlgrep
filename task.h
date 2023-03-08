#ifndef TASK_H
#define TASK_H
#include "metadata.h"
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <thread>

using PathType = std::filesystem::path;

class Task
{
public:
  Task(int id, PathType path, std::string target);

  int getId() const { return id; };
  PathType getTaskPath() const { return taskPath; };
  void doWork(Metadata& metadata);
  void setListOfFilesToSearchTargetInGivenPath(PathType path);
  void processInputFileList(std::list<PathType> filepathlist, std::string target, Metadata& outdata);

private:
  int id;
  PathType taskPath;
  std::string userTarget{};
  std::list<PathType> filesToSearchList;
};

#endif // TASK_H
