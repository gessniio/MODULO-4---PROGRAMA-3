#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NOMBRE_ARCHIVO "bitacora.txt"
#define BUFFER_SIZE 256

void obtenerFechaHora(char *buffer, int tamano)
{
    time_t ahora = time(NULL);
    struct tm *t = localtime(&ahora);
    strftime(buffer, tamano, "%d/%m/%Y %H:%M:%S", t);
}

int validarEnteroPositivo(const char *mensaje)
{
    int valor;
    int valido = 0;

    while (!valido)
    {
        printf("%s", mensaje);
        if (scanf("%d", &valor) != 1)
        {
            while (getchar() != '\n')
                ;
            printf("  [ERROR] Por favor ingrese un número entero válido.\n");
        }
        else if (valor <= 0)
        {
            printf("  [ERROR] El valor debe ser un número positivo mayor a cero.\n");
        }
        else
        {
            valido = 1;
        }
    }
    return valor;
}

void registrarBitacora()
{
    FILE *archivo;
    char fechaHora[BUFFER_SIZE];
    int sesiones, turnos;

    printf("\n===================================================\n");
    printf("   REGISTRO DE USO - MARVIN - MAYRA\n");
    printf("===================================================\n");

    sesiones = validarEnteroPositivo("  Número de sesiones activas del día : ");
    turnos = validarEnteroPositivo("  Número de turnos atendidos         : ");

    obtenerFechaHora(fechaHora, BUFFER_SIZE);

    archivo = fopen(NOMBRE_ARCHIVO, "a");
    if (archivo == NULL)
    {
        printf("\n  [ERROR] No se pudo abrir el archivo '%s'.\n", NOMBRE_ARCHIVO);
        return;
    }

    fprintf(archivo, "---------------------------------------------------\n");
    fprintf(archivo, "Fecha y hora     : %s\n", fechaHora);
    fprintf(archivo, "Sesiones activas : %d\n", sesiones);
    fprintf(archivo, "Turnos atendidos : %d\n", turnos);
    fprintf(archivo, "---------------------------------------------------\n\n");

    fclose(archivo);

    printf("\n  [OK] Registro guardado correctamente en '%s'.\n", NOMBRE_ARCHIVO);
}

void consultarBitacora()
{
    FILE *archivo;
    char linea[BUFFER_SIZE];
    int registros = 0;

    printf("\n===================================================\n");
    printf("     CONSULTA DE BITÁCORA - MARVIN - MAYRA           \n");
    printf("===================================================\n");

    archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL)
    {
        printf("\n  [INFO] No existe ningún registro aún en '%s'.\n", NOMBRE_ARCHIVO);
        printf("         Realice primero un registro de datos.\n");
        return;
    }

    printf("\n  Contenido del archivo '%s':\n\n", NOMBRE_ARCHIVO);

    while (fgets(linea, BUFFER_SIZE, archivo) != NULL)
    {
        printf("  %s", linea);
        /* Contar secciones de registro (cada separador = 1 registro) */
        if (strstr(linea, "Sesiones activas") != NULL)
        {
            registros++;
        }
    }

    fclose(archivo);

    printf("\n  Total de registros encontrados: %d\n", registros);
    printf("===================================================\n");
}

int mostrarMenu()
{
    int opcion;

    printf("\n===================================================\n");
    printf("       SISTEMA PAD-Bienestar | MARVIN - MAYRA\n");
    printf("===================================================\n");
    printf("  1. Registrar uso del día\n");
    printf("  2. Consultar bitácora guardada\n");
    printf("  3. Salir del programa\n");
    printf("---------------------------------------------------\n");
    printf("  Seleccione una opción [1-3]: ");

    if (scanf("%d", &opcion) != 1)
    {
        while (getchar() != '\n')
            ;
        return 0; 
    }

    return opcion;
}

int main()
{
    int opcion;

    printf("\n  Bienvenido al sistema de Bitácora - PAD-Bienestar MARVIN - MAYRA\n");

    do
    {
        opcion = mostrarMenu();

        switch (opcion)
        {
        case 1:
            registrarBitacora();
            break;

        case 2:
            consultarBitacora();
            break;

        case 3:
            printf("\n  [OK] Cerrando el programa. ¡Hasta luego!\n\n");
            break;

        default:
            printf("\n  [ERROR] Opción inválida. Ingrese 1, 2 o 3.\n");
            break;
        }

    } while (opcion != 3);

    return 0;
}