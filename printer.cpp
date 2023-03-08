#include "printer.h"

Printer::Printer()
{
}

Printer::~Printer()
{
}

void Printer::printManual()
{
  std::cout << "------------- Manual --------------\n"
            << "Usage: QLgrep PATTERN [options]... \n"
            << "Example: QLgrep target -d c:// -l new-log -r new-result -t 4\n";
  std::cout << std::left << std::setw(45) << "-d , --dir <directory patch> "
            << "directory to search, including subdirectories\n"
            << std::setw(45) << "-l , --log_file <log_file_name> "
            << "set log_file name\n"
            << std::setw(45) << "-r , --result_file <result_file_name> "
            << "set result_file name\n"
            << std::setw(45) << "-t , --threads <threads number> "
            << "number of threads in the pool (1-4)\n";
}

void Printer::printConsoleOutput()
{
  std::cout << "\nSearched files: " << SearchedFiles
            << "\nFiles with pattern: " << FilesWithPattern
            << "\nPatterns number: " << PatternsNumber
            << "\nResult file: " << resultFileName
            << "\nLog file: " << logFileName
            << "\nUsed threads: " << threadsCount << "\n";
}

void Printer::getResults(Metadata metadata, UserSettings usersettings)
{
  SearchedFiles = metadata.getSearchedFiles();
  FilesWithPattern = metadata.getFilesWithPattern();
  PatternsNumber = metadata.getPatternsNumber();
  resultFileName = usersettings.getResultFileName();
  logFileName = usersettings.getLogFileName();
  threadsCount = usersettings.getThreadsCount();
}

void Printer::writeDataToLogFile(Metadata metadata)
{
  std::string fileName = logFileName;
  std::fstream file;
  file.open(fileName, std::ios::out);
  if(file.good())
  {
    for(const auto& list : metadata.getDataToWriteLog())
    {
      for(auto& str : list)
      {
        file << str;
      }
      file << "\n";
    }
    file.close();
  }
  else
    std::cout << "Failed to create " << fileName << " file!\n";
}

void Printer::writeDataToResultFile(Metadata metadata)
{
  std::string fileName = resultFileName;
    std::fstream file;
  file.open(fileName, std::ios::out);
  if(file.good())
  {
    // std::cout << "File: " << fileName << " created, open to write.\n";
    for(const auto& list : metadata.getDataToWriteResult())
    {
      for(auto& str : list)
      {
        file << str << "\n";
      }
    }
    file.close();
    // std::cout << "Data writed, file: " << fileName <<  " closed.\n";
  }
  else
    std::cout << "Failed to create " << fileName << " file!\n";
}
