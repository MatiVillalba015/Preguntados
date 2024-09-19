#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puntos.h"

PuntosPtr crearPuntos() {
    PuntosPtr puntos = (PuntosPtr)malloc(sizeof(struct Puntos));
    if (puntos == NULL) {
        perror("Error al crear puntos");
        exit(1);
    }
    puntos->actual = 0;
    puntos->maximo = 0;

    return puntos;
}

void liberarPuntos(PuntosPtr puntos) {
    free(puntos);
}

void mostrarPuntos(PuntosPtr puntos) {
    printf("PUNTAJE ACTUAL: %d\n", puntos->actual);
    printf("MAXIMO PUNTAJE: %d\n", puntos->maximo);
}

void guardarPuntajeMaximo(int puntajeMaximo, const char *alias) {
    FILE *archivo = fopen("puntaje_maximo.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar el puntaje máximo.\n");
        return;
    }

    fprintf(archivo, "%s,%d\n", alias, puntajeMaximo);

    fclose(archivo);
}

void guardarPuntajeMaximoPuntoExtra(int puntajeMaximo, const char *alias) {
    FILE *archivo = fopen("puntaje_maximo_extra.txt", "a");

    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar el puntaje máximo.\n");
        return;
    }

    fprintf(archivo, "%s,%d\n", alias, puntajeMaximo);

    fclose(archivo);
}

void consultarPuntajeMaximo() {
    FILE *archivo = fopen("puntaje_maximo.txt", "r");

    if (archivo == NULL) {
        printf("NO HAY PUNTAJE MAXIMO TODAVIA.\n");
        return;
    }

    char alias[20];
    int puntajeMaximo;

    printf("PUNTAJES MAS ALTOS:\n");

    while (fscanf(archivo, "%19[^,],%d\n", alias, &puntajeMaximo) == 2) {
        printf("PUNTAJE MAS ALTO: %d (Jugador: %s)\n", puntajeMaximo, alias);
    }

    fclose(archivo);
    archivo = fopen("puntaje_maximo.txt", "w");
    fclose(archivo);

    FILE * archivoExtra = fopen("puntaje_maximo_extra.txt","r");

    if(archivoExtra == NULL){
        printf("Aún no hay un puntaje extra registrado.\n");
        return;
    }

    char aliasExtra[20];
    int puntajeMaximoExtra;

    //printf("Ganador del puntaje extra:\n");

    while (fscanf(archivo, "%19[^,],%d\n", aliasExtra, &puntajeMaximoExtra) == 2) {
        printf("Puntaje extra: %d (Jugador: %s)\n", puntajeMaximoExtra, aliasExtra);
    }

    fclose(archivoExtra);

    archivo = fopen("puntaje_maximo_extra.txt", "w");

    fclose(archivoExtra);


}



void cargarPuntaje(PuntosPtr puntos, const char *alias) {
    FILE *archivo = fopen("puntaje_maximo.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para cargar el puntaje máximo.\n");
        return;
    }

    char linea[100];
    char aliasActual[20];
    int puntajeActual;

    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%[^,],%d\n", aliasActual, &puntajeActual);
        if (strcmp(aliasActual, alias) == 0) {
            puntos->maximo = puntajeActual;
            break;
        }
    }

    fclose(archivo);
}

void guardarPuntaje(PuntosPtr puntos, const char *alias) {
    FILE *archivo = fopen("puntaje_maximo.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar el puntaje máximo.\n");
        return;
    }

    fprintf(archivo, "%s,%d\n", alias, puntos->maximo);

    fclose(archivo);
}



void actualizarPuntajeMaximo(PuntosPtr puntos) {
    if (puntos->actual > puntos->maximo) {
        puntos->maximo = puntos->actual;
    }
}

