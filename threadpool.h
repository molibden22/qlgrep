#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <list>
#include <string.h>
#include <chrono>
#include <vector>

#include "worker.h"
#include "task.h"

class Threadpool
{
public:
    using sizeType = int;
    using clockType = std::chrono::high_resolution_clock;
    using TaskType = std::filesystem::path;

    Threadpool(sizeType workersCount);
    ~Threadpool();

    void addTask(Task task);

    void initTasksQueue(TaskType userPath);
    void initWorkers(sizeType workersCount);

    bool isThereAnyTask() const;

    std::string getUserTarget() const {return userTarget;};

private:
    void setListOfDirectoriesToSearchFor(TaskType start_path);
    void printAplicationRunTime();


private:
    clockType::time_point start = clockType::now();
    std::list<Task> tasksQueue;
    std::vector<Worker> workers;
    std::string userTarget{};

};

#endif // THREADPOOL_H
