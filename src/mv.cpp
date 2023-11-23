#include "mv.h"
#include <unistd.h>
#include <bits/stdc++.h>

Mv::Mv(filesystem::path *path) : CommandClass(path) {}

void Mv::execute(int argc, char *argv[])
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
    while ((c = getopt(argc, argv, "fhi")) != -1)
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
        case 'f':
        {
            if (count < 2)
            {
                cout << "Invalid arguements" << endl;
                return;
            }
            mv(args, count - 1, args[count - 1], true, false);
            break;
        }
        case 'i':
        {
            if (count < 2)
            {
                cout << "Invalid arguements" << endl;
                return;
            }
            mv(args, count - 1, args[count - 1], false, true);
            break;
        }
        }
    }
    if (optind == 1)
    {
        if (count < 2)
        {
            cout << "Invalid options" << endl;
            return;
        }
        mv(args, count - 1, args[count - 1]);
    }
}

const char *Mv::helpText()
{
    return "Usage: mv [OPTION] SRC DEST\n"
           "   or: mv [OPTION] SRC... DIRECTORY\n"
           "Renames SRC to DEST or moves all SRC to DIRECTORY.\n\n"
           "-h   Get help text\n"
           "-f   Forcibly overwrite\n"
           "-i   Prompt before overwrite\n\n";
}

void Mv::mv(char *src[], int count, const char *dest, bool overwrite, bool interactive)
{
    try
    {
        filesystem::path destPath = *currentPath;
        destPath.append(dest);
        if (!filesystem::exists(destPath.parent_path()))
        {
            cout << "The given destination doesn't exist" << endl;
            return;
        }
        if (count == 1 && !filesystem::is_directory(destPath))
        {
            filesystem::path srcFile = *currentPath;
            srcFile.append(src[0]);

            if (srcFile == destPath)
                return;
            if (!filesystem::exists(srcFile))
            {
                cout << "The given source doesn't exists" << endl;
                return;
            }
            if (!filesystem::exists(destPath) || filesystem::is_regular_file(srcFile) != filesystem::is_regular_file(destPath))
            {
                filesystem::rename(srcFile, destPath);
                return;
            }

            if (!overwrite && !interactive)
            {
                cout << "Already exists, cannot overwrite without -f flag" << endl;
            }
            else if (overwrite)
            {
                filesystem::rename(srcFile, destPath);
            }
            else
            {
                string response;
                do
                {
                    cout << destPath << " will be overwritten, are you sure you want to continue?[y/n]: ";
                    getline(cin, response);
                } while (response != "y" && response != "n");
                if (response == "y")
                {
                    filesystem::rename(srcFile, destPath);
                }
            }
        }

        if (!filesystem::is_directory(destPath))
        {
            cout << "Multiple files cannot be renamed to the same name" << endl;
            return;
        }

        vector<filesystem::path> srcPaths(count);
        for (int i = 0; i < count; i++)
        {
            srcPaths[i] = *currentPath;
            srcPaths[i].append(src[i]);
            if (!filesystem::exists(srcPaths[i]))
            {
                cout << srcPaths[i] << " doesn't exists, skipping" << endl;
                continue;
            }
            bool found = false;
            filesystem::path newPath;
            for (auto &entry : filesystem::directory_iterator(destPath))
            {
                if (srcPaths[i].filename() == entry.path().filename())
                {
                    found = true;
                    newPath = entry.path();
                    break;
                }
            }
            if (!found)
            {
                auto temp = destPath;
                temp.append(srcPaths[i].filename().c_str());
                filesystem::rename(srcPaths[i], temp);
            }
            else
            {
                if (!overwrite && !interactive)
                {
                    cout << "Cannot move " << srcPaths[i] << " as " << newPath << " aready exists, cannot overwrite without -f flag" << endl;
                }
                else if (overwrite)
                {
                    filesystem::rename(srcPaths[i], newPath);
                }
                else
                {
                    string response;
                    do
                    {
                        cout << newPath << " will be overwritten, are you sure you want to continue?[y/n]: ";
                        getline(cin, response);
                    } while (response != "y" && response != "n");
                    if (response == "y")
                    {
                        filesystem::rename(srcPaths[i], newPath);
                    }
                }
            }
        }
    }
    catch (const exception &except)
    {
        cout << except.what() << endl;
    }
}
