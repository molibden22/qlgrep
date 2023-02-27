#include "worker.h"

Worker::Worker(int id, const std::string& name)
  : id(id)
  , name(name)
  , stopProcessing(false)
{
  future = std::async(std::launch::async, &Worker::process, this);
}
Worker::~Worker() noexcept
{
  stopProcessing = true;
}

void Worker::process()
{
  std::cout << name << " start processing.." << std::endl;
  while(!stopProcessing)
  {
    if(auto task = taskTaker; task.has_value())
    {
      doTask(*task);
      doWork(*task);
    }
  }
  std::cout << name << " finished task: " << std::endl;
}

void Worker::doTask(Task task)
{
  std::thread::id thread_id = std::this_thread::get_id();
  std::cout << "[>>Thread Id: " << thread_id << "]";
  std::cout << task.getId() << "is  doing by: "; // << std::endl;
}

void Worker::doWork(Task task)
{
  setListOfFilesToSearchTargetInGivenPath(task.getTaskPath());
  for(auto& filePath : filesList)
  {
    processInputFile(filePath, "ma");
    // makeLogFile(std::string fileName, std::string data)
  }
}

void Worker::setTaskTaker(const std::optional<Task>& newTaskTaker)
{
  taskTaker = newTaskTaker;
}

void Worker::setListOfFilesToSearchTargetInGivenPath(TaskType start_path)
{
  start_path.make_preferred();
  for(auto const& dir_entry : std::filesystem::directory_iterator(start_path))
  {
    TaskType path = dir_entry;
    if(path.extension() != "")
    {
      filesList.push_back(dir_entry);
      // std::cout << "---if cond.---> ";
      std::cout << "path to filename : " << path << '\n';
    }
  }
}

void Worker::processInputFile(TaskType filepath, std::string target)
{
  std::ifstream inputFile;
  int lineNumber{};
  std::string line;
  std::string fileName{filepath.filename().string()};
  int found_count{0};

  inputFile.open(fileName, std::ios::in);
  if(inputFile.good())
  {
    std::cout << "File <" << fileName << "> is open." << std::endl;
    int found_count{0};
    while(!inputFile.eof())
    {
      std::getline(inputFile, line);
      lineNumber++;
      if(line.find(target, 0) != std::string::npos)
      {
        found_count++;
        line = std::to_string(lineNumber) + ": " + line;
        taskResultsData.push_back(filepath.string() + line); // collect data
        std::cout << "found count: " << found_count << "--> " << line << std::endl;
      }
    }
    inputFile.close();
  }
  else
    std::cout << "Failed to open a file!" << std::endl;
}

std::vector<std::string>& Worker::getTaskResultData()
{
  return taskResultsData;
}
