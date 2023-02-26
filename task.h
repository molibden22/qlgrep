#ifndef TASK_H
#define TASK_H

#include <filesystem>
#include <iostream>

using TaskType = std::filesystem::path;

class Task
{
public:
  Task(int id, TaskType path);

  int getId() const { return id; };
  TaskType getTaskPath() const { return taskPath; };

private:
  int id;
  TaskType taskPath;
};

#endif // TASK_H
