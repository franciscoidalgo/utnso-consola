#include "consola.h"

#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv) {
  if (argc != 3) {

    printf("Se requieren dos parametros [path del archivo] [tamanio del "
           "proceso]. Solo se recivio %d.\n",
           argc);
    return EXIT_FAILURE;
  }

  parsear_codigo(argv[1]);

  return EXIT_SUCCESS;
}