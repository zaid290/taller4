#include <stdio.h>
#include <string.h>



int main() {
    int MAX_PRODUCTOS=5;
    int MAX_NOMBRE =30;
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE];
    float tiempoFabricacion[MAX_PRODUCTOS];
    int recursosPorUnidad[MAX_PRODUCTOS];
    int cantidadDemandada[MAX_PRODUCTOS];
    int activos[MAX_PRODUCTOS]; // 1= si esta activo, 0= si esta vacio
    int opcion, i;
    float tiempoDisponible, tiempoTotal;
    int recursosDisponibles, recursosTotales;
    char buscarNombre[MAX_NOMBRE];

    for (i = 0; i < MAX_PRODUCTOS; i++) activos[i] = 0;

    do {
        printf("\n      MENU PRINCIPAL      \n");
        printf("1. Ingresar producto\n");
        printf("2. Mostrar productos\n");
        printf("3. Calcular tiempo y recursos totales\n");
        printf("4. Verificar si se puede cumplir la demanda\n");
        printf("5. Editar producto\n");
        printf("6. Eliminar producto\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            printf("Entrada invalida.\n");
            return 0;
        }
        getchar(); // limpiar \n

        switch(opcion) {
            case 1: {
                // buscar primer hueco libre
                int idx = -1;
                for (i = 0; i < MAX_PRODUCTOS; i++) {
                    if (activos[i] == 0) { idx = i; break; }
                }
                if (idx == -1) {
                    printf("Capacidad maxima alcanzada (%d productos). Elimine uno para agregar.\n", MAX_PRODUCTOS);
                    break;
                }

                printf("\n    Ingreso de producto espacio %d    \n", idx+1);
                printf("Nombre del producto: ");
                fgets(nombres[idx], MAX_NOMBRE, stdin);
                nombres[idx][strcspn(nombres[idx], "\n")] = '\0';

                printf("Tiempo de fabricacion por unidad (horas): ");
                scanf("%f", &tiempoFabricacion[idx]);
                printf("Recursos requeridos por unidad: ");
                scanf("%d", &recursosPorUnidad[idx]);
                printf("Cantidad: ");
                scanf("%d", &cantidadDemandada[idx]);
                getchar(); // limpiar baffer
                activos[idx] = 1;
                printf("Producto agregado correctamente.\n");
                break;
            }

            case 2:
                printf("\n    LISTA DE PRODUCTOS    \n");
                for (i = 0; i < MAX_PRODUCTOS; i++) {
                    if (activos[i]) {
                        printf("Producto %d: %s\n", i + 1, nombres[i]);
                        printf("  Tiempo por unidad: %.2f h\n", tiempoFabricacion[i]);
                        printf("  Recursos por unidad: %d\n", recursosPorUnidad[i]);
                        printf("  Cantidad: %d\n\n", cantidadDemandada[i]);
                    }
                }
                break;

            case 3:
                tiempoTotal = 0.0f;
                recursosTotales = 0;
                for (i = 0; i < MAX_PRODUCTOS; i++) {
                    if (activos[i]) {
                        tiempoTotal += tiempoFabricacion[i] * cantidadDemandada[i];
                        recursosTotales += recursosPorUnidad[i] * cantidadDemandada[i];
                    }
                }
                printf("\nTiempo total de fabricacion: %.2f horas\n", tiempoTotal);
                printf("Recursos totales necesarios: %d unidades\n", recursosTotales);
                break;

            case 4:
                printf("\nIngrese el tiempo disponible (horas): ");
                scanf("%f", &tiempoDisponible);
                printf("Ingrese los recursos disponibles: ");
                scanf("%d", &recursosDisponibles);
                getchar();

                tiempoTotal = 0.0f;
                recursosTotales = 0;
                for (i = 0; i < MAX_PRODUCTOS; i++) {
                    if (activos[i]) {
                        tiempoTotal += tiempoFabricacion[i] * cantidadDemandada[i];
                        recursosTotales += recursosPorUnidad[i] * cantidadDemandada[i];
                    }
                }

                if (tiempoTotal <= tiempoDisponible && recursosTotales <= recursosDisponibles) {
                    printf("\n La fabrica PUEDE cumplir con la demanda.\n");
                } else {
                    printf("\n La fabrica NO puede cumplir con la demanda.\n");
                    printf("Tiempo requerido: %.2f / Disponible: %.2f\n", tiempoTotal, tiempoDisponible);
                    printf("Recursos requeridos: %d / Disponibles: %d\n", recursosTotales, recursosDisponibles);
                }
                break;

            case 5:
                printf("\nIngrese el nombre del producto para editar: ");
                fgets(buscarNombre, MAX_NOMBRE, stdin);
                buscarNombre[strcspn(buscarNombre, "\n")] = '\0';

                for (i = 0; i < MAX_PRODUCTOS; i++) {
                    if (activos[i] && strcmp(nombres[i], buscarNombre) == 0) {
                        printf("\n    Editando producto: %s    \n", nombres[i]);
                        printf("Nuevo nombre (enter para mantener): ");
                        char temp[MAX_NOMBRE];
                        fgets(temp, MAX_NOMBRE, stdin);
                        temp[strcspn(temp, "\n")] = '\0';
                        if (strlen(temp) > 0) strcpy(nombres[i], temp);

                        printf("Nuevo tiempo por unidad (-1 para mantener): ");
                        float ttmp; scanf("%f", &ttmp);
                        if (ttmp >= 0) tiempoFabricacion[i] = ttmp;

                        printf("Nuevos recursos por unidad (-1 para mantener): ");
                        int rtmp; scanf("%d", &rtmp);
                        if (rtmp >= 0) recursosPorUnidad[i] = rtmp;

                        printf("Nueva cantidad (-1 para mantener): ");
                        int qtmp; scanf("%d", &qtmp);
                        if (qtmp >= 0) cantidadDemandada[i] = qtmp;
                        getchar();

                        printf("Producto actualizado correctamente.\n");
                        break;
                    }
                }
                if (i == MAX_PRODUCTOS) printf("Producto no encontrado.\n");
                break;

            case 6:
                printf("\nIngrese el nombre del producto a eliminar: ");
                fgets(buscarNombre, MAX_NOMBRE, stdin);
                buscarNombre[strcspn(buscarNombre, "\n")] = '\0';

                for (i = 0; i < MAX_PRODUCTOS; i++) {
                    if (activos[i] && strcmp(nombres[i], buscarNombre) == 0) {
                        activos[i] = 0;
                        printf("Producto '%s' eliminado correctamente.\n", buscarNombre);
                        break;
                    }
                }
                if (i == MAX_PRODUCTOS) printf("Producto no encontrado.\n");
                break;

            case 0:
                printf("\nSaliendo del programa\n");
                break;

            default:
                printf("Opcion invalida. vuelva a intentar.\n");
        }

    } while(opcion != 0);

    return 0;
}
