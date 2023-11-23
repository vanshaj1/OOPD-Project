#include "cd.h"
#include <unistd.h>
#include <bits/stdc++.h>

Cd::Cd(filesystem::path *path) : CommandClass(path) {}

void Cd::execute(int argc, char *argv[])
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
    while ((c = getopt(argc, argv, "h")) != -1)
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
            break;
        }
        }
    }
    if (optind == 1)
    {
        if (count != 1)
        {
            cout << "Invalid options" << endl;
            return;
        }
        cd(args[0]);
    }
}

const char *Cd::helpText()
{
    return "Usage: cd DEST\n"
           "   or: cd -h\n"
           "Change current path to the given one.\n\n"
           "-h   Get help text\n\n";
}

void Cd::cd(const char *dest)
{
    auto temp = *currentPath;
    temp.append(dest);
    if (!filesystem::is_directory(temp))
    {
        cout << "Directory doesn't exists" << endl;
        return;
    }
    currentPath->append(dest);
    *currentPath = currentPath->lexically_normal();
}
