#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLEADOS 10

FILE *archivoEmpleados;
FILE *archivoEmpleadosEliminados;

struct Empleado {
    int id;
    char nombre[50];
    float salario;
    int horas;
};

void leerEmpleado(struct Empleado *empleado) {
    printf("\nIngrese el ID: ");
    scanf("%d", &empleado->id);

    printf("Ingrese el nombre: ");
    scanf("%s", empleado->nombre);

    printf("Ingrese el salario: ");
    scanf("%f", &empleado->salario);

    printf("Ingrese las horas semanales: ");
    scanf("%d", &empleado->horas);
}

void agregarEmpleado() {
    struct Empleado nuevoEmpleado;
    leerEmpleado(&nuevoEmpleado);

    archivoEmpleados = fopen("empleados.txt", "a");
    if (archivoEmpleados == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    fprintf(archivoEmpleados, "ID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
            nuevoEmpleado.id, nuevoEmpleado.nombre, nuevoEmpleado.salario, nuevoEmpleado.horas);

    fclose(archivoEmpleados);
}

void listarEmpleados() {
    struct Empleado empleadoActual;

    archivoEmpleados = fopen("empleados.txt", "r");
    if (archivoEmpleados == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    printf("\nLista de empleados:\n");

    while (fscanf(archivoEmpleados, "ID: %d\nNombre: %s\nSueldo: %f\nHoras semanales: %d\n\n",
                  &empleadoActual.id, empleadoActual.nombre, &empleadoActual.salario, &empleadoActual.horas) != EOF) {
        printf("ID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
                empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
    }

    fclose(archivoEmpleados);
}

void eliminarEmpleado(int idAEliminar) {
    struct Empleado empleadoActual;
    FILE *tempFd = fopen("temp.txt", "w");

    archivoEmpleados = fopen("empleados.txt", "r");
    archivoEmpleadosEliminados = fopen("empleados_eliminados.txt", "a");

    if (archivoEmpleados == NULL || archivoEmpleadosEliminados == NULL || tempFd == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    while (fscanf(archivoEmpleados, "ID: %d\nNombre: %s\nSueldo: %f\nHoras semanales: %d\n\n",
                  &empleadoActual.id, empleadoActual.nombre, &empleadoActual.salario, &empleadoActual.horas) != EOF) {
        if (empleadoActual.id == idAEliminar) {
            fprintf(archivoEmpleadosEliminados, "%d, %s, %.2f, %d\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
        } else {
            fprintf(tempFd, "ID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
        }
    }

    fclose(archivoEmpleados);
    fclose(archivoEmpleadosEliminados);
    fclose(tempFd);

    remove("empleados.txt");
    rename("temp.txt", "empleados.txt");
}

void consultarEmpleado(int idAConsultar) {
    struct Empleado empleadoActual;
    int encontrado = 0;

    archivoEmpleados = fopen("empleados.txt", "r");
    if (archivoEmpleados == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    while (fscanf(archivoEmpleados, "ID: %d\nNombre: %s\nSueldo: %f\nHoras semanales: %d\n\n",
                  &empleadoActual.id, empleadoActual.nombre, &empleadoActual.salario, &empleadoActual.horas) != EOF) {
        if (empleadoActual.id == idAConsultar) {
            encontrado = 1;
            printf("\nID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
        }
    }

    fclose(archivoEmpleados);

    if (!encontrado) {
        printf("No se encontró un empleado con el ID %d\n", idAConsultar);
    }
}

void modificarSalario(int idAModificar) {
    struct Empleado empleadoActual;
    int encontrado = 0;
    float nuevoSalario;

    archivoEmpleados = fopen("empleados.txt", "r");
    archivoEmpleadosEliminados = fopen("empleados_eliminados.txt", "a");
    FILE *tempFd = fopen("temp.txt", "w");

    if (archivoEmpleados == NULL || archivoEmpleadosEliminados == NULL || tempFd == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    while (fscanf(archivoEmpleados, "ID: %d\nNombre: %s\nSueldo: %f\nHoras semanales: %d\n\n",
                  &empleadoActual.id, empleadoActual.nombre, &empleadoActual.salario, &empleadoActual.horas) != EOF) {
        if (empleadoActual.id == idAModificar) {
            encontrado = 1;
            printf("Nuevo salario para %s: ", empleadoActual.nombre);
            scanf("%f", &nuevoSalario);
            fprintf(archivoEmpleadosEliminados, "%d, %s, %.2f, %d\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
            fprintf(tempFd, "ID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
                    empleadoActual.id, empleadoActual.nombre, nuevoSalario, empleadoActual.horas);
            printf("Salario modificado exitosamente.\n");
        } else {
            fprintf(tempFd, "ID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
        }
    }

    fclose(archivoEmpleados);
    fclose(archivoEmpleadosEliminados);
    fclose(tempFd);

    remove("empleados.txt");
    rename("temp.txt", "empleados.txt");

    if (!encontrado) {
        printf("No se encontró un empleado con el ID %d\n", idAModificar);
    }
}

void modificarHoras(int idAModificar) {
    struct Empleado empleadoActual;
    int encontrado = 0;
    int nuevasHoras;

    archivoEmpleados = fopen("empleados.txt", "r");
    archivoEmpleadosEliminados = fopen("empleados_eliminados.txt", "a");
    FILE *tempFd = fopen("temp.txt", "w");

    if (archivoEmpleados == NULL || archivoEmpleadosEliminados == NULL || tempFd == NULL) {
        printf("Error al tratar de abrir el archivo");
        return;
    }

    while (fscanf(archivoEmpleados, "ID: %d\nNombre: %s\nSueldo: %f\nHoras semanales: %d\n\n",
                  &empleadoActual.id, empleadoActual.nombre, &empleadoActual.salario, &empleadoActual.horas) != EOF) {
        if (empleadoActual.id == idAModificar) {
            encontrado = 1;
            printf("Nuevas horas para %s: ", empleadoActual.nombre);
            scanf("%d", &nuevasHoras);
            fprintf(archivoEmpleadosEliminados, "%d, %s, %.2f, %d\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
            fprintf(tempFd, "ID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, nuevasHoras);
            printf("Horas modificadas exitosamente.\n");
        } else {
            fprintf(tempFd, "ID: %d\nNombre: %s\nSueldo: %.2f\nHoras semanales: %d\n\n",
                    empleadoActual.id, empleadoActual.nombre, empleadoActual.salario, empleadoActual.horas);
        }
    }

    fclose(archivoEmpleados);
    fclose(archivoEmpleadosEliminados);
    fclose(tempFd);

    remove("empleados.txt");
    rename("temp.txt", "empleados.txt");

    if (!encontrado) {
        printf("No se encontró un empleado con el ID %d\n", idAModificar);
    }
}