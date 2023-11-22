#include "main_class.h"
#include <unistd.h>

MainClass::MainClass() : currentPath{new filesystem::path(filesystem::current_path())}, mkdir(currentPath)
{
}

void MainClass::mainLoop()
{
    while (true)
    {
        cout << (*currentPath).c_str() << "$ ";
        string s;
        getline(std::cin, s);
        if (s == "exit")
            break;
        commandParser(s);
    }
}

void MainClass::commandParser(string &s)
{
    int argc = 1;
    for (auto &c : s)
    {
        if (c == ' ')
        {
            argc++;
        }
    }
    char *argv[argc];
    stringstream str;
    str << s;
    string key;
    int i = 0;
    while (std::getline(str, key, ' '))
    {
        argv[i] = new char[key.size() + 1];
        strcpy(argv[i], key.c_str());
        i++;
    }
    if (!strcmp(argv[0], "mkdir"))
    {
        mkdir.execute(argc, argv);
    }
    else
    {
    }

    for (i = 0; i < argc; i++)
    {
        delete argv[i];
    }
}
