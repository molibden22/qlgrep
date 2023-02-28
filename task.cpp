#include "task.h"

using PathType = std::filesystem::path;

Task::Task(int id, PathType path)
  : id(id)
  , taskPath(path)
{
  //std::cout << "(taskId:" << id << ")";
}

void Task::doWork(Metadata& metadata)
{
  setListOfFilesToSearchTargetInGivenPath(taskPath);
  // search files & get data
  // write data to metadata
}

void Task::setListOfFilesToSearchTargetInGivenPath(PathType path)
{
  for(auto const& dir_entry : std::filesystem::directory_iterator(path))
  {
      if(PathType(dir_entry).extension() != "")
    {
      filesToSearchList.push_back(dir_entry);
      std::cout << "path to filename : " << dir_entry << '\n';
    }
  }
}

