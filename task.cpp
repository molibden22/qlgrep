#include "task.h"

   using TaskType = std::filesystem::path;

Task::Task(int id, TaskType path) : id(id), taskPath(path)
{
    std::cout << "(task id:" << id << ")";
}
