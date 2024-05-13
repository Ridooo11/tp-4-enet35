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
void ordenarPorNombreApellido();
void ordenarPorDNI();

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
        printf(" 4 - Ordenar por Nombre y Apellido\n");
		printf(" 5 - Ordenar por DNI\n");
        printf(" 6 - Salir\n");
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
            	
    			ordenarPorNombreApellido();
    			pausa();
    			break;
    			
			case '5':
				
    			ordenarPorDNI();
    			pausa();
    			break;
    			
            case '6':
                printf(" Saliendo del programa. . .\n");
                pausa();
                exit(0);
            default:
                printf(" Ingrese una opcion valida.\n");
                pausa();
                break;
        }
    } while (opcion != '6');
}



void guardarDatos(struct Persona persona) {
    FILE *archivo;
    archivo = fopen("datos_tp5.txt", "a");
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
    archivo = fopen("datos_tp5.txt", "r");
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
    archivo = fopen("datos_tp5.txt", "r");
    if (archivo == NULL) {
        printf(" Error al abrir el archivo.\n");
        return;
    }
    struct Persona persona;
    int encontrado = 0;
    while (fscanf(archivo, "%s %s %d", persona.nombre, persona.apellido, &persona.dni) != EOF) {
        if (strcasecmp(persona.nombre, nombre) == 0 || strcasecmp(persona.apellido, apellido) == 0) {
            printf(" Nombre: %s\n Apellido: %s\n DNI: %d\n", persona.nombre, persona.apellido, persona.dni);
            encontrado = 1;
            printf("\n");
        }
    }
    fclose(archivo);
    if (!encontrado) {
        printf(" No se encontraron datos para el nombre y apellido ingresados.\n");
    }
}

int validarDuplicados(struct Persona persona) {
    FILE *archivo;
    archivo = fopen("datos_tp5.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    struct Persona tmp;
    while (fscanf(archivo, "%s %s %d", tmp.nombre, tmp.apellido, &tmp.dni) != EOF) {
        if (strcasecmp(tmp.nombre, persona.nombre) == 0 && strcasecmp(tmp.apellido, persona.apellido) == 0 || tmp.dni == persona.dni) {
            fclose(archivo);
            return 0;
        }
    }
    fclose(archivo);
    return 1;
}

void ordenarPorNombreApellido() {
	int i, j;
    FILE *archivo;
    archivo = fopen("datos_tp5.txt", "r");
    if (archivo == NULL) {
        printf(" Error al abrir el archivo.\n");
        return;
    }
	
	// Se leen los registros y se guardan en un array de forma dinamica con realloc.
    struct Persona *personas = NULL;
    int numPersonas = 0;
    struct Persona temp;
    while (fscanf(archivo, "%s %s %d", temp.nombre, temp.apellido, &temp.dni) != EOF) {
        personas = (struct Persona *)realloc(personas, (numPersonas + 1) * sizeof(struct Persona));
        strcpy(personas[numPersonas].nombre, temp.nombre);
        strcpy(personas[numPersonas].apellido, temp.apellido);
        personas[numPersonas].dni = temp.dni;
        numPersonas++;
    }
    fclose(archivo);


    for (i = 0; i < numPersonas - 1; i++) {
        for (j = 0; j < numPersonas - i - 1; j++) {
            if (stricmp(personas[j].nombre, personas[j + 1].nombre) > 0 ||
                (stricmp(personas[j].nombre, personas[j + 1].nombre) == 0 &&
                 stricmp(personas[j].apellido, personas[j + 1].apellido) > 0)) {
                 	
                strcpy(temp.nombre, personas[j].nombre);
                strcpy(temp.apellido, personas[j].apellido);
                temp.dni = personas[j].dni;

                strcpy(personas[j].nombre, personas[j + 1].nombre);
                strcpy(personas[j].apellido, personas[j + 1].apellido);
                personas[j].dni = personas[j + 1].dni;

                strcpy(personas[j + 1].nombre, temp.nombre);
                strcpy(personas[j + 1].apellido, temp.apellido);
                personas[j + 1].dni = temp.dni;
            }
        }
    }
    
    FILE *nuevoArchivo;
    nuevoArchivo = fopen("datos_ordenados_por_nombre_apellido.txt", "w");
    if (nuevoArchivo == NULL) {
        printf(" Error al crear el archivo.\n");
        free(personas);
        return;
    }
    for (i = 0; i < numPersonas; i++) {
        fprintf(nuevoArchivo, "%s %s %d\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
    fclose(nuevoArchivo);
    
    printf(" Datos ordenados por nombre y apellido guardados en 'datos_ordenados_por_nombre_apellido.txt'.\n");
    
    pausa();
    limpiar();
    
    printf("Datos ordenados por nombre y apellido:\n");
    for (i = 0; i < numPersonas; i++) {
        printf(" Nombre: %s\n Apellido: %s\n DNI: %d\n\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }

    // Se libera la memoria dinamica.
    free(personas);
}

void ordenarPorDNI() {
	int i, j;
    FILE *archivo;
    archivo = fopen("datos_tp5.txt", "r");
    if (archivo == NULL) {
        printf(" Error al abrir el archivo.\n");
        return;
    }

    // Se leen los registros y se guardan en un array de forma dinamica con realloc.
    struct Persona *personas = NULL;
    int numPersonas = 0;
    struct Persona temp;
    while (fscanf(archivo, "%s %s %d", temp.nombre, temp.apellido, &temp.dni) != EOF) {
        personas = (struct Persona *)realloc(personas, (numPersonas + 1) * sizeof(struct Persona));
        strcpy(personas[numPersonas].nombre, temp.nombre);
        strcpy(personas[numPersonas].apellido, temp.apellido);
        personas[numPersonas].dni = temp.dni;
        numPersonas++;
    }
    fclose(archivo);

    for (i = 0; i < numPersonas - 1; i++) {
        for (j = 0; j < numPersonas - i - 1; j++) {
            if (personas[j].dni > personas[j + 1].dni) {
                strcpy(temp.nombre, personas[j].nombre);
                strcpy(temp.apellido, personas[j].apellido);
                temp.dni = personas[j].dni;

                strcpy(personas[j].nombre, personas[j + 1].nombre);
                strcpy(personas[j].apellido, personas[j + 1].apellido);
                personas[j].dni = personas[j + 1].dni;

                strcpy(personas[j + 1].nombre, temp.nombre);
                strcpy(personas[j + 1].apellido, temp.apellido);
                personas[j + 1].dni = temp.dni;
            }
        }
    }
    
    FILE *nuevoArchivo;
    nuevoArchivo = fopen("datos_ordenados_por_dni.txt", "w");
    if (nuevoArchivo == NULL) {
        printf(" Error al crear/abrir el archivo.\n");
        free(personas);
        return;
    }

    for (i = 0; i < numPersonas; i++) {
        fprintf(nuevoArchivo, "%s %s %d\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }
    fclose(nuevoArchivo);
    
    printf(" Datos ordenados por DNI guardados en 'datos_ordenados_por_dni.txt'.\n");
    
    pausa();
    limpiar();

    printf("Datos ordenados por DNI:\n");
    for (i = 0; i < numPersonas; i++) {
        printf(" Nombre: %s\n Apellido: %s\n DNI: %d\n\n", personas[i].nombre, personas[i].apellido, personas[i].dni);
    }

    // Se libera la memoria dinamica.
    free(personas);
}
