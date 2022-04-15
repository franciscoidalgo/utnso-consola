#include "consola.h"

#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "commons/string.h"

#define TAM_MAXIMO_INSTRUCCION 10
#define CANT_INSTRUCCIONES 6

typedef struct {
  char nombre[TAM_MAXIMO_INSTRUCCION];
  int cantidad_parametros;
} identificador_t;

typedef struct {
  identificador_t identificador;
  int *argumentos;
} instruccion_t;

identificador_t identificadores[] = {
    {"NO_OP", 1}, {"I/O", 1},   {"READ", 1},
    {"COPY", 2},  {"WRITE", 2}, {"EXIT", 0},
};

static identificador_t parsear_identificador(char *nombre) {
  int i;
  for (i = 0; i < CANT_INSTRUCCIONES &&
              !string_equals_ignore_case(nombre, identificadores[i].nombre);
       i++)
    ;
  if (i == CANT_INSTRUCCIONES) {
    printf("Instruccion invalida: %s", nombre);
    exit(EXIT_FAILURE);
  } else {
    return identificadores[i];
  }
}

static instruccion_t *new_instruccion_t(identificador_t id, int *parametros) {
  instruccion_t *instruccion_final =
      (instruccion_t *)malloc(sizeof(instruccion_t));
  instruccion_final->identificador = id;
  instruccion_final->argumentos =
      (int *)malloc(sizeof(int) * id.cantidad_parametros);
  instruccion_final->argumentos = parametros;
  return instruccion_final;
}

static instruccion_t *parsear_instruccion(char *instruccion) {
  char *token;
  int *parametros;

  token = strtok(instruccion, " ");
  identificador_t identificador = parsear_identificador(token);

  parametros = (int *)malloc(identificador.cantidad_parametros * sizeof(int));
  for (int i = 0; i < identificador.cantidad_parametros; i++) {
    token = strtok(NULL, " ");
    if (token == NULL) {
      break;
    }
    parametros[i] = atoi(token);
  }
  printf("Operacion leida: %s\n", identificador.nombre);

  return new_instruccion_t(identificador, parametros);
}

void parsear_codigo(char *file_path) {
  FILE *archivo;
  char *linea;
  size_t longitud = 0;
  ssize_t leido;

  archivo = fopen(file_path, "r");
  if (archivo == NULL) {
    perror("Error al leer archivo");
    exit(EXIT_FAILURE);
  }

  leido = getline(&linea, &longitud, archivo);
  while (leido != -1) {
    parsear_instruccion(linea);
    leido = getline(&linea, &longitud, archivo);
  }

  fclose(archivo);
  if (linea) {
    free(linea);
  }
}
