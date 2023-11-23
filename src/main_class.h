#pragma once
#include <bits/stdc++.h>
#include <filesystem>
#include "mkdir.h"
#include "rm.h"
#include "cp.h"
#include "mv.h"

using namespace std;

class MainClass
{
    filesystem::path *currentPath;
    void commandParser(string &s);

    Mkdir mkdir;
    Rm rm;
    Cp cp;
    Mv mv;

public:
    MainClass();
    void mainLoop();
};