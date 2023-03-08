#include "worker.h"

Worker::Worker(const int id, const std::string& name)
  : id(id)
  , name(name)
  , stopProcessing(false)
{
  ptrToFinalWorkerResult = std::make_shared<Metadata>();
  future = std::async(std::launch::async, &Worker::process, this);
}
Worker::~Worker() noexcept
{
  stopProcessing = true;
}

void Worker::process()
{
  while(!stopProcessing)
  {
    if(auto task = taskTaker(); task.has_value())
    {
      doTask(*task);
    }
  }
}

void Worker::doTask(Task task)
{
  task.doWork(*ptrToFinalWorkerResult);
}

void Worker::setTaskTaker(const TaskTakerType& newTaskTaker)
{
  taskTaker = newTaskTaker;
}

std::shared_ptr<Metadata>& Worker::getPtrToFinalWorkerResult()
{
  return ptrToFinalWorkerResult;
}
