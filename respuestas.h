#ifndef RESPUESTAS_H_INCLUDED
#define RESPUESTAS_H_INCLUDED

#define TAMRESP 20

struct Respuestas;

typedef struct Respuestas * RespustasPtr;

int seleccionarRespuesta();

RespustasPtr cargarRespuestaNula();
void cargarRespuestasNulas(RespustasPtr respuestas[],int t);

void mostrarRespuesta(RespustasPtr respuesta);
void mostrarRespuestas(RespustasPtr respuestas[],int t);

void liberarRespuestas(RespustasPtr respuestas[],int t);

///###########################GETTERS###########################
int getNroRespuesta(RespustasPtr respuesta);
char* getR1(RespustasPtr respuesta);
char* getR2(RespustasPtr respuesta);
char* getR3(RespustasPtr respuesta);
char* getR4(RespustasPtr respuesta);

///###########################SETTERS###########################

void setNroRespuesta(RespustasPtr respuesta,int nuevoNro);
void setR1(RespustasPtr respuesta, char nuevoR1[15]);
void setR2(RespustasPtr respuesta, char nuevoR2[15]);
void setR3(RespustasPtr respuesta, char nuevoR3[15]);
void setR4(RespustasPtr respuesta, char nuevoR4[15]);

#endif // RESPUESTAS_H_INCLUDED
