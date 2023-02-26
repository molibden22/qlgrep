#include "worker.h"


Worker::Worker(int id, std::string name) : id (id), name(name)
{
    //doTask(task);
}
Worker::~Worker()
{

}

void Worker::process()
{
    std::cout << name << " start processing.." << std::endl;

    std::cout << name << " finished task: " << std::endl;
}

void Worker::doTask(Task task)
{
    std::thread::id thread_id = std::this_thread::get_id();
    std::cout << "[>>Thread Id: "<< thread_id << "]";
    std::cout << "is  doing by: "; // << std::endl;
}

void Worker::doWork(Task task)
{
    setListOfFilesToSearchTargetInGivenPath(task.getTaskPath());
}

void Worker::setListOfFilesToSearchTargetInGivenPath(TaskType start_path){
    start_path.make_preferred();
    for (auto const& dir_entry : std::filesystem::directory_iterator(start_path)) {
        TaskType path = dir_entry;
        if (path.extension() != "") {
            filesList.push_back(dir_entry);
            //std::cout << "---if cond.---> ";
            std::cout << "path to filename : " << path << '\n';
        }
    }
}

void Worker::openFileAndSearchTarget(std::string fileName, std::string target){
    std::ifstream file;
    int lineNumber{};
    std::string line;
    std::string path;
    int found_count {0};

    file.open(fileName, std::ios::in);
    if (file.good()) {
        std::cout << "File <" << fileName << "> is open." << std::endl;
        int found_count {0};
        while (!file.eof()) {
            std::getline(file, line); // pobieranie z pliku  1 linii
            lineNumber++;
            //szukanie w linii
            if (line.find(target, 0) != std::string::npos) {
                found_count++;
                line = std::to_string(lineNumber) + ": " + line;
                std::cout << "found count: " << found_count << "--> " << line << std::endl;
            }
        }
        file.close();
    }
    else std::cout << "Failed to open a file!" << std::endl;
}





