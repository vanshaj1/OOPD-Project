#pragma once
#include <bits/stdc++.h>
#include <filesystem>
#include "mkdir.h"

using namespace std;

class MainClass
{
    filesystem::path *currentPath;
    void commandParser(string &s);

    Mkdir mkdir;

public:
    MainClass();
    void mainLoop();
};