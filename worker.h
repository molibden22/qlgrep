#ifndef WORKER_H
#define WORKER_H
#include <iostream>
#include "task.h"

class Worker
{
public:
Worker(int id, std::string name);

//void doTask(Task task);
  void doTask();

private:
    int id;

public:
    std::string name;

};


#endif // WORKER_H
