#ifndef TASK_H
#define TASK_H

#include <iostream>

class Task
{
public:
Task(int id);

int getId() {return id;};
int getTask() {return task;};

private:
    int id;
    int task;

};


#endif // TASK_H
