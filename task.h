#ifndef TASK_H
#define TASK_H
#include <functional>
#include <filesystem>
#include <iostream>

using PathType = std::filesystem::path;

class Task
{
public:
  Task(int id, PathType path);

  int getId() const { return id; };
  PathType getTaskPath() const { return taskPath; };

private:
  int id;
  PathType taskPath;
};

#endif // TASK_H


