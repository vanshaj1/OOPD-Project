#pragma once
#include "command_class.h"

class Rm : public CommandClass
{
    void _deleteItem(std::filesystem::path path, bool recursive);

public:
    Rm(std::filesystem::path *path);

    void execute(int argc, char *argv[]) override;
    const char *helpText() override;
    void deleteItem(const char *path, bool recursive = false);
};