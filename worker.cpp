#include "worker.h"

Worker::Worker(int id, std::string name) : id (id), name(name)
{
    //doTask(task);
    doTask();
}

void Worker::doTask()//doTask(Task task)
{
    std::cout << "is  doing by: "; // << std::endl;
}
