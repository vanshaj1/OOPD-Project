#pragma once
#include <bits/stdc++.h>
#include <filesystem>
#include "mkdir.h"
#include "rm.h"
#include "cp.h"
#include "mv.h"
#include "cd.h"
#include "ls.h"

using namespace std;

class MainClass
{
    filesystem::path *currentPath;
    void commandParser(string &s);

    Mkdir mkdir;
    Rm rm;
    Cp cp;
    Mv mv;
    Cd cd;
    Ls ls;

public:
    MainClass();
    void mainLoop();

    ~MainClass();
};