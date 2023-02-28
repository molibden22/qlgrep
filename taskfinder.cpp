#include "taskfinder.h"

Taskfinder::Taskfinder()
{
}

Taskfinder::PathType Taskfinder::getDirectoryToSearch()
{
  PathType temp = directriesToSearchList.front();
  directriesToSearchList.pop_front();
  return temp;
}

void Taskfinder::setListOfDirectoriesToSearchFor(PathType start_path)
{
  // std::cout << start_path << std::endl;
  for(int i{0}; auto const& dir_entry : std::filesystem::recursive_directory_iterator(start_path))
  {
    PathType path = dir_entry;
    if(path.filename().extension() == "")
    {
      directriesToSearchList.push_back(path);
    }
  }
}
