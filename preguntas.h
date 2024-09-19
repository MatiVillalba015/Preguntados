#ifndef PREGUNTAS_H_INCLUDED
#define PREGUNTAS_H_INCLUDED

#define TAM 100
#include "respuestas.h"

struct Preguntas;

typedef struct Preguntas * PreguntasPtr;

PreguntasPtr cargarPreguntaNula();
void cargarPreguntasNulas(PreguntasPtr preguntas[],int t);

void cargarPreguntaTxt(PreguntasPtr preguntas[]);
void cargarRespuestasTxt(PreguntasPtr respuesta);

void mostrarPregunta(PreguntasPtr pregunta);
void mostrarPreguntas(PreguntasPtr pregunta[],int t);

int cantidadPreguntas(char * c);
void liberarPreguntas(PreguntasPtr preguntas[],int t);

void shuffleArray(int array[], int size);

///###########################GETTERS###########################

int getNroPregunta(PreguntasPtr pregunta);

int getDificultad(PreguntasPtr pregunta);

char* getPregunta(PreguntasPtr pregunta);

int getCorrecta(PreguntasPtr pregunta);

///###########################SETTERS###########################

void setNroPregunta(PreguntasPtr pregunta, int nuevoNroPregunta);

void setDificultad(PreguntasPtr pregunta, int nuevoDificultad);

void setPregunta(PreguntasPtr pregunta, char nuevoNroPregunta[100]);

void setCorrecta(PreguntasPtr pregunta,int nuevaCorrecta);

#endif // PREGUNTAS_H_INCLUDED
