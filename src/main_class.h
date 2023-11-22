#pragma once
#include <bits/stdc++.h>
#include <filesystem>
#include "mkdir.h"
#include "rm.h"

using namespace std;

class MainClass
{
    filesystem::path *currentPath;
    void commandParser(string &s);

    Mkdir mkdir;
    Rm rm;

public:
    MainClass();
    void mainLoop();
};