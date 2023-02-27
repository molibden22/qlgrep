#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <iostream>
#include <chrono>

class Stopwatch
{
public:
    using clockType = std::chrono::high_resolution_clock;

    Stopwatch() : start(clockType::now()){}
    ~Stopwatch() { printAplicationRunTime(); }

    void printAplicationRunTime();

private:
    clockType::time_point start;
    clockType::time_point stop;
};

void Stopwatch::printAplicationRunTime()
{
  clockType::time_point stop = clockType::now();
  std::chrono::duration duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  std::cout << "Elapseed time: " << duration.count() << "[ms]" << std::endl;
}

#endif // STOPWATCH_H
