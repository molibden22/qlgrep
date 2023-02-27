#include "threadpool.h"
#include <filesystem>
#include <list>


using TaskType = std::filesystem::path;

Threadpool::Threadpool(int argc, char* argv[])
{
  int threadsCount = 4;
  //setUserSettings(argc, argv);
  //initTasksQueue(default_dir);
  initWorkers(threadsCount);
  initCallbackForWorkers();
}

Threadpool::~Threadpool()
{
  // while(isThereAnyTask()){
  //     std::this_thread::sleep_for(std::chrono::seconds(1));
  // }
}



void Threadpool::initTasksQueue( UserSettings::PathType default_dir)
{
  setListOfDirectoriesToSearchFor(default_dir);
}

void Threadpool::initWorkers(int workersCount)
{
  for(int i = 0; i < workersCount; ++i)
  {
    workers.push_back(std::make_shared<Worker>(i, "[Worker: " + std::to_string(i) + "]"));
  }
}

void Threadpool::initCallbackForWorkers()
{
  for(auto& worker : workers)
  {
    worker->setTaskTaker(this->takeNextTask());
  }
}

bool Threadpool::isThereAnyTask() const
{
  auto lock = std::lock_guard(tasksAccessLock);
  return !tasksQueue.empty();
}

void Threadpool::addTask(const Task& task)
{
  auto lock = std::lock_guard(tasksAccessLock);
  tasksQueue.push_back(task);
}

std::optional<Task> Threadpool::takeNextTask()
{
  if(isThereAnyTask())
  {
    auto task = tasksQueue.front();
    tasksQueue.pop_front();
    return task;
  }
  return std::nullopt;
  std::cout << "No more tasks available";
}

void Threadpool::setListOfDirectoriesToSearchFor(TaskType start_path)
{
  std::cout << start_path << std::endl;
  for(int i{0}; auto const& dir_entry : std::filesystem::recursive_directory_iterator(start_path))
  {
    TaskType path = dir_entry;
    if(path.filename().extension() == "")
    {
      // tasksQueue.push_back(Task(++i, path));
      addTask(Task(++i, path));
    }
  }
}


