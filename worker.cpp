#include "worker.h"

Worker::Worker(int id, std::string name) : id (id), name(name)
{
    doTask(Task(id));
}

void Worker::doTask(Task task)
{
    std::cout << "is  doing by: "; // << std::endl;
}
