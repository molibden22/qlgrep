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
  for(int i{0}; auto const& dir_entry : std::filesystem::recursive_directory_iterator(
          start_path, std::filesystem::directory_options::skip_permission_denied))
  {
    if( dir_entry.is_directory() )
    {
      directriesToSearchList.push_back(dir_entry);
    }
  }
}

bool Taskfinder::isDirectoryToSerachEmpty()
{
  return directriesToSearchList.empty();
}
