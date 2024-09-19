#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "respuestas.h"
#include "jugador.h"
#include "preguntas.h"
#include "puntos.h"

void mostrarReglasIntroduccion();
void menuInicial();
void realizarTarea();

int main() {

    mostrarReglasIntroduccion();

    system("pause");
    system("cls");
    int tam = cantJugadores();
    JugadorPtr jugador[tam];
    int ganador;

    int opcion;
    do {
        menuInicial();
        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            cargarJugadoresPorTeclado(jugador, tam);
            leerDatosJugador(jugador,tam);
            mostrarPreguntasYResponderGlobal(jugador,tam);
            ganador = determinarGanador(jugador, tam);
            if (ganador == -1) {
                desempate(jugador, tam);
            }
            printf("\n\nJUEGO FINALIZADO\n\n");
            system("pause");
            system("cls");
            break;
        case 2:
            consultarPuntajeMaximo();
            break;
        case 6:
            printf("Gracias por jugar!!\n");
            break;
        }
    } while (opcion != 6);

    guardarDatosJugador(jugador,tam);
    liberarJugadores(jugador, tam);

    return 0;
}


void mostrarReglasIntroduccion() {
    printf("###################################################\n");
    printf("###            ¡Bienvenido a QUIZ!              ###\n");
    printf("###################################################\n\n");

}

void menuInicial() {
    printf("\n  ################################\n");
    printf("  ##1)          COMENZAR        ##\n");
    printf("  ##2)          PUNTOS          ##\n");
    printf("  ##3)          SALIR           ##\n");
    printf("  ################################\n");
}


