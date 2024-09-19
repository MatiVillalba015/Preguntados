#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "jugador.h"
#include "puntos.h"
#include "preguntas.h"

struct Jugador{

    char alias[20];
    int dni;

    PreguntasPtr preguntas[TAM];
    PuntosPtr puntos;


};

JugadorPtr cargarJugadorNulo(){

    JugadorPtr j = (JugadorPtr)malloc(sizeof(struct Jugador));

    strcpy(j->alias,"VACIO");
    j->dni = -1;

    j->preguntas[TAM] = cargarPreguntaNula();
    j->puntos = crearPuntos();

    return j;

};
JugadorPtr cargarJugadorTeclado() {
    JugadorPtr j = (JugadorPtr)malloc(sizeof(struct Jugador));

    printf("Ingrese un NOMBRE/ALIAS: \n");
    fflush(stdin);
    gets(j->alias);

    bool dniValido = false;
    do {
        printf("Ingrese su DNI (8 digitos): \n");
        char dniString[20];
        scanf("%s", dniString);

        int dni;
        if (sscanf(dniString, "%d", &dni) == 1 && strlen(dniString) == 8) {
            j->dni = dni;
            dniValido = true;
        } else {
            printf("DNI invalido, intente nuevamente con otro DNI).\n");
        }
    } while (!dniValido);

    cargarPreguntasNulas(j->preguntas, TAM);
    j->puntos = crearPuntos();

    return j;
}

int cantJugadores(){
    int n;

    do{
        printf("######################################\n");
        printf("Cuantos jugadores participaran??\n");
        printf("######################################\n");
        printf("Ingrese a continuacion un numero:");
        scanf("%d",&n);
    }while(n < 1 || n > 4);

    return n;

}

void cargarJugadoresPorTeclado(JugadorPtr jugador[],int t){

    for(int i = 0; i < t; i++){
        jugador[i] = cargarJugadorTeclado();
    }

};

void mostrarJugador(JugadorPtr jugador){
    printf("\n*******************************\n");
    printf("    ALIAS:           %s\n", jugador->alias);
    printf("    DNI:             %d\n", jugador->dni);
    printf("*******************************\n");
    printf("\n");
    cargarPreguntaTxt(jugador->preguntas);
    mostrarPreguntasYResponderAleatoria(jugador);
};

void mostrarJugadores(JugadorPtr jugadores[],int t){

    for(int i = 0; i < t; i++){
        mostrarJugador(jugadores[i]);
    }

};

void mostrarPreguntasYResponderAleatoria(JugadorPtr jugador) {
    int tam = cantidadPreguntas("preguntas.txt");

    int preguntasAleatorias[tam];
    for (int i = 0; i < tam; i++) {
        preguntasAleatorias[i] = i;
    }

    shuffleArray(preguntasAleatorias, tam);

    for (int i = 0; i < tam; i++) {
        int pregAleatoria = preguntasAleatorias[i];
        if (pregAleatoria < 0 || pregAleatoria >= tam) {
            printf("Índice de pregunta aleatoria fuera de los límites permitidos.");
            return;
        }
        mostrarPregunta(jugador->preguntas[pregAleatoria]);

        int seleccion = seleccionarRespuesta();

        printf("Numero seleccionado: %d\n", seleccion);

        int dificultadPregunta = getDificultad(jugador->preguntas[pregAleatoria]);
        int respCorrecta = getCorrecta(jugador->preguntas[pregAleatoria]);
        int puntosGanados = 0;

        if (seleccion == respCorrecta) {
            switch (dificultadPregunta) {
                case 1:
                    puntosGanados = 1;
                    break;

                case 3:
                    puntosGanados = 3;
                    break;

                case 5:
                    puntosGanados = 5;
                    break;
            }

            printf("\nLa respuesta es correcta\n\n");
        } else {
            printf("\nLa respuesta es incorrecta\n\n");
        }

        jugador->puntos->actual += puntosGanados;

        actualizarPuntajeMaximo(jugador->puntos);

        printf("Puntos: %d\n", jugador->puntos->actual);
        system("pause");
        system("cls");
    }
}


void mostrarPreguntasYResponderGlobal(JugadorPtr jugador[],int t){

    for(int i = 0; i < t; i++){
        system("cls");
        printf("-------------------------- JUGADOR %d --------------------------\n",i+1);;
        mostrarJugador(jugador[i]);
        guardarPuntaje(jugador[i]->puntos, jugador[i]->alias);
        system("cls");
        printf("\n-------------------------- SIGUIENTE JUGADOR --------------------------\n");
        system("pause");
    }

}

void generarPreguntaMatematica(char *enunciado, int *respuesta) {
    int num1 = rand() % 10 + 1;
    int num2 = rand() % 10 + 1;

    sprintf(enunciado, "¿Cuanto es %d * %d?", num1, num2);

    *respuesta = num1 * num2;
}

void desempate(JugadorPtr jugadores[], int t) {
    char enunciado[50];
    int respuestaCorrecta;
    generarPreguntaMatematica(enunciado, &respuestaCorrecta);

    printf("\nEmpate en puntos. Se realizará un desempate con la siguiente pregunta:\n");
    printf("%s\n", enunciado);

    int respuestaJugadores[t];

    for (int i = 0; i < t; i++) {
        printf("Jugador %d, ingresa tu respuesta: ", i + 1);
        scanf("%d", &respuestaJugadores[i]);
    }
    int respuestaMasCercana = respuestaCorrecta;
    int menorDiferencia = abs(respuestaJugadores[0] - respuestaCorrecta);
    int jugadoresConMenorDiferencia[t];
    int numJugadoresConMenorDiferencia = 0;

    for (int i = 0; i < t; i++) {
        int diferencia = abs(respuestaJugadores[i] - respuestaCorrecta);

        if (diferencia < menorDiferencia) {
            menorDiferencia = diferencia;
            respuestaMasCercana = respuestaJugadores[i];
            numJugadoresConMenorDiferencia = 1;
            jugadoresConMenorDiferencia[0] = i;
        } else if (diferencia == menorDiferencia) {
            jugadoresConMenorDiferencia[numJugadoresConMenorDiferencia++] = i;
        }
    }

    if (numJugadoresConMenorDiferencia == 1) {
        int jugadorMasCercano = jugadoresConMenorDiferencia[0];
        jugadores[jugadorMasCercano]->puntos->maximo += 1;
        printf("El jugador %d gana el desempate y obtiene un punto extra.\n", jugadorMasCercano + 1);

        guardarPuntajeMaximoPuntoExtra(jugadores[jugadorMasCercano]->puntos->maximo, jugadores[jugadorMasCercano]->alias);
    } else {
        printf("Empate en el desempate. Nadie obtiene un punto extra.\n");
    }
}


int determinarGanador(JugadorPtr jugadores[], int t) {
    int maximoPuntaje = 0;
    int ganador = -1;

    for (int i = 0; i < t; i++) {
        if (jugadores[i]->puntos->maximo > maximoPuntaje) {
            maximoPuntaje = jugadores[i]->puntos->maximo;
            ganador = i;
        } else if (jugadores[i]->puntos->maximo == maximoPuntaje) {
            ganador = -1;
        }
    }

    printf("Puntajes Finales:\n");
    for (int i = 0; i < t; i++) {
        printf("Jugador %d: Puntos Actuales: %d, Puntaje Maximo: %d\n", i + 1, jugadores[i]->puntos->actual, jugadores[i]->puntos->maximo);
    }

    if (ganador != -1) {
        printf("El ganador es el Jugador %d con %d puntos.\n", ganador + 1, maximoPuntaje);
    } else {
        printf("Empate en el puntaje máximo.\n");
    }

    return ganador;
}


void guardarDatosJugador(JugadorPtr jugador[],int t){

    FILE * archivo = fopen("datos_jugador.txt","a");

    for(int i = 0; i < t; i++){
        fprintf(archivo,"%s,%d\n",jugador[i]->alias,jugador[i]->dni);
    }

    fclose(archivo);

}

void leerDatosJugador(JugadorPtr jugador[], int t) {
    FILE *archivo = fopen("datos_jugador.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo datos_jugador.txt\n");
        return;
    }

    char buffer[200];

    while (fgets(buffer, sizeof(buffer), archivo)) {
        char alias[100];
        int dni;
        if (sscanf(buffer, "%[^,],%d", alias, &dni) == 2) {
            int jugadorExistente = -1;
            for (int i = 0; i < t; i++) {
                if (jugador[i]->dni == dni) {
                    jugadorExistente = i;
                    break;
                }
            }

            if (jugadorExistente != -1) {
                printf("El jugador con DNI %d ya ha jugado.\n", dni);
                while (1) {
                    int dniNuevo;
                    printf("Ingrese un nuevo DNI: ");
                    scanf("%d", &dniNuevo);

                    if (dniNuevo != dni) {
                        setDni(jugador[jugadorExistente], dniNuevo);
                        printf("DNI actualizado a %d\n", dniNuevo);
                        break;
                    } else {
                        printf("El DNI ingresado es igual al anterior. Ingrese un DNI diferente.\n");
                    }
                }
            } else {
                printf("Jugador %s con DNI %d cargado.\n", alias, dni);
            }
        } else {
            printf("Error al leer datos del archivo.\n");
        }
    }

    fclose(archivo);
}

bool verificarDNIExistente(const char* dni_str) {
    FILE* archivo = fopen("datos_jugador.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return false;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        strtok(buffer, ",");
        char* dni_existente = strtok(NULL, ",");
        if (strcmp(dni_existente, dni_str) == 0) {
            fclose(archivo);
            return true;
        }
    }

    fclose(archivo);
    return false;
}


void liberarJugador(JugadorPtr jugador){

    free(jugador);
    liberarPreguntas(jugador->preguntas,TAM);
    liberarPuntos(jugador->puntos);
};

void liberarJugadores(JugadorPtr jugadores[],int t){

    for(int i = 0; i < t; i++){
        liberarJugador(jugadores[i]);
    }

};

///###########################GETTERS###########################

int getDni(JugadorPtr jugador){

    return jugador->dni;

}

char* getAlias(JugadorPtr jugador){

    return jugador->alias;

}

///###########################SETTERS###########################

void setDni(JugadorPtr jugador, int nuevoDni){

    jugador->dni = nuevoDni;

}

void setAlias(JugadorPtr jugador, char nuevoAlias[20]){

    strcpy(jugador->alias,nuevoAlias);

}
