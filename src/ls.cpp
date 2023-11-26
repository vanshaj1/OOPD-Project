#include "ls.h"
#include <bits/stdc++.h>
#include <unistd.h>

Ls::Ls(filesystem::path *path) : CommandClass(path) {}

void Ls::execute(int argc, char *argv[])
{
    char *args[argc];
    int count = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] != '-')
        {
            args[count] = argv[i];
            count++;
        }
    }

    int c;
    while ((c = getopt(argc, argv, "ha")) != -1)
    {
        switch (c)
        {
        case 'h':
        {
            if (count)
            {
                cout << "Invalid option -h" << endl;
                return;
            }
            cout << helpText();
            return;
        }
        case 'a':
        {
            if (count > 1)
            {
                cout << "Invalid arguements" << endl;
                return;
            }
            if (count == 1)
            {
                printEntries(args[0], true);
            }
            else
            {
                printEntries("./", true);
            }
            return;
        }
        }
    }
    if (optind == 1)
    {
        if (count > 1)
        {
            cout << "Invalid options" << endl;
            return;
        }
        if (count == 1)
        {
            printEntries(args[0]);
        }
        else
        {
            printEntries("./");
        }
    }
}

const char *Ls::helpText()
{
    return "Usage: ls [OPTION] [DEST]\n"
           "List directories and files in DEST.\n\n"
           "-a   List all directories\n"
           "-h   Get help text\n\n";
}

void Ls::printEntries(const char *dest, bool showHidden)
{
    auto temp = *currentPath;
    temp.append(dest);
    if (!filesystem::exists(temp))
    {
        cout << "Destination doesn't exists" << endl;
        return;
    }
    if (filesystem::is_regular_file(temp))
    {
        temp.lexically_normal();
        cout << temp.filename().c_str() << endl;
        return;
    }

    for (auto &entry : filesystem::directory_iterator(temp))
    {
        if (!showHidden && entry.path().filename().c_str()[0] == '.')
            continue;
        cout << entry.path().filename().c_str() << "  ";
    }
    cout << endl;
}