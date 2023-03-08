#include "metadata.h"

Metadata::Metadata()
{
}

Metadata::~Metadata()
{
}

int Metadata::getSearchedFiles() const
{
  int sum{};
  for(const auto& vec : *ptrToResluts)
  {
    sum += std::accumulate(vec->searchedFiles.begin(), vec->searchedFiles.end(), 0);
  }
  return sum;
}

int Metadata::getPatternsNumber() const
{
  int sum{};
  for(const auto& vec : *ptrToResluts)
  {
    sum += std::accumulate(vec->patternsNumber.begin(), vec->patternsNumber.end(), 0);
  }
  return sum;
}

int Metadata::getFilesWithPattern() const
{
  int sum{};
  for(const auto& vec : *ptrToResluts)
  {
    sum += std::accumulate(vec->filesWithPattern.begin(), vec->filesWithPattern.end(), 0);
  }
  return sum;
}

void Metadata::parseFinalData()
{
  parseLogData(dataToWriteLog);
  parseResultData(dataToWriteResult);
}

void Metadata::parseLogData(std::vector<std::list<std::string>>& vec)
{
  for(const auto& v : *ptrToResluts)
  {
    vec.push_back(v->logFileData);
  }
  std::sort(vec.begin(), vec.end(), vecSizeComparer());
}

void Metadata::parseResultData(std::vector<std::list<std::string>>& vec)
{
  for(const auto& v : *ptrToResluts)
  {
    for(const auto& list : v->resultFileData)
    {
      vec.push_back(list);
    }
  }
  std::sort(vec.begin(), vec.end(), vecSizeComparer());
}

std::vector<std::list<std::string> > Metadata::getDataToWriteResult() const
{
    return dataToWriteResult;
}

std::vector<std::list<std::string> > Metadata::getDataToWriteLog() const
{
    return dataToWriteLog;
}

void Metadata::setPtrToResluts(const std::shared_ptr<std::vector<std::shared_ptr<Metadata>>>& newPtrToResluts)
{
  ptrToResluts = newPtrToResluts;
}
