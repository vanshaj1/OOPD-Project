#pragma once
#include "command_class.h"

class Mv : public CommandClass
{
public:
    Mv(filesystem::path *path);
    void execute(int argc, char *argv[]) override;
    const char *helpText() override;

    void mv(char *src[], int count, const char *dest, bool overwrite = false, bool interactive = false);
};