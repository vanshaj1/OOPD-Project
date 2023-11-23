#pragma once
#include "command_class.h"

class Cd : public CommandClass
{
public:
    Cd(filesystem::path *path);
    void execute(int argc, char *argv[]) override;
    const char *helpText() override;

    void cd(const char *dest);
};