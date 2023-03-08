#ifndef PRINTER_H
#define PRINTER_H
#include "metadata.h"
#include "usersettings.h"
#include <fstream>
#include <iomanip>
#include <iostream>

class Printer
{
public:
  Printer();
  ~Printer();

  void printManual();
  void getResults(Metadata metadata, UserSettings usersettings);
  void printConsoleOutput();

  void writeDataToLogFile(Metadata metadata);
  void writeDataToResultFile(Metadata metadata);

private:
  int SearchedFiles{};
  int FilesWithPattern{};
  int PatternsNumber{};
  std::string logFileName{};
  std::string resultFileName{};
  int threadsCount{};
};

#endif // PRINTER_H
