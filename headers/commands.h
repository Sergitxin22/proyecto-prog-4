#ifndef COMMANDS_H
#define COMMANDS_H

#include "status.h"

Status ver_cmd(int argc, const char **args);
Status mkdir_cmd(int argc, const char **args);
Status print_cmd(int argc, const char **args);
Status writeline_cmd(int arc, const char **args);
Status man_cmd(int arc, const char **args);
Status printdir_cmd(int argc, const char **args);
Status cat_cmd(int arc, const char **args);
Status cd_cmd(int argc, const char **args);
Status admin_cmd(int argc, const char **args);
Status listdir_cmd(int argc, const char **args);
Status printcommands_cmd(int argc, const char **args);
Status login_cmd(int argc, const char **args);
Status clear_cmd(int argc, const char **args);
Status printuser_cmd(int argc, const char **args);
#endif
