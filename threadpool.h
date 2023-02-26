#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <queue>
#include <string.h>

#include "worker.h"
#include "task.h"

class Threadpool
{
public:
    using sizeType = int;

    Threadpool(sizeType workersCount);

    void addTask(Task task);

    void initWorkers(sizeType workersCount);

private:
    std::queue<Task> tasksQueue;
    std::vector<Worker> workers;

};

#endif // THREADPOOL_H
