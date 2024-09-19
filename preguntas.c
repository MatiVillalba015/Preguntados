#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "preguntas.h"
#include "jugador.h"
#include "puntos.h"

struct Preguntas{

    int nroPregunta;
    char preguntas[100];
    int dificultad;
    int correcta;
    RespustasPtr resp[TAM];

};

PreguntasPtr cargarPreguntaNula(){

    PreguntasPtr p = (PreguntasPtr)malloc(sizeof(struct Preguntas));

    strcpy(p->preguntas,"VACIO");
    p->nroPregunta = -1;
    p->dificultad = -1;
    p->correcta = -1;

    cargarRespuestasNulas(p->resp,TAM);

    return p;

}
void cargarPreguntasNulas(PreguntasPtr preguntas[],int t){

    for(int i = 0; i < t; i++){
        preguntas[i] = cargarPreguntaNula();
    }

};

void cargarPreguntaTxt(PreguntasPtr preguntas[]){

    FILE * archivo = fopen("preguntas.txt","r");

    if(archivo == NULL){
        printf("Error al leer");
        exit(1);
    }

    int pos = 0;

    while(!feof(archivo)){
        preguntas[pos] = cargarPreguntaNula();
        fscanf(archivo,"%d,%d,%d",&preguntas[pos]->nroPregunta,&preguntas[pos]->dificultad,&preguntas[pos]->correcta);
        fgets(preguntas[pos]->preguntas,100,archivo);

        pos++;

    }

    fclose(archivo);

    for(int i = 0; i < TAM; i++){

        cargarRespuestasTxt(preguntas[i]);

    }

}

void cargarRespuestasTxt(PreguntasPtr respuesta) {
    FILE * archivo = fopen("respuestas.txt", "r");

    if (archivo == NULL) {
        printf("Error al leer las respuestas");
        exit(1);
    }

    int pos = 0;
    char linea[100];

    while (fgets(linea, sizeof(linea), archivo)) {
        int nroResp;
        char resp1[15];
        char resp2[15];
        char resp3[15];
        char resp4[15];

        if (sscanf(linea, "%d,%[^,],%[^,],%[^,],%[^,]", &nroResp, resp1, resp2, resp3, resp4) == 5) {
            if (nroResp == getNroPregunta(respuesta)) {
                setNroRespuesta(respuesta->resp[pos],nroResp);
                setR1(respuesta->resp[pos],resp1);
                setR2(respuesta->resp[pos],resp2);
                setR3(respuesta->resp[pos],resp3);
                setR4(respuesta->resp[pos],resp4);
                pos++;
            }
        }
    }

    fclose(archivo);
}

void mostrarPregunta(PreguntasPtr pregunta) {

    if (pregunta->nroPregunta != -1) {
        //printf("    PREGUNTA NUMERO-> %d\n", pregunta->nroPregunta);
        printf("    NIVEL DE DIFICULTAD-> %d\n", pregunta->dificultad);
        printf("    PREGUNTA: %s\n", pregunta->preguntas);
        mostrarRespuestas(pregunta->resp,TAM);
    }
}

void mostrarPreguntas(PreguntasPtr pregunta[],int t){

    for(int i = 0; i < t; i++){
        mostrarPregunta(pregunta[i]);
    }


};

int cantidadPreguntas(char * c){

    FILE * archivo = fopen(c,"r");

    char buffer[200];
    int pos = 0;
    while(!feof(archivo)){

        fgets(buffer,200,archivo);
        pos++;
    }

    fclose(archivo);

    return pos;

}

void shuffleArray(int array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void liberarPregunta(PreguntasPtr pregunta){

    liberarRespuestas(pregunta->resp,TAM);
    free(pregunta);
}

void liberarPreguntas(PreguntasPtr preguntas[],int t){

    for(int i = 0; i < t; i++){
        free(preguntas[i]);
    }

};


int getNroPregunta(PreguntasPtr pregunta){
    return pregunta->nroPregunta;
};

int getDificultad(PreguntasPtr pregunta){
    return pregunta->dificultad;
};

char* getPregunta(PreguntasPtr pregunta){
    return pregunta->preguntas;
};

int getCorrecta(PreguntasPtr pregunta){
    return pregunta->correcta;
};

///###########################SETTERS###########################

void setNroPregunta(PreguntasPtr pregunta, int nuevoNroPregunta){
    pregunta->nroPregunta = nuevoNroPregunta;
};

void setDificultad(PreguntasPtr pregunta, int nuevoDificultad){
    pregunta->dificultad = nuevoDificultad;
};

void setPregunta(PreguntasPtr pregunta, char nuevaPregunta[100]){
    strcpy(pregunta->preguntas,nuevaPregunta);
};

void setCorrecta(PreguntasPtr pregunta,int nuevaCorrecta){
    pregunta->correcta = nuevaCorrecta;
};

