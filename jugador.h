#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include <stdbool.h>

#define MAX_PREGUNTAS 100

#include "preguntas.h"

struct Jugador;

typedef struct Jugador * JugadorPtr;

JugadorPtr cargarJugadorNulo();
JugadorPtr cargarJugadorTeclado();
int cantJugadores();
void cargarJugadoresPorTeclado(JugadorPtr jugador[],int t);

void mostrarJugador(JugadorPtr jugador);

void mostrarPreguntasYResponderGlobal(JugadorPtr jugador[],int t);

int determinarGanador(JugadorPtr jugadores[], int t);
void mostrarPreguntasYResponderAleatoria(JugadorPtr jugador);

void generarPreguntaMatematica(char *enunciado, int *respuesta);
void desempate(JugadorPtr jugadores[], int t);

void guardarDatosJugador(JugadorPtr jugador[],int t);
bool verificarDNIExistente(const char* dni_str);
void leerDatosJugador(JugadorPtr jugador[], int t);

void liberarJugador(JugadorPtr jugadores);
void liberarJugadores(JugadorPtr jugadores[],int t);

///###########################GETTERS###########################
int getDni(JugadorPtr jugador);

char* getAlias(JugadorPtr jugador);
///###########################SETTERS###########################

void setDni(JugadorPtr jugador, int nuevoDni);

void setAlias(JugadorPtr jugador, char nuevoAlias[20]);

#endif // JUGADOR_H_INCLUDED
