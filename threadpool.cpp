#include "threadpool.h"
#include <filesystem>
#include <list>

using clockType = std::chrono::high_resolution_clock;
using TaskType = std::filesystem::path;

Threadpool::Threadpool(int argc, char* argv[])
{
  setUserSettings(argc, argv);
  initTasksQueue(default_dir);
  initWorkers(threadsCount);
  initCallbackForWorkers();
}

Threadpool::~Threadpool()
{
  // while(isThereAnyTask()){
  //     std::this_thread::sleep_for(std::chrono::seconds(1));
  // }
  printConsoleOutput();
  printAplicationRunTime();
}

void Threadpool::setUserSettings(int argc, char* argv[])
{
  std::string argv_input[10];
  for(int i{}; i < argc; ++i)
  {
    argv_input[i] = argv[i];
  }
  int count = 1;
  while(count <= argc)
  {
    if(count == 1)
      userTarget = argv_input[count];
    if(argv_input[count] == "d" || argv_input[count] == "--dir")
    {
      if(argv_input[count + 1] != "")
      {
        default_dir = TaskType(argv_input[++count]);
        count++;
      }
    }
    else if(argv_input[count] == "-l" || argv_input[count] == "--log_file")
    {
      logFileName = argv_input[++count] + ".log";
      count++;
    }
    else if(argv_input[count] == "-r" || argv_input[count] == "--result_file")
    {
      resultFileName = argv_input[++count] + ".txt";
      count++;
    }
    else if(argv_input[count] == "-t" || argv_input[count] == "--therads")
    {
      threadsCount = std::stoi(argv_input[++count]);
      count++;
    }
    else
      count++;
  }
}

void Threadpool::initTasksQueue(TaskType userPath)
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

void Threadpool::printAplicationRunTime()
{
  clockType::time_point stop = clockType::now();
  std::chrono::duration duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Elapseed time: " << duration.count() << "[ms]" << std::endl;
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

void Threadpool::printManual()
{
  std::cout << "------------- Manual --------------\n"
            << "Usage: QLgrep PATTERN [options]... \n"
            << "Example: QLgrep 'Ala' -d c:// -l new-log -r new-result -t 4\n";
  std::cout << std::left << std::setw(45) << "-d , --dir <directory patch> "
            << "directory to search with subdirectories\n"
            << std::setw(45) << "-l , --log_file <log_file_name> "
            << "set log_file name\n"
            << std::setw(45) << "-r , --result_file <result_file_name> "
            << "set result_file name\n"
            << std::setw(45) << "-t , --threads <threads number> "
            << "number of threads in the pool\n";
}

void Threadpool::printConsoleOutput()
{
  std::string SearchedFiles = "6";
  std::string FilesWithPattern = "4";
  std::string PatternsNumber = "7";

  std::cout << "Searched files: " << SearchedFiles << "\nFiles with pattern: " << FilesWithPattern
            << "\nPatterns number: " << PatternsNumber << "\nResult file: " << resultFileName
            << "\nLog file: " << logFileName << "\nUsed threads: " << threadsCount << "\n";
}
