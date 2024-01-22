#include "menu_empleados.h"

int main() {
  int eleccion;

  while (1) {
    printf("\n\t.: Sistema de Citas:. \n");
    printf("1. Agendar Cita\n");
    printf("2. Editar cita\n");
    printf("3. Eliminar cita\n");
    printf("4. Visualizar citas\n");
    printf("5. Salir\n");
    printf("Ingrese su eleccion: ");
    scanf("%d", &eleccion);

    switch (eleccion) {
      case 1:
      agendar_cita();
        break;

      case 2:
      editar_cita();
        break;

      case 3:
      eliminar_cita();
        break;

      case 4:
      mostrar_citas();
        break;

      case 5:
      printf("\nGracias por usar nuestro programa. ¡Hasta luego!\n");
        exit(0);

      default:
      printf("\nOpción inválida. Intente de nuevo.\n");
        break;
    }
  } 
  return 0;
}