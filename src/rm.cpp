#include "rm.h"
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;

Rm::Rm(filesystem::path *path) : CommandClass(path) {}

void Rm::execute(int argc, char *argv[])
{
    char *item;
    bool found = false;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            item = argv[i];
            found = true;
            break;
        }
    }

    int c;
    while ((c = getopt(argc, argv, "rh")) != -1)
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
        case 'r':
        {
            if (!found)
            {
                cout << "file/directory not found" << endl;
                return;
            }
            deleteItem(item, true);
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
        deleteItem(item);
    }
}

const char *Rm::helpText()
{
    return "Usage: rm [OPTION]... FILE...\n"
           "Remove(unlink) the FILE.\n\n"
           "-h   Get help text\n"
           "-r recursively delete directories\n\n";
}

void Rm::deleteItem(const char *path, bool recursive)
{
    try
    {
        auto newPath = *currentPath;
        newPath.append(path);
        _deleteItem(newPath, recursive);
    }
    catch (const char *s)
    {
        cout << s << endl;
    }
    catch (const exception &except)
    {
        cout << except.what() << endl;
    }
}

void Rm::_deleteItem(filesystem::path path, bool recursive)
{
    if (filesystem::is_directory(path))
    {
        if (!recursive)
        {
            throw "-r flag required for deleting directories";
        }
    }
    else
    {
        filesystem::remove(path);
        return;
    }

    for (auto const &dirEntry : filesystem::directory_iterator(path))
    {
        _deleteItem(dirEntry.path(), recursive);
    }
    filesystem::remove(path);
}