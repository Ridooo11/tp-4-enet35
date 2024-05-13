#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Persona {
    char nombre[50];
    char apellido[50];
    int dni;
};

// Prototipado funciones
	void menu();
	void pausa();
	void guardarDatos(struct Persona persona);
	void buscarPorDNI(int dni);
	void limpiar();
	

	
int main() {
	menu();
    return 0;
}

void menu() {
    char opcion;
    struct Persona persona;
    
    
    int dniBuscar;
                
    do {
        limpiar();
        printf(" Menu:\n");
        printf(" 1 - Ingresar datos\n");
        printf(" 2 - Buscar por DNI\n");
        printf(" 3 - Salir\n");
        printf(" Ingrese la opcion: ");
        opcion = getche();
        limpiar();

        switch (opcion) {
            case '1':
                printf(" Ingrese el nombre: ");
                scanf("%s", persona.nombre);
                printf(" Ingrese el apellido: ");
                scanf("%s", persona.apellido);
                printf(" Ingrese el DNI: ");
                scanf("%d", &persona.dni);
		              
                guardarDatos(persona);
                pausa();
        		
                break;
            case '2':
                printf(" Ingrese el DNI a buscar: ");
                
                scanf("%d", &dniBuscar);
                
                limpiar();
                
                buscarPorDNI(dniBuscar);
                pausa();
                break;
            case '3':
                printf(" Saliendo del programa. . .\n");
                pausa();
                exit(0);
            default:
                printf(" Ingrese una opcion valida.\n");
                pausa();
                break;
        }
    } while (opcion != '3');
}
	
void pausa() {
    printf("\n\n\t");
    system("PAUSE");
}

void limpiar() {
    system("CLS");
}

void guardarDatos(struct Persona persona) {
    FILE *archivo;
    archivo = fopen("datos_tp1.txt", "a");
    if (archivo == NULL) {
        printf(" Error al abrir el archivo.\n");
        return;
    }
    fprintf(archivo, "%s %s %d\n", persona.nombre, persona.apellido, persona.dni);
    fclose(archivo);
    printf(" Datos guardados correctamente.\n");
}

void buscarPorDNI(int dni) {
    FILE *archivo;
    archivo = fopen("datos_tp1.txt", "r");
    if (archivo == NULL) {
        printf(" Error al abrir el archivo.\n");
        return;
    }
    struct Persona persona;
    int encontrado = 0;
    while (fscanf(archivo, "%s %s %d", persona.nombre, persona.apellido, &persona.dni) != EOF) {
        if (persona.dni == dni) {
            printf(" Nombre: %s\n Apellido: %s\n", persona.nombre, persona.apellido);
            encontrado = 1;
            break;
        }
    }
    fclose(archivo);
    if (!encontrado) {
        printf(" No se encontraron datos para el DNI ingresado.\n");
    }
}
	


