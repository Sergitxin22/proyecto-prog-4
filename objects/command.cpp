#include "../headers/command.h"
#include <iostream>
#include <string.h>
using namespace std;

Command::Command(const char *name, Status (*commandPtr)(int, const char **))
{
    this->name = new char[strlen(name) + 1];
    strcpy((char *)this->name, name);
    this->commandPtr = commandPtr;
}

Command::~Command()
{
    delete[] name;
}

const char *Command::getName() const
{
    return name;
}

Status Command::execute(int argc, const char **args) const
{
    return commandPtr(argc, args);
}
