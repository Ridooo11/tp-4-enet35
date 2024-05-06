#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Persona {
    char nombre[50];
    char apellido[50];
    int dni;
};


void menu();
void guardarDatos(struct Persona persona); 
void buscarPorDNI(int dni);
void buscarPorNombreApellido(char nombre[], char apellido[]);
int validarDuplicados(struct Persona persona);

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
    char opcion;
    struct Persona persona;
    
    char nombreBuscar[50];
    char apellidoBuscar[50];
                
    do {
        limpiar();
        printf(" Menu:\n");
        printf(" 1 - Ingresar datos y guardar en archivo\n");
        printf(" 2 - Buscar por DNI\n");
        printf(" 3 - Buscar por Nombre y Apellido\n");
        printf(" 4 - Salir\n");
        printf(" Ingrese la opcion deseada: ");
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
		              if (validarDuplicados(persona)) {
                    guardarDatos(persona);
                    pausa();
        			 } else {
                   printf("Este registro ya existe en el archivo.\n");
                   pausa();
                }
                break;
            case '2':
                printf(" Ingrese el DNI a buscar: ");
                int dniBuscar;
                scanf("%d", &dniBuscar);
                buscarPorDNI(dniBuscar);
                pausa();
                break;
            case '3':
            	
                printf(" Ingrese el nombre a buscar: ");
                scanf("%s", nombreBuscar);
                
                printf(" Ingrese el apellido a buscar: ");
                scanf("%s", apellidoBuscar);
                
                buscarPorNombreApellido(nombreBuscar, apellidoBuscar);
                pausa();
                break;
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

void guardarDatos(struct Persona persona) {
    FILE *archivo;
    archivo = fopen("datos_tp3.txt", "a");
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
    archivo = fopen("datos_tp3.txt", "r");
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

void buscarPorNombreApellido(char nombre[], char apellido[]) {
    FILE *archivo;
    archivo = fopen("datos_tp3.txt", "r");
    if (archivo == NULL) {
        printf(" Error al abrir el archivo.\n");
        return;
    }
    struct Persona persona;
    int encontrado = 0;
    while (fscanf(archivo, "%s %s %d", persona.nombre, persona.apellido, &persona.dni) != EOF) {
        if (strcmp(persona.nombre, nombre) == 0 || strcmp(persona.apellido, apellido) == 0) {
            printf(" Nombre: %s\n Apellido: %s\n DNI: %d\n", persona.nombre, persona.apellido, persona.dni);
            encontrado = 1;
            break;
        }
    }
    fclose(archivo);
    if (!encontrado) {
        printf(" No se encontraron datos para el nombre y apellido ingresados.\n");
    }
}

int validarDuplicados(struct Persona persona) {
    FILE *archivo;
    archivo = fopen("datos_tp3.txt", "r");
    if (archivo == NULL) {
        printf(" Error al abrir el archivo.\n");
        return 1; 
    }
    struct Persona tmp;
    while (fscanf(archivo, "%s %s", tmp.nombre, tmp.apellido) != EOF) {
        if (strcmp(tmp.nombre, persona.nombre) == 0 && strcmp(tmp.apellido, persona.apellido) == 0) {
            fclose(archivo);
            return 0; 
        }
    }
    fclose(archivo);
    return 1; 
}
