#pragma once
#include <filesystem>

using namespace std;

class CommandClass
{
protected:
    std::filesystem::path *currentPath;

public:
    CommandClass(std::filesystem::path *path) : currentPath{path} {}
    virtual void execute(int argc, char *argv[]) = 0;
    virtual const char *helpText() = 0;
};