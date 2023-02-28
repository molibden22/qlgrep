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
    if(auto task = taskTaker(); task.has_value())
    {
      doTask(*task);
    }
  }
  std::cout << name << " finished processing: " << std::endl;
}

void Worker::doTask(Task task)
{
  std::thread::id thread_id = std::this_thread::get_id();
  std::cout << "[>>Thread Id: " << thread_id  << " is doing task: " << task.getId() << "]" << std::endl;
  Metadata outData;
  task.doWork(outData);
  taskResultsData.push_back(outData);
  std::cout << this->name << " finished task: " << task.getId() << std::endl;
}

void Worker::setTaskTaker(const TaskTakerType& newTaskTaker)
{
  taskTaker = newTaskTaker;
}

std::vector<Metadata>& Worker::getTaskResultData()
{
  return taskResultsData;
}
