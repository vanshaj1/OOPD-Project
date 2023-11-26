#pragma once
#include "command_class.h"

class Ls : public CommandClass
{
public:
    Ls(filesystem::path *path);
    void execute(int argc, char *argv[]) override;
    const char *helpText() override;
    void printEntries(const char *dest, bool showHidden = false);
};