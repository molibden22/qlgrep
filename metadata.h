#ifndef METADATA_H
#define METADATA_H
#include <iostream>
#include <list>
#include <vector>

class Metadata
{
public:
  Metadata();

public:
  std::vector<std::list<std::string>> resultFileData;
  std::vector<std::list<std::string>> logFileData;

  std::list<int> searchedFiles;
  std::list<int> filesWithPattern;
  std::list<int> patternsNumber;
};

#endif // METADATA_H
