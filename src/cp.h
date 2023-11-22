#pragma once
#include "command_class.h"

class Cp : public CommandClass
{
    void _copy(filesystem::path src, filesystem::path dest, bool recursive, bool verbose);

public:
    Cp(filesystem::path *path);
    void execute(int argc, char *argv[]) override;
    const char *helpText() override;
    void copy(const char *src, const char *dest, bool recursive = false, bool verbose = false);
};