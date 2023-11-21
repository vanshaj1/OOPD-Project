#include <bits/stdc++.h>
#include <filesystem>

using namespace std;

class MainClass
{
    filesystem::path currentPath;

public:
    MainClass();
    void mainLoop();
    void commandParser(string &s);
};