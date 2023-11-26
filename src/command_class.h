#pragma once
#include <filesystem>
#include <thread>

using namespace std;

class CommandClass
{
protected:
    std::filesystem::path *currentPath;
    unsigned int totalCores;
    int currentThreads = 0;
    int factor = 3;

public:
    CommandClass(std::filesystem::path *path) : currentPath{path}, totalCores{thread::hardware_concurrency()} {}
    virtual void execute(int argc, char *argv[]) = 0;
    virtual const char *helpText() = 0;
};