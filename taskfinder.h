#ifndef TASKFINDER_H
#define TASKFINDER_H
#include <filesystem>
#include <list>

class Taskfinder
{
public:
  using PathType = std::filesystem::path;

  Taskfinder();

  void setListOfDirectoriesToSearchFor(PathType start_path);
  PathType getDirectoryToSearch();

private:
  PathType start_path{std::filesystem::current_path()};
  std::list<PathType> directriesToSearchList;

};

#endif // TASKFINDER_H
