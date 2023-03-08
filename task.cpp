#include "task.h"

using PathType = std::filesystem::path;

Task::Task(int id, PathType path, std::string target)
  : id(id)
  , taskPath(path)
  , userTarget(target)
{
}

void Task::doWork(Metadata& outdata)
{
  setListOfFilesToSearchTargetInGivenPath(taskPath);
  processInputFileList(filesToSearchList, userTarget, outdata);
}

void Task::setListOfFilesToSearchTargetInGivenPath(PathType path)
{
  for(auto const& dir_entry : std::filesystem::directory_iterator(path))
  {
    if(PathType(dir_entry).extension() != "")
    {
      filesToSearchList.push_back(dir_entry);
    }
  }
}

void Task::processInputFileList(std::list<PathType> filepathlist, std::string target, Metadata& outdata)
{
  std::ifstream inputFile;
  PathType filePath;
  std::string fileName;
  std::string line;
  int lineNumber{0};
  int targetFoundCount{0};
  int searchedFiles{0};
  int filesWithPatternCount{0};

  while(!filepathlist.empty())
  {
    filePath = filepathlist.front();
    fileName = filePath.filename().string();
    filepathlist.pop_front();

    inputFile.open(filePath, std::ios::in);
    if(inputFile.good())
    {
      std::list<std::string> resultList;
      targetFoundCount = 0;
      lineNumber = 0;
      while(!inputFile.eof())
      {
        std::getline(inputFile, line);
        ++lineNumber;
        size_t position{0};
        if(line.find(target, position) != std::string::npos)
        {
          while(position != std::string::npos)
          {
            size_t newPosition = line.find(target, position);
            if(newPosition != std::string::npos)
            {
              ++targetFoundCount;
              position = newPosition + 1;
              resultList.push_back({filePath.string() + " : " + std::to_string(lineNumber) + ": " + line});
            }
            else
              position = newPosition;
          }
        }
      }
      if(targetFoundCount != 0)
      {
        if(outdata.logFileData.empty() == true)
        {
          std::stringstream ss;
          ss << std::this_thread::get_id();
          outdata.logFileData.push_back(ss.str() + ": ");
        }
        outdata.logFileData.push_back({fileName + ", "});
        outdata.resultFileData.push_back(resultList);
        outdata.patternsNumber.push_back(targetFoundCount);
        ++filesWithPatternCount;
      }
      ++searchedFiles;
    }
    else {
      //std::cout << "Failed to open a file!" << std::endl;
    }
    inputFile.close();
  }
  outdata.searchedFiles.push_back(searchedFiles);
  outdata.filesWithPattern.push_back(filesWithPatternCount);
}
