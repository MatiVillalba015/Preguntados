#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "respuestas.h"

struct Respuestas{

    int nroRespuestas;
    char r1[15];
    char r2[15];
    char r3[15];
    char r4[15];

};

int seleccionarRespuesta(){

    int seleccion;

    do{

        printf("Ingrese la opcion: \n");
        scanf("%d", &seleccion);

    }while(seleccion < 1 || seleccion > 4);

    return seleccion;

}

RespustasPtr cargarRespuestaNula(){

    RespustasPtr r = (RespustasPtr)malloc(sizeof(struct Respuestas));

    strcpy(r->r1,"VACIO");
    strcpy(r->r2,"VACIO");
    strcpy(r->r3,"VACIO");
    strcpy(r->r4,"VACIO");
    r->nroRespuestas = -1;

    return r;

};

void cargarRespuestasNulas(RespustasPtr respuestas[],int t){

    for(int i = 0; i < t; i++){
        respuestas[i] = cargarRespuestaNula();
    }

};

void mostrarRespuesta(RespustasPtr respuesta){
    if(respuesta->nroRespuestas != -1){
        printf("####################################################################################\n");
        printf("    OPCION 1:%s",respuesta->r1);
        printf("    OPCION 2:%s",respuesta->r2);
        printf("    OPCION 3: %s",respuesta->r3);
        printf("    OPCION 4: %s",respuesta->r4);
        printf("\n####################################################################################\n");

    }

};

void mostrarRespuestas(RespustasPtr respuestas[],int t){

    for(int i = 0; i < t; i++){
        mostrarRespuesta(respuestas[i]);

    }

};

void liberarRespuestas(RespustasPtr respuestas[],int t){

    for(int i = 0; i < t; i++){
        free(respuestas[i]);
    }

};

///###########################GETTERS###########################

int getNroRespuesta(RespustasPtr respuesta){
    return respuesta->nroRespuestas;
};

char* getR1(RespustasPtr respuesta){
    return respuesta->r1;
};

char* getR2(RespustasPtr respuesta){
    return respuesta->r2;
};

char* getR3(RespustasPtr respuesta){
    return respuesta->r3;
};

char* getR4(RespustasPtr respuesta){
    return respuesta->r4;
};


///###########################SETTERS###########################

void setNroRespuesta(RespustasPtr respuesta,int nuevoNro){
    respuesta->nroRespuestas = nuevoNro;
};

void setR1(RespustasPtr respuesta, char nuevoR1[15]){
    strcpy(respuesta->r1,nuevoR1);
};

void setR2(RespustasPtr respuesta, char nuevoR2[15]){
    strcpy(respuesta->r2,nuevoR2);
};

void setR3(RespustasPtr respuesta, char nuevoR3[15]){
    strcpy(respuesta->r3,nuevoR3);
};

void setR4(RespustasPtr respuesta, char nuevoR4[15]){
    strcpy(respuesta->r4,nuevoR4);
};
