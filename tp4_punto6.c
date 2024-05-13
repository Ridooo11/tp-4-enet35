#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_JUGADORES = 15;

struct Jugador {
    char nombre[50];
    int puntaje;
};

void menu();
void pausa();
void limpiar();
void guardarJugador(struct Jugador jugador);
void mejoresJugadores();
void buscarJugador(char nombreBuscado[]);

void pausa() {
    printf("\n\n\t");
    system("PAUSE");
}

void limpiar() {
    system("CLS");
}

int main() {
    menu();
    return 0;
}

void menu() {
	
	struct Jugador nuevoJugador;
	char opcion;
	char nombreBuscado[50];
    
    do {
        limpiar();
        printf(" Menu:\n");
        printf(" 1 - Registrar un nuevo jugador\n");
        printf(" 2 - Mostrar el top 10 de jugadores\n");
        printf(" 3 - Buscar un jugador\n");
        printf(" 4 - Salir\n");
        printf(" Ingrese la opcion deseada: ");
        opcion = getche();
        limpiar();

        switch (opcion) {
            case '1': {
                do {
                	printf(" Ingrese el nombre del jugador: ");
                	scanf("%s", nuevoJugador.nombre);
                	
        			printf(" Ingrese el puntaje del jugador: ");
        			scanf("%d", &nuevoJugador.puntaje);
        				if (nuevoJugador.puntaje < 0) {
        					limpiar();
            				printf(" El puntaje no puede ser menor a 0. Por favor, ingrese un puntaje valido.\n");
            				pausa();
            				limpiar();
        				}
    			} while (nuevoJugador.puntaje < 0);
                
                guardarJugador(nuevoJugador);
                pausa();
                break;
            }
            case '2':
                mejoresJugadores();
                pausa();
                break;
            case '3': {
                printf(" Ingrese el nombre a buscar: ");
                scanf("%s", nombreBuscado);
                buscarJugador(nombreBuscado);
                pausa();
                break;
            }
            case '4':
                printf(" Saliendo del programa. . .\n");
                pausa();
                exit(0);
            default:
                printf(" Ingrese una opcion valida.\n");
                pausa();
                break;
        }
    } while (opcion != '4');
}

void guardarJugador(struct Jugador jugador) {
    FILE *archivo = fopen("jugadores.txt", "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s %d\n", jugador.nombre, jugador.puntaje);
        printf(" Jugador ingresado correctamente.");
        fclose(archivo);
    } else {
        printf(" Error al abrir el archivo.\n");
    }
}

void mejoresJugadores() {
	int i, j, k;
    struct Jugador jugadores[MAX_JUGADORES];
    FILE *archivo = fopen("jugadores.txt", "r");
    if (archivo != NULL) {
        while (fscanf(archivo, "%s %d", jugadores[i].nombre, &jugadores[i].puntaje) != EOF) {
            i++;
        }
        fclose(archivo);

        for (j = 0; j < i - 1; j++) {
            for (k = 0; k < i - j - 1; k++) {
                if (jugadores[k].puntaje < jugadores[k + 1].puntaje) {
                    struct Jugador temp = jugadores[k];
                    jugadores[k] = jugadores[k + 1];
                    jugadores[k + 1] = temp;
                }
            }
        }

        printf("Top 10 Jugadores:\n");
        for (j = 0; j < i && j < 10; j++) {
            printf(" %d. %s - Puntaje: %d\n", j + 1, jugadores[j].nombre, jugadores[j].puntaje);
        }
    } else {
        printf(" No hay jugadores registrados.\n");
    }
}

void buscarJugador(char nombreBuscado[50]) {
    struct Jugador jugador;
    FILE *archivo = fopen("jugadores.txt", "r");
    if (archivo != NULL) {
        int encontrado = 0;
        while (fscanf(archivo, "%s %d", jugador.nombre, &jugador.puntaje) != EOF) {
            if (strcasecmp(jugador.nombre, nombreBuscado) == 0) {
                printf(" Jugador encontrado - Nombre: %s, Puntaje: %d\n", jugador.nombre, jugador.puntaje);
                encontrado = 1;
            }
        }
        if (!encontrado) {
            printf(" Jugador no encontrado.\n");
        }
        fclose(archivo);
    } else {
        printf(" No hay jugadores registrados.\n");
    }
}
