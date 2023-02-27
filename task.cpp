#include "task.h"

using TaskType = std::filesystem::path;

Task::Task(int id, TaskType path)
  : id(id)
  , taskPath(path)
{
  // std::cout << "(taskId:" << id << ")";
}

void setListOfDirectoriesToSearchFor(PathType start_path);
void setListOfDirectoriesToSearchFor(TaskType start_path)
{
  std::cout << start_path << std::endl;
  for(int i{0}; auto const& dir_entry : std::filesystem::recursive_directory_iterator(start_path))
  {
    TaskType path = dir_entry;
    if(path.filename().extension() == "")
    {
      // tasksQueue.push_back(Task(++i, path));
      //addTask(Task(++i, path));
    }
  }
}



