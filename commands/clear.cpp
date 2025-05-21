
#include <stdio.h>
#include "../headers/status.h"

Status clear_cmd(int argc, const char **args)
{

  if (argc > 1)
  {
    fprintf(stderr, "clear: incorrect number of arguments\n");
    return Status(1);
  }

  // Limpiar la pantalla
  return Status(0, "\e[1;1H\e[2J");
}