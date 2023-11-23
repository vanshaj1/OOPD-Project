#pragma once
#include <bits/stdc++.h>
#include <filesystem>
#include "mkdir.h"
#include "rm.h"
#include "cp.h"
#include "mv.h"
#include "cd.h"

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

public:
    MainClass();
    void mainLoop();

    ~MainClass();
};