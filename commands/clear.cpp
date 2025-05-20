
#include <stdio.h>

int clear_cmd(int argc, const char **args)
{

  if (argc > 1)
  {
    fprintf(stderr, "clear: incorrect number of arguments\n");
    return 1;
  }

  // Limpiar la pantalla
  printf("\e[1;1H\e[2J");
  return 0;
}