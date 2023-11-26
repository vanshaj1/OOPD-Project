#include "rm.h"
#include <unistd.h>
#include <bits/stdc++.h>
#include <thread>

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
    while ((c = getopt(argc, argv, "rhv")) != -1)
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
        case 'v':
        {
            if (!found)
            {
                cout << "file/directory not found" << endl;
                return;
            }
            deleteItem(item, true, true);
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
           "-r   Recursively delete directories\n"
           "-v   Get description of each step(implicitly recursive)\n\n";
}

void Rm::deleteItem(const char *path, bool recursive, bool verbose)
{
    try
    {
        auto newPath = *currentPath;
        newPath.append(path);
        _deleteItem(newPath, recursive, verbose);
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

void Rm::_deleteItem(filesystem::path path, bool recursive, bool verbose)
{
    if (filesystem::is_directory(path))
    {
        if (!recursive)
        {
            throw "-r or -v flag required for deleting directories";
        }
    }
    else
    {
        if (verbose)
        {
            cout << "Deleting file " << path.filename() << endl;
        }
        filesystem::remove(path);
        return;
    }
    if (verbose)
    {
        cout << "Deleting directory " << path.filename() << ": " << endl;
    }
    vector<thread *> threads;
    for (auto const &dirEntry : filesystem::directory_iterator(path))
    {
        if (filesystem::is_regular_file(dirEntry.path()) && currentThreads > factor * totalCores)
        {
            _deleteItem(dirEntry.path(), recursive, verbose);
        }
        else
        {
            currentThreads++;
            thread *th = new thread(&Rm::_deleteItem, *this, dirEntry.path(), recursive, verbose);
            threads.push_back(th);
        }
    }
    for (auto &t : threads)
    {
        t->join();
        currentThreads--;
        delete t;
    }
    filesystem::remove(path);
}