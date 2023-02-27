#include "printer.h"

Printer::Printer()
{
}

void Printer::printManual()
{
  std::cout << "------------- Manual --------------\n"
            << "Usage: QLgrep PATTERN [options]... \n"
            << "Example: QLgrep 'Ala' -d c:// -l new-log -r new-result -t 4\n";
  std::cout << std::left << std::setw(45) << "-d , --dir <directory patch> "
            << "directory to search with subdirectories\n"
            << std::setw(45) << "-l , --log_file <log_file_name> "
            << "set log_file name\n"
            << std::setw(45) << "-r , --result_file <result_file_name> "
            << "set result_file name\n"
            << std::setw(45) << "-t , --threads <threads number> "
            << "number of threads in the pool\n";
}

void Printer::printConsoleOutput()
{
  std::string SearchedFiles = "searched files";
  std::string FilesWithPattern = "files with pattern";
  std::string PatternsNumber = "patterns number";

  std::cout << "Searched files: " << SearchedFiles << "\nFiles with pattern: " << FilesWithPattern
            << "\nPatterns number: " << PatternsNumber << "\nResult file: " << "resultFileName"
            << "\nLog file: " << "logFileName" << "\nUsed threads: " << "threadsCount" << "\n";
}
