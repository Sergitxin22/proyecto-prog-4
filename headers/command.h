#ifndef COMMAND_H
#define COMMAND_H

#include "status.h"

class Command
{
private:
    char *name;
    Status (*commandPtr)(int argc, const char **args);

public:
    Command(const char *name, Status (*commandPtr)(int argc, const char **args));
    ~Command();

    const char *getName() const;
    Status execute(int argc, const char **args) const;
};

#endif
