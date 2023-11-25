#include "cp.h"
#include <unistd.h>
#include <bits/stdc++.h>

Cp::Cp(filesystem::path *path) : CommandClass(path)
{
}

void Cp::execute(int argc, char *argv[])
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
    while ((c = getopt(argc, argv, "rhv")) != -1)
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
        case 'r':
        {
            if (count < 2)
            {
                cout << "Invalid arguements" << endl;
                return;
            }
            copy(args[0], args[1], true);
            break;
        }
        case 'v':
        {
            if (count < 2)
            {
                cout << "Invalid arguements" << endl;
                return;
            }
            copy(args[0], args[1], true, true);
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
        copy(args[0], args[1]);
    }
}

const char *Cp::helpText()
{
    return "Usage: cp [OPTION] SRC DEST\n"
           "Copies contents from  SRC to DEST.\n\n"
           "-h   Get help text\n"
           "-r   Recursively copy directories\n"
           "-v   Get description of each step(implicitly recursive)\n\n";
}

void Cp::copy(const char *src, const char *dest, bool recursive, bool verbose)
{
    try
    {
        filesystem::path srcPath = *currentPath, destPath = *currentPath;
        srcPath.append(src);
        destPath.append(dest);

        if (!filesystem::is_directory(destPath.parent_path()))
        {
            cout << "Path doesn't exists" << endl;
            return;
        }
        if (filesystem::is_regular_file(dest))
        {
            cout << "Cannot overwrite file" << endl;
            return;
        }
        if (filesystem::is_directory(dest))
        {
            destPath.append(srcPath.filename().c_str());
            _copy(srcPath, destPath, recursive, verbose);
            return;
        }
        _copy(srcPath, destPath, recursive, verbose);
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

void Cp::_copy(filesystem::path src, filesystem::path dest, bool recursive, bool verbose)
{
    if (filesystem::is_directory(src))
    {
        if (!recursive)
        {
            throw "Use the -r or -v flag to copy directories";
        }
    }
    else
    {
        if (verbose)
        {
            cout << "Copying from " << src << " to " << dest << endl;
        }
        ifstream inp(src, ios::binary);
        ofstream otp(dest, ios::binary);
        std::copy(istreambuf_iterator<char>(inp), istreambuf_iterator<char>(), ostreambuf_iterator<char>(otp));
        inp.close();
        otp.close();
        return;
    }
    if (verbose)
    {
        cout << "Creating directory " << dest << endl;
    }
    filesystem::create_directory(dest);
    for (auto &entry : filesystem::directory_iterator(src))
    {
        if (entry.path() == dest)
            continue;
        auto temp = dest;
        temp.append(entry.path().filename().c_str());
        _copy(entry.path(), temp, recursive, verbose);
    }
}