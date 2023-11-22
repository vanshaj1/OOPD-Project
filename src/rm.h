#pragma once
#include "command_class.h"

class Rm : public CommandClass
{
    void _deleteItem(filesystem::path path, bool recursive, bool verbose);

public:
    Rm(filesystem::path *path);

    void execute(int argc, char *argv[]) override;
    const char *helpText() override;
    void deleteItem(const char *path, bool recursive = false, bool verbose = false);
};