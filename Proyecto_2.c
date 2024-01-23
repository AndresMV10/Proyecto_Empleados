#include "menu_empleados.h"

int main() {
    int opcion, id;

    do {
        printf("\n\t.:MENU:.\n");
        printf("1. Alta empleado\n");
        printf("2. Baja empleado\n");
        printf("3. Lista de empleados\n");
        printf("4. Consultar datos de empleados\n");
        printf("5. Modificar salario\n");
        printf("6. Modificar horas\n");
        printf("7. Salir\n");

        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarEmpleado();
                break;
            case 2:
                printf("Ingrese el ID del empleado a dar de baja: ");
                scanf("%d", &id);
                eliminarEmpleado(id);
                break;
            case 3:
                listarEmpleados();
                break;
            case 4:
                printf("Ingrese el ID del empleado a consultar: ");
                scanf("%d", &id);
                consultarEmpleado(id);
                break;
            case 5:
                printf("Ingrese el ID del empleado a modificar salario: ");
                scanf("%d", &id);
                modificarSalario(id);
                break;
            case 6:
                printf("Ingrese el ID del empleado a modificar horas: ");
                scanf("%d", &id);
                modificarHoras(id);
                break;
            case 7:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Por favor, elija una opción del 1 al 7.\n");
        }
    } while (opcion != 7);

    return 0;
}

