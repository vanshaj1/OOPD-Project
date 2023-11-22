
#include "mkdir.h"
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

Mkdir::Mkdir(filesystem::path *path) : CommandClass(path) {}

void Mkdir::execute(int argc, char *argv[])
{
    char *directory;
    bool found = false;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            directory = argv[i];
            found = true;
            break;
        }
    }

    int c;
    while ((c = getopt(argc, argv, "hp")) != -1)
    {
        switch (c)
        {
        case 'h':
        {
            if (found)
            {
                cout << "Invalid option -h" << endl;
                return;
            }
            cout << helpText();
            break;
        }
        case 'p':
        {
            if (!found)
            {
                cout << "Directory path not found" << endl;
                return;
            }
            createDirectory(directory, true);
            break;
        }
        }
    }
    if (optind == 1)
    {
        if (!found)
        {
            cout << "Invalid options" << endl;
            return;
        }
        createDirectory(directory);
    }
}
const char *Mkdir::helpText()
{
    return "Usage: mkdir [OPTION]... DIRECTORY...\n"
           "Create the DIRECTORY(ies), if they do not already exits\n\n"
           "-p   make parent directories if required\n\n";
}

void Mkdir::createDirectory(const char *path, bool parent)
{
    filesystem::path newPath = *currentPath;
    try
    {
        newPath.append(path);
        if (parent)
        {
            filesystem::create_directories(newPath);
        }
        else
        {
            filesystem::create_directory(newPath);
        }
    }
    catch (const exception &except)
    {
        cout << except.what() << endl;
    }
}