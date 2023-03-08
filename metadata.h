#ifndef METADATA_H
#define METADATA_H
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <vector>

class Metadata
{
public:
  Metadata();
  ~Metadata();

  int getSearchedFiles() const;
  int getFilesWithPattern() const;
  int getPatternsNumber() const;
  std::vector<std::list<std::string> > getDataToWriteLog() const;
  std::vector<std::list<std::string> > getDataToWriteResult() const;
  void setPtrToResluts(const std::shared_ptr<std::vector<std::shared_ptr<Metadata>>> &newPtrToResluts);
  void parseFinalData();

private:
  void parseLogData(std::vector<std::list<std::string>>& vec);
  void parseResultData(std::vector<std::list<std::string>>& vec);

public:
  std::list<std::string> logFileData;
  std::vector<std::list<std::string>> resultFileData;
  std::list<int> searchedFiles;
  std::list<int> filesWithPattern;
  std::list<int> patternsNumber;

private:
  std::shared_ptr<std::vector<std::shared_ptr<Metadata>>> ptrToResluts;
  std::vector<std::list<std::string>> dataToWriteLog;
  std::vector<std::list<std::string>> dataToWriteResult;

};

struct vecSizeComparer
{
  bool operator()(const std::list<std::string>& lhs, const std::list<std::string>& rhs) const
  {
    return lhs.size() > rhs.size();
  }
};

#endif // METADATA_H
