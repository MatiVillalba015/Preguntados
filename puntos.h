#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

#include "puntos.h"

struct Puntos{

    int actual;
    int maximo;
    int codPuntos;

};

typedef struct Puntos * PuntosPtr;

PuntosPtr crearPuntos();

void mostrarPuntos(PuntosPtr puntos);

void actualizarPuntajeMaximo(PuntosPtr puntos);

void guardarPuntajeMaximo(int puntajeMaximo, const char *alias);
void guardarPuntajeMaximoPuntoExtra(int puntajeMaximo, const char *alias);

void cargarPuntaje(PuntosPtr puntos, const char *alias);
void guardarPuntaje(PuntosPtr puntos, const char *alias);

void consultarPuntajeMaximo();

void liberarPuntos(PuntosPtr puntos);


#endif // PUNTOS_H_INCLUDED
