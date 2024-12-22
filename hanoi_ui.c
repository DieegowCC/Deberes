#include <stdio.h>
#include <stdlib.h>

/*
    Autor: Diego Alejandro Cardona Castillo
    Fecha: 22 de diciembre de 2024
    Descripción:
        Este programa implementa una representación visual y funcional del clásico juego de las Torres de Hanoi.
        El jugador debe mover discos entre tres ejes, respetando las reglas del juego:
        - No se puede colocar un disco de mayor diámetro sobre uno de menor diámetro.
        - No se puede mover un disco de un eje vacío.
        - Solo se puede mover un disco a la primera posición inferior libre del eje destino.
*/














/*
    FUNCIÓN: hanoi_ui_3discos
    PARÁMETROS: int * posicion_discos
        Este puntero apunta al primer entero de un array de tres elementos que representan las posiciones de los discos en cada eje.
        Los valores válidos son:
        -> 1: eje izquierdo
        -> 2: eje central
        -> 3: eje derecho
    Descripción:
        Esta función visualiza el estado de las torres de Hanoi con tres discos, mostrando su disposición en la consola.
        Se asegura de que los discos se coloquen correctamente en las posiciones especificadas y verifica que no haya violaciones de las reglas del juego.
*/





void
 hanoi_ui_3discos(int* posicion_discos) {
    // Inicialización de una matriz 3x3 para representar las torres de Hanoi
    const char* arr[3][3] = {
        {"    |    ", "    |    ", "    |    "},
        {"    |    ", "    |    ", "    |    "},
        {"    |    ", "    |    ", "    |    "}
    };

    // Definición de los tamaños de los discos
		    const char* d1 = "    #    ";  // Disco pequeño
		    const char* d2 = "   ###   ";  // Disco mediano
		    const char* d3 = "  #####  ";  // Disco grande
		    
    // Colocación de los discos en la matriz según las posiciones
    for (int i = 0; i < 3; i++) {
        int columna = posicion_discos[i] - 1; // Ajuste del índice de la columna (1 -> 0, 2 -> 1, 3 -> 2)
        
        // Búsqueda de la posición más baja disponible en la columna
        int fila = -1;
        for (int j = 2; j >= 0; j--) {  // Recorre las filas de abajo hacia arriba
            if (arr[j][columna] == "    |    ") {  // Verifica si hay un espacio vacío
                fila = j;  // Guarda la posición disponible
                break;
            }
        }

        if (fila != -1) {  // Si se encontró una posición vacía
            // Asignación del disco según su tamaño
            switch (i) {
                case 0:
                    arr[fila][columna] = d3;  // Coloca el disco grande
                    break;
                case 1:
                    arr[fila][columna] = d2;  // Coloca el disco mediano
                    break;
                case 2:
                    arr[fila][columna] = d1;  // Coloca el disco pequeño
                    break;
                default:
                    break;
            }
        } else {
            // Mensaje de error si no hay espacio disponible
            printf("No hay espacio disponible en el eje %d para el disco %d.\n", columna + 1, i + 1);
        }
    }

    // Verificación de la correcta disposición de los discos
    for (int col = 0; col < 3; col++) {
        for (int row = 2; row > 0; row--) {
            if (arr[row][col] == d1 && arr[row - 1][col] == d2) { // Disco pequeño debajo del mediano
                // Intercambio de discos
                arr[row][col] = d2;
                arr[row - 1][col] = d1;
            }
            if (arr[row][col] == d2 && arr[row - 1][col] == d3) { // Disco mediano debajo del grande
                // Intercambio de discos
                arr[row][col] = d3;
                arr[row - 1][col] = d2;
            }
        }
    }
	
    // Impresión del estado de los ejes
    printf("Estado de los ejes\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%s ", arr [i][j]); // Imprime cada valor con un espacio
        }
        printf("\n"); // Nueva línea al final de cada fila
    }
}







/*
    FUNCIÓN: hanoi_ui_ndiscos
    PARÁMETROS: int * posicion_discos
        Este puntero apunta al primer entero de un array que registra las posiciones de n discos en cada eje.
        Los valores válidos son:
        -> 1: eje izquierdo
        -> 2: eje central
        -> 3: eje derecho
    Descripción:
        Esta función visualiza el estado de las torres de Hanoi para un número variable de discos, mostrando tanto la representación numérica como gráfica de las torres.
        Se asegura de que el número de discos no exceda el límite permitido y organiza los discos en la matriz de acuerdo a sus posiciones.
*/










void visualizar_hanoi(int total_discos, int* ubicacion_discos) {
    int matriz[total_discos][3]; // Representación de las torres

    if (total_discos <= 10) { // Verificación del límite de discos
        // Inicialización de la matriz con ceros
        for (int fila = 0; fila < total_discos; fila++) {
            for (int columna = 0; columna < 3; columna++) {
                matriz[fila][columna] = 0; // Asigna cero a cada posición
            }
        }




        // Posicionamiento de los discos según su ubicación
        int niveles[3] = {total_discos - 1, total_discos - 1, total_discos - 1}; // Niveles disponibles
        for (int disco = 0; disco < total_discos; disco++) {
            int torre_actual = ubicacion_discos[disco] - 1; // Torre objetivo (0, 1, 2)
            matriz[niveles[torre_actual]][torre_actual] = total_discos - disco; // Asigna el disco de mayor a menor
            niveles[torre_actual]--; // Reduce el nivel disponible
        }





        // Mostrar el estado numérico de las torres
        printf("\nEstado numérico de las torres:\n\n");
        for (int fila = 0; fila < total_discos; fila++) {
            for (int columna = 0; columna < 3; columna++) {
                printf(" %6d ", matriz[fila][columna]); // Muestra el valor o 0
            }
            printf("\n");
        }
        printf("\n");






        // Mostrar el estado gráfico de las torres
        printf("\nEstado gráfico de las torres:\n\n");
        for (int fila = 0; fila < total_discos; fila++) {
            for (int columna = 0; columna < 3; columna++) {
                if (matriz[fila][columna] != 0) {
                    // Imprime la representación gráfica del disco según su tamaño
                    switch (matriz[fila][columna]) {
                        case 1: printf("         #         "); break;
                        case 2: printf("        ###        "); break;
                        case 3: printf("       #####       "); break;
                        case 4: printf("      #######      "); break;
                        case 5: printf("     #########     "); break;
                        case 6: printf("    ###########    "); break;
                        case 7: printf("   #############   "); break;
                        case 8: printf("  ###############  "); break;
                        case 9: printf(" ################# "); break;
                        case 10: printf("###################"); break;
                        default: break;
                    }
                } else {
                    printf("         |         "); // Representa un espacio vacío
                }
            }
            printf("\n");
        }
        printf("\n");
	}
}





/*
    FUNCIÓN: main
    Descripción:
        Función principal del programa que ejecuta ejemplos de las funciones hanoi_ui_3discos y visualizar_hanoi.
        Inicializa las posiciones de los discos y llama a las funciones para mostrar el estado de las torres.
*/







int main(int argc, char *argv[]) {
	
	
	
	
	
	
    // Ejemplo de uso de la función hanoi_ui_3discos
    printf("Ejemplo de hanoi_ui_3discos\n");
    int posiciones[] = {3 , 3, 3}; // Inicializa las posiciones de los discos en el eje derecho
    hanoi_ui_3discos(posiciones); // Llama a la función para visualizar el estado de las torres con 3 discos






    // Ejemplo de uso de la función visualizar_hanoi
    printf("\nEjemplo de visualizar_hanoi\n");
    int nuevas_posiciones[] = {3, 2, 1, 1, 1}; // Inicializa las posiciones de 5 discos
    visualizar_hanoi(5, nuevas_posiciones); // Llama a la función para mostrar el estado gráfico y numérico de las torres



	return 0;

}

