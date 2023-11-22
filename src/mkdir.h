#pragma once
#include "command_class.h"

class Mkdir : public CommandClass
{
public:
    Mkdir(filesystem::path *path);
    void execute(int argc, char *argv[]) override;
    const char *helpText() override;
    void createDirectory(const char *path, bool parent = false);
};