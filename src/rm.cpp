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
    while ((c = getopt(argc, argv, "rhvi")) != -1)
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
        case 'i':
        {
            if (!found)
            {
                cout << "file/directory not found" << endl;
                return;
            }
            deleteItem(item, true, false, true);
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
           "-v   Get description of each step(implicitly recursive)\n"
           "-i   Get prompts before every file deletion(implicitly recursive)\n\n";
}

void Rm::deleteItem(const char *path, bool recursive, bool verbose, bool interactive)
{
    try
    {
        auto newPath = *currentPath;
        newPath.append(path);
        _deleteItem(newPath, recursive, verbose, interactive);
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

void Rm::_deleteItem(filesystem::path path, bool recursive, bool verbose, bool interactive)
{
    if (filesystem::is_regular_file(path))
    {
        if (interactive)
        {
            string choice;
            do
            {
                cout << "Delete " << path.lexically_relative(*currentPath) << " ?[y/n]";
                getline(cin, choice);
                if (choice == "N" || choice == "n")
                {
                    return;
                }

            } while (choice != "y" && choice != "Y");
        }
        if (verbose)
        {
            cout << "Deleting file " << path.filename() << endl;
        }
        filesystem::remove(path);
        return;
    }
    if (!filesystem::is_directory(path))
    {
        if (!filesystem::is_directory(path.parent_path()))
        {
            cout << "Path doesn't exists" << endl;
            return;
        }

        string file_name = path.filename().c_str();
        if (file_name.size() < 2 || file_name[0] != '*' || file_name[1] != '.')
        {
            cout << "Wrong arguments" << endl;
            return;
        }

        for (auto &entry : filesystem::directory_iterator(path.parent_path()))
        {
            if (path.extension() != entry.path().extension())
                continue;
            _deleteItem(entry.path(), recursive, verbose, interactive);
        }
        return;
    }
    if (!recursive)
    {
        throw "-r or -v flag required for deleting directories";
    }
    if (verbose)
    {
        cout << "Deleting directory " << path.filename() << ": " << endl;
    }
    for (auto const &dirEntry : filesystem::directory_iterator(path))
    {
        _deleteItem(dirEntry.path(), recursive, verbose, interactive);
    }
    if (filesystem::is_empty(path))
    {
        filesystem::remove(path);
    }
}