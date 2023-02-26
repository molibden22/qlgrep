#include "threadpool.h"
#include <list>
#include <filesystem>

    using clockType = std::chrono::high_resolution_clock;
    using TaskType = std::filesystem::path;

Threadpool::Threadpool(int workersCount)
{
    std::cout << "Threadpool workers count: " << workersCount << std::endl;
}

Threadpool::~Threadpool()
{
    //consoleOutput();
    printAplicationRunTime();
}

void Threadpool::initTasksQueue(TaskType userPath)
{
    setListOfDirectoriesToSearchFor(userPath);

}

void Threadpool::initWorkers(sizeType workersCount)
{
  for(sizeType i = 0; i < workersCount; ++i)
  {
    workers.push_back(Worker(i, "[Worker: " + std::to_string(i) + "]"));
    std::cout << workers.at(i).name << std::endl;
  }
}

bool Threadpool::isThereAnyTask() const
{
    return !tasksQueue.empty();
}

void Threadpool::addTask(Task task)
{
    tasksQueue.push_back(task);
}

void Threadpool::printAplicationRunTime()
{
    clockType::time_point stop = clockType::now();
    std::chrono::duration duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time elapsed: " << duration.count() << "[ms]" << std::endl;
}

void Threadpool::setListOfDirectoriesToSearchFor(TaskType start_path) {
    std::cout << start_path << std::endl; // location form user -> argc
    for (int i{0}; auto const& dir_entry : std::filesystem::recursive_directory_iterator(start_path)) {
        TaskType path = dir_entry;
        if (path.filename().extension() == "") {
            tasksQueue.push_back(Task(++i,path));
            //std::cout << "---if cond.---> ";
            //std::cout << "path filename : " << path << '\n';
        }
    }
    std::cout << "---------path list of Directories--------------------\n";
    for (auto const& task : tasksQueue) {
        std::cout << task.getTaskPath() << '\n';
    }
}
